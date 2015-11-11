#!/bin/bash

BASEDIR=$1;

function gen_test_makefile {
  local FILE="Makefile";

  echo > ${FILE};
  echo "include ${BASEDIR}/template.mk" >> ${FILE};
  echo >> ${FILE};
  echo "BASE= ${BASEDIR}" >> ${FILE};
  echo "INC_BASE= -I \$(BASE) -I\${BASE}/emu" >> ${FILE};
  echo "LD_BASE= -L \$(BASE)" >> ${FILE};
  echo >> ${FILE};
  echo "CPPSRCS=\$(wildcard *.cpp)" >> ${FILE};
  echo >> ${FILE};
  echo "CCSRCS=\$(wildcard *.cc)" >> ${FILE};
  echo >> ${FILE};
  echo "OBJS=\$(CPPSRCS:.cpp=.o) \$(CCSRCS:.cc=.o)" >> ${FILE};
  echo >> ${FILE};
  echo "EXEC=kangaroo">> ${FILE};
  echo >> ${FILE};
  echo "all: \$(OBJS) \$(EXEC)" >> ${FILE};
  echo >> ${FILE};
  echo "\$(EXEC): \$(OBJS)" >> ${FILE};
  echo -e "\t\$(CC) \$(INC_BASE) \$(OFLAGS) \$(OBJS) \$(LD_BASE) -lkangaroo -lm -o \$@" >> ${FILE};
  echo >> ${FILE};
  echo ".cpp.o:" >> ${FILE};
  echo -e "\t\$(CC) -c \$(CFLAGS) \$(INC_BASE) \$< -o \$@" >> ${FILE};
  echo >> ${FILE};
  echo ".cc.o:" >> ${FILE};
  echo -e "\t\$(CC) -c \$(CFLAGS) \$(INC_BASE) \$< -o \$@" >> ${FILE};
  echo >> ${FILE};
  echo ".PHONY: clean">> ${FILE};
  echo "clean:" >> ${FILE};
  echo -e "\trm -f \${EXEC} *.o *~" >> ${FILE};
  echo >> ${FILE};
}

gen_test_makefile;

