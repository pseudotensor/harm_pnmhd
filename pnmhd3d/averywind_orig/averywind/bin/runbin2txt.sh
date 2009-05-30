#!/bin/sh
#
#  sh runbin2txt.sh 32 16 16 0000 dump
#
#
# $1,$2,$3=nx,ny,nz
# $4=# of the dump
# $5=headername (i.e. dump)
#
# head -n3 ../bin_64cubed_rot_mc_nonuni/0_grid1.par | tail -n 1 | wc -w
#
#
echo $1
echo $2
echo $3
echo $4
echo $5
#
fnamebin=$5$4.dat.bin
fnametxt=$5$4.dat.txt
#
echo $fnamebin $fnametxt
#
bin2txt 1 2 0 0 3 $1 $2 $3 1 $5$4.dat.bin $5$4.dat.txt f 9
cat $5$4.dat.bin.head $5$4.dat.txt > $5$4.dat

bin2txt 1 2 0 0 3 $1 $2 $3 1 0_gridact1.par.bin 0_gridact1.par.txt f 36
bin2txt 1 2 0 0 3 $1 $2 $3 1 0_gridact2.par.bin 0_gridact2.par.txt f 36
cp 0_gridact2.par.bin.head 0_gridact1.par.bin.head
cat 0_gridact1.par.bin.head 0_gridact1.par.txt > 0_gridact1.par
cat 0_gridact2.par.bin.head 0_gridact2.par.txt > 0_gridact2.par

if ((0)); then
bin2txt 1 2 0 0 3 $1 $2 $3 1 0_grid1.par.bin 0_grid1.par.txt f 36
bin2txt 1 2 0 0 3 $1 $2 $3 1 0_grid2.par.bin 0_grid2.par.txt f 36
cp 0_grid2.par.bin.head 0_grid1.par.bin.head
cat 0_grid1.par.bin.head 0_grid1.par.txt > 0_grid1.par
cat 0_grid2.par.bin.head 0_grid2.par.txt > 0_grid2.par
fi
