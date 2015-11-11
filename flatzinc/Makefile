
include /home/swakkhar/kangaroo/template.mk

BASE=/home/swakkhar/kangaroo
INC_BASE= -I$(BASE) -I${BASE}/emu
LD_BASE= -L$(BASE)
FZ_FLAGS= -DNDEBUG

SRCS=$(wildcard *.cpp)

OBJS=$(SRCS:.cpp=.o)

EXEC=kangaroo-fz

all: lexer.yy.cpp parser.tab.cpp $(OBJS) $(EXEC)

$(EXEC): lexer.yy.o parser.tab.o $(OBJS)
	$(CC) $(FZ_FLAGS) $(INC_BASE) $(OFLAGS) $(OBJS) $(LD_BASE) -lkangaroo -lm -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $(FZ_FLAGS) $(INC_BASE) $< -o $@

lexer.yy.cpp: lexer.lxx parser.tab.hpp
	flex -olexer.yy.cpp lexer.lxx

parser.tab.hpp parser.tab.cpp: parser.yxx
	bison -t -o parser.tab.cpp -d $<

.PHONY: clean
clean:
	rm -f ${EXEC} *.o *~

.PHONY: distclean
distclean: clean
	rm -f lexer.yy.cpp parser.tab.hpp parser.tab.cpp

