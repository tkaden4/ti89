
TIGCC=../tigcc
LD=$(TIGCC)/bin/ld-tigcc
CC=$(TIGCC)/bin/gcc
CFLAGS=-std=c99 -I ./libs/ -I $(TIGCC)/include/c -w
LDFLAGS=

LIBS=$(wildcard ./libs/*.c)
OBJS=$(patsubst ./libs/%.c, ./libs/%.o, $(LIBS))

export PATH := $(TIGCC)/bin/:$(PATH)

.PHONY: all clean

all: bin/osc.89z bin/rcv.89z bin/rcv2.89z bin/status.89z bin/wrt.89z bin/wrt2.89z bin/cheat.89z bin/u0.89z

bin/%.89z: %.o $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $<  $(TIGCC)/lib/tigcc.a -o $(basename $@) 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm ./bin/*.89z
