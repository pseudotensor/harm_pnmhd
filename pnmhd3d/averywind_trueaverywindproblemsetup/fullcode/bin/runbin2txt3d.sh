#!/bin/sh
echo $1
echo $2
echo $3
echo $4
bin2txt 1 2 0 3 $1 $2 $3 dump$4.dat.bin dump$4.dat.txt f 9
cat dump$4.dat.bin.head dump$4.dat.txt > dump$4.dat

bin2txt 1 2 3 0 $1 $2 $3 0_gridact1.par.bin 0_gridact1.par.txt f 36
bin2txt 1 2 3 0 $1 $2 $3 0_gridact2.par.bin 0_gridact2.par.txt f 36
cp 0_gridact2.par.bin.head 0_gridact1.par.bin.head
cat 0_gridact1.par.bin.head 0_gridact1.par.txt > 0_gridact1.par
cat 0_gridact2.par.bin.head 0_gridact2.par.txt > 0_gridact2.par

bin2txt 1 2 3 0 $1 $2 $3 0_grid1.par.bin 0_grid1.par.txt f 36
bin2txt 1 2 3 0 $1 $2 $3 0_grid2.par.bin 0_grid2.par.txt f 36
cp 0_grid2.par.bin.head 0_grid1.par.bin.head
cat 0_grid1.par.bin.head 0_grid1.par.txt > 0_grid1.par
cat 0_grid2.par.bin.head 0_grid2.par.txt > 0_grid2.par
