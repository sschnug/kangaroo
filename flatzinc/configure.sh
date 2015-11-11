#!/bin/bash

BASEDIR=$1;

function gen_flatzinc_makefile {
  local FILE="Makefile";

  echo > ${FILE};
  echo "include ${BASEDIR}/template.mk" >> ${FILE};
  echo >> ${FILE};
  echo "BASE=${BASEDIR}" >> ${FILE};
  echo "INC_BASE= -I\$(BASE) -I\${BASE}/emu" >> ${FILE};
  echo "LD_BASE= -L\$(BASE)" >> ${FILE};
  echo "FZ_FLAGS= -DNDEBUG" >> ${FILE};
  echo >> ${FILE};
  echo "SRCS=\$(wildcard *.cpp)" >> ${FILE};
  echo >> ${FILE};
  echo "OBJS=\$(SRCS:.cpp=.o)" >> ${FILE};
  echo >> ${FILE};
  echo "EXEC=kangaroo-fz">> ${FILE};
  echo >> ${FILE};
  echo "all: lexer.yy.cpp parser.tab.cpp \$(OBJS) \$(EXEC)" >> ${FILE};
  echo >> ${FILE};
  echo "\$(EXEC): lexer.yy.o parser.tab.o \$(OBJS)" >> ${FILE};
  echo -e "\t\$(CC) \$(FZ_FLAGS) \$(INC_BASE) \$(OFLAGS) \$(OBJS) \$(LD_BASE) -lkangaroo -lm -o \$@" >> ${FILE};
  echo >> ${FILE};
  echo ".cpp.o:" >> ${FILE};
  echo -e "\t\$(CC) -c \$(CFLAGS) \$(FZ_FLAGS) \$(INC_BASE) \$< -o \$@" >> ${FILE};
  echo >> ${FILE};
  echo "lexer.yy.cpp: lexer.lxx parser.tab.hpp" >> ${FILE};
  echo -e "\tflex -olexer.yy.cpp lexer.lxx" >> ${FILE};
  echo >> ${FILE};
  echo "parser.tab.hpp parser.tab.cpp: parser.yxx" >> ${FILE};
  echo -e "\tbison -t -o parser.tab.cpp -d \$<" >> ${FILE};
  echo >> ${FILE};
  echo ".PHONY: clean">> ${FILE};
  echo "clean:" >> ${FILE};
  echo -e "\trm -f \${EXEC} *.o *~" >> ${FILE};
  echo >> ${FILE};
  echo ".PHONY: distclean">> ${FILE};
  echo "distclean: clean" >> ${FILE};
  echo -e "\trm -f lexer.yy.cpp parser.tab.hpp parser.tab.cpp" >> ${FILE};
  echo >> ${FILE};
}

gen_flatzinc_makefile;

