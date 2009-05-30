#!/bin/sh
#
# e.g. ./block2tile.sh 32 32 32 s1 0 0 0 tile.r8
#
nx=$1
ny=$2
nz=$3
type=$4
outtype=$5
maptype=$6
slicenum=$7
filetype=$8
#$7 is palette command for r8s like: -p../genimages.pal
echo $nx $ny $nz
echo $type
echo $outtype
echo $maptype
echo $filetype
echo $slicenum
cd ./imx$outtype-$maptype-$slicenum-$type/
for fil in `/bin/ls imx$outtype-$maptype-$slicenum-$type*`
do 
	echo $fil begin
	block2tile 3 $1 $2 $3 $fil
	echo $fil done
done
cd ..
