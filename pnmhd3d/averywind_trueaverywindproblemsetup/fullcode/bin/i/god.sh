#!/bin/sh
god1=($1 - ".gz" )
echo $god1
# parse argument list

          while [ $# -ge 1 ]; do
                  case $1 in
                  -c*)    rate=`echo $1 | cut -c3-`;;
                  -c)     shift;  rate=$1 ;;
                  -p*)    prefix=`echo $1 | cut -c3-`;;
                  -p)     shift;  prefix=$1 ;;
                  -*)     echo $Usage; exit 1 ;;
                  *)      disks=$*;       break   ;;
                  esac

                  shift

          done

year=$1
case "$year" in

          [0-9][0-9])
                  year=19${year}
                  years=`expr $year - 1901`
                  ;;
          [0-9][0-9][0-9][0-9])
                  years=`expr $year - 1901`
                  ;;
          *)
                  echo 1>&2 Year \"$year\" out of range ...
                  exit 127
                  ;;
          esac
echo $years

