LIB=libnewtime.a
OLIB=lib/

export CC CFLAGS INCFLAGS LIB
CC=cc
SHUTUP= -Wno-pointer-arith -Wno-discarded-qualifiers
CFLAGS= -pedantic -Wall -I . -funsigned-char -Os -fdata-sections -ffunction-sections $(MYCFLAGS) $(SHUTUP)
CSOURCE=$(wildcard src/*.c)
OBJFILES= $(patsubst src/%.c, obj/%.o, $(CSOURCE)) $(patsubst src/%.S, obj/%.o, $(ASMSOURCE))

Q=@

.PHONY: all clean test

all: $(LIB)

$(LIB): $(OBJFILES)
	rm -f $(LIB)
	ar rs $(OLIB)$@ $^

obj/%.o: src/%.c
	$(Q)printf "CC %-20s -> $@\n" "$<"
	$(Q)$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OLIB)* obj/*.o

test: $(LIB)
	@./test.sh
