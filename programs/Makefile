
TIGCC=../tigcc
LD=$(TIGCC)/bin/ld-tigcc
CC=$(TIGCC)/bin/gcc
CFLAGS=-std=c99 -I ./libs/ -I $(TIGCC)/include/c
LDFLAGS=

LIBS=$(wildcard ./libs/*.c)
OBJS=$(patsubst ./libs/%.c, ./libs/%.o, $(LIBS))

.PHONY: all

all: osc.89z

%.89z: %.o $(OBJS)
	$(LD) $(TIGCC)/lib/tigcc.a $(OBJS) $(LDFLAGS) -o $(basename $@) $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
