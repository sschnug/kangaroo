#!/bin/bash

BASEDIR=`pwd`;
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

## MAIN ##
for f in `ls | grep -v -E ".svn"`; do
  discover $f;
done

for d in ${SRCDIRS}; do
  rm -fr $d/Makefile;
done

rm -fr Makefile
