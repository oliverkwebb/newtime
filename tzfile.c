// See https://datatracker.ietf.org/doc/html/rfc8536
// The following code is in the public domain
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

struct __attribute__((packed)) tzheader {
	uint8_t  magic[4];
	uint8_t  version;
	uint8_t  reserved[15];

	uint32_t isutcnt;
	uint32_t isstdcnt;
	uint32_t leapcnt;
	uint32_t timecnt;
	uint32_t typecnt;
	uint32_t charcnt;
};

int main(int argc, char **argv)
{
	if (!argv[1]) {
		fprintf(stderr, "Use: %s [file]", argv[0]);
		return 1;
	}
	FILE *f = fopen(argv[1], "r");
	if (!f) {
		fprintf(stderr, "Non File: %s", argv[1]);
		return 1;
	}

	struct tzheader h;
	fread(&h, 44, 1, f);
	h.isstdcnt = ntohl(h.isstdcnt);
	h.isutcnt  = ntohl(h.isutcnt);
	h.leapcnt  = ntohl(h.leapcnt);
	h.timecnt  = ntohl(h.timecnt);
	h.typecnt  = ntohl(h.typecnt);
	h.charcnt  = ntohl(h.charcnt);

	// Version 1 data block
	int32_t ttimes[h.timecnt];
	uint8_t ttypes[h.timecnt];
	struct __attribute__((packed)) lttr {
		int32_t utoff;
		uint8_t dst;
		uint8_t idx;
	} lttr[h.typecnt];
	uint8_t tzdesig[h.charcnt];
	struct __attribute__((packed)) lsrec {
		int32_t occur;
		int32_t correct;
	} leaprecs[h.leapcnt];
	uint8_t wallindic[h.isstdcnt];
	uint8_t localindic[h.isutcnt];

	fread(ttimes, h.timecnt, 4, f);
	for (int i = 0; i < h.timecnt; i++) ttimes[i] = ntohl(ttimes[i]);

	fread(ttypes, h.timecnt, 1, f);
	
	fread(lttr, h.typecnt, sizeof(struct lttr), f);
	for (int i = 0; i < h.typecnt; i++) lttr[i].utoff = ntohl(lttr[i].utoff);

	fread(tzdesig, h.charcnt, 1, f);

	fread(leaprecs, h.leapcnt, 8, f);
	for (int i = 0; i < h.leapcnt; i++) {
		leaprecs[i].occur   = ntohl(leaprecs[i].occur);
		leaprecs[i].correct = ntohl(leaprecs[i].correct);
	}

	fread(wallindic,  h.isstdcnt, 1, f);
	fread(localindic, h.isutcnt,  1, f);

	if (memcmp(h.magic, "TZif", 4))
		return -1;
	printf("Version %c\n", h.version ? : '0');
	printf("%d Entries:\n", h.timecnt);
}
