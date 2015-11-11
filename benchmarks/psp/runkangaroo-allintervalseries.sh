#!/bin/bash

HOMEDIR="/import/crl-linhome/home/1/dpham/CP-11"
SOLVER="kangaroo"
SDIR="${HOMEDIR}/kangaroo"
PROB="allintervalseries"
PROBID=3

ITRS=10000000

TR=100
#TO=86400

TABU=${1}

for SZ in 10; do
  echo > job.qsub;
  for i in {1..100}; do
    echo "${SDIR}/${SOLVER} ${PROBID} 5 ${TABU} ${ITRS} ${SZ} | ${HOMEDIR}/problems/val${PROB} >> ${HOMEDIR}/results/${SOLVER}/${PROB}/${SOLVER}_${PROB}_${SZ}.5.${TABU}.log" >> job.qsub;
  done

  chmod +x job.qsub;

#  qsub -N g1.2-${1} -q oneHour -l nodes=1 job.qsub;
  #qsub -N ${PROB}-${SZ} -l h_vmem=1G job.qsub;
  qsub -N ${PROB}-${SZ} job.qsub;
  sleep 1
done

