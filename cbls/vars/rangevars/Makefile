
include /home/swakkhar/kangaroo/template.mk

INC_BASE= -I/home/swakkhar/kangaroo -I/home/swakkhar/kangaroo/emu

SRCS=$(wildcard *.cpp)

OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)

.cpp.o:
	$(CC) -c $(CFLAGS) $(INC_BASE) $< -o $@

.PHONY: clean
clean:
	rm -f ${OBJS} *~

