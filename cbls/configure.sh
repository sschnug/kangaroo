#!/bin/bash

BASEDIR=$1;
SCRDIRS="";

function exist {
  for f in $1/$2; do
    if [ -e "$f" ]; then
      echo $f;
      return 1;
    else
      return 0;
    fi
  done
}

function discover {
  for d in $1; do
    if [ -d $d ]; then
      if [ `exist $d "*.cpp"` ] || [ `exist $d "*.cc"` ]; then
        SRCDIRS="${SRCDIRS} $d";
      fi
      discover "$d/*";
    fi
  done
}

function gen_sub_makefile {
  local FILE="$1/Makefile";

  echo > ${FILE};
  echo "include ${BASEDIR}/template.mk" >> ${FILE};
  echo >> ${FILE};
  echo "INC_BASE= -I${BASEDIR} -I${BASEDIR}/emu" >> ${FILE};
  echo >> ${FILE};
  echo "SRCS=\$(wildcard *.cpp)" >> ${FILE};
  echo >> ${FILE};
  echo "OBJS=\$(SRCS:.cpp=.o)" >> ${FILE};
  echo >> ${FILE};
  echo "all: \$(OBJS)" >> ${FILE};
  echo >> ${FILE};
  echo ".cpp.o:" >> ${FILE};
  echo -e "\t\$(CC) -c \$(CFLAGS) \$(INC_BASE) \$< -o \$@" >> ${FILE};
  echo >> ${FILE};
  echo ".PHONY: clean">> ${FILE};
  echo "clean:" >> ${FILE};
  echo -e "\trm -f \${OBJS} *~" >> ${FILE};
  echo >> ${FILE};
}

function gen_libmain_makefile {
  local FILE="Makefile";

  echo > ${FILE};
  echo "include ${BASEDIR}/template.mk" >> ${FILE};
  echo >> ${FILE};
  echo "EXEC=kangaroo">> ${FILE};
  echo >> ${FILE};
  local OBJS="";
  for d in ${SRCDIRS}; do
    OBJS="${OBJS} $d/*.o";
  done
  echo "LOBJS=${OBJS}" >> ${FILE};
  echo >> ${FILE};
  echo "all: subdirs \$(EXEC)" >> ${FILE};
  echo >> ${FILE};
  echo "\$(EXEC): subdirs" >> ${FILE};
  echo -e "\t\$(AR) lib\$@.a \$(LOBJS)" >> ${FILE};
  echo >> ${FILE};
  echo ".PHONY: subdirs">> ${FILE};
  echo "subdirs:" >> ${FILE};
  for d in ${SRCDIRS}; do
    echo -e "\t@\${MAKE} -w -C $d" >> ${FILE};
  done
  echo >> ${FILE};
  echo ".PHONY: clean">> ${FILE};
  echo "clean:" >> ${FILE};
  for d in ${SRCDIRS}; do
    echo -e "\t@\${MAKE} -w -C $d clean" >> ${FILE};
  done
  echo -e "\trm -f lib\${EXEC}.a *~" >> ${FILE};
  echo >> ${FILE};
}

## MAIN ##
for f in `ls | grep -v -E ".svn"`; do
  discover $f;
done

for d in ${SRCDIRS}; do
  gen_sub_makefile $d;
done

gen_libmain_makefile;

