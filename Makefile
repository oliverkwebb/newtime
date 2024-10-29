LIB=libnewtime.a
SOLIB=libnewtime.so
OLIB=lib/

export CC CFLAGS INCFLAGS LIB SOLIB
CC=cc
SHUTUP= -Wno-pointer-arith -Wno-discarded-qualifiers
CFLAGS= -pedantic -Wall -I inc/ -funsigned-char -Os -fdata-sections -ffunction-sections $(MYCFLAGS) $(SHUTUP) -lm
CSOURCE=$(wildcard src/*.c)
OBJFILES= $(patsubst src/%.c, obj/%.o, $(CSOURCE)) $(patsubst src/%.S, obj/%.o, $(ASMSOURCE))
PREFIX=/usr/local

Q=@

.PHONY: all clean test install full_test

all: $(LIB) $(SOLIB)

$(LIB): $(OBJFILES)
	rm -f $(OLIB)$(LIB)
	ar rs $(OLIB)$@ $^

$(SOLIB): $(OBJFILES)
	gcc -shared $^ -lm -o $(OLIB)$(SOLIB)

obj/%.o: src/%.c
	$(Q)printf "CC %-20s -> $@\n" "$<"
	$(Q)$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OLIB)* obj/*.o

test: $(LIB)
	@./test.sh

full_test:
	$(MAKE) clean all test
	$(MAKE) clean all test CC=musl-gcc

install: $(LIB) $(SOLIB)
	cp inc/newtime.h $(PREFIX)/include/
	cp lib/$(LIB) $(PREFIX)/lib/
	cp lib/$(SOLIB) $(PREFIX)/lib
