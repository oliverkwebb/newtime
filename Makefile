LIB=libnewtime.a
SOLIB=libnewtime.so
OLIB=lib/

export CC CFLAGS INCFLAGS LIB SOLIB
CC=cc
SHUTUP= -Wno-pointer-arith -Wno-discarded-qualifiers
CFLAGS= -pedantic -Wall -I inc/ -funsigned-char -Os -fdata-sections -ffunction-sections $(MYCFLAGS) $(SHUTUP) -lm
CSOURCE=$(wildcard src/*.c)
OBJFILES= $(patsubst src/%.c, obj/%.o, $(CSOURCE)) $(patsubst src/%.S, obj/%.o, $(ASMSOURCE))

Q=@

.PHONY: all clean test

all: $(LIB)

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

install: $(LIB) $(SOLIB)
	cp inc/newtime.h /usr/include/
	cp lib/$(LIB) /usr/lib/
	cp lib/$(SOLIB) /usr/lib