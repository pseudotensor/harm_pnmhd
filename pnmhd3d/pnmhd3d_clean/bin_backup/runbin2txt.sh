#!/bin/sh
echo $1
echo $2
echo $3
echo $4
bin2txt 1 2 0 2 $1 $2 1 1 $4$3.dat.bin $4$3.dat.txt f 9
cat $4$3.dat.bin.head $4$3.dat.txt > $4$3.dat

bin2txt 1 2 0 2 $1 $2 1 1 0_gridact1.par.bin 0_gridact1.par.txt f 36
bin2txt 1 2 0 2 $1 $2 1 1 0_gridact2.par.bin 0_gridact2.par.txt f 36
cp 0_gridact2.par.bin.head 0_gridact1.par.bin.head
cat 0_gridact1.par.bin.head 0_gridact1.par.txt > 0_gridact1.par
cat 0_gridact2.par.bin.head 0_gridact2.par.txt > 0_gridact2.par

bin2txt 1 2 0 2 $1 $2 1 1 0_grid1.par.bin 0_grid1.par.txt f 36
bin2txt 1 2 0 2 $1 $2 1 1 0_grid2.par.bin 0_grid2.par.txt f 36
cp 0_grid2.par.bin.head 0_grid1.par.bin.head
cat 0_grid1.par.bin.head 0_grid1.par.txt > 0_grid1.par
cat 0_grid2.par.bin.head 0_grid2.par.txt > 0_grid2.par
