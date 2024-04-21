
TIGCC=../tigcc
LD=$(TIGCC)/bin/ld-tigcc
CC=$(TIGCC)/bin/gcc
CFLAGS=-std=c99 -I ./libs/ -I $(TIGCC)/include/c
LDFLAGS=

LIBS=$(wildcard ./libs/*.c)
OBJS=$(patsubst ./libs/%.c, ./libs/%.o, $(LIBS))

.PHONY: all clean

all: bin/osc.89z bin/rcv.89z bin/status.89z bin/wrt.89z bin/cheat.89z

bin/%.89z: %.o $(OBJS)
	$(LD) $(TIGCC)/lib/tigcc.a $(OBJS) $(LDFLAGS) -o $(basename $@) $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean: 
	rm ./bin/*.89z
