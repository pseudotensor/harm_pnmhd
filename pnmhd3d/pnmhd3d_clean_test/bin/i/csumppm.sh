#!/bin/bash
# eg. ./sumppm.sh 128 128 128 1 s1 0 0 0 r8 ../genimages.pal
echo start
nx=$1
ny=$2
nz=$3
norm=$4
type=$5
outtype=$6
maptype=$7
slicenum=$8
filetype=$9
palette=${10}
echo $nx $ny $nz
echo $type $outtype $maptype $slicenum $filetype
echo $palette
mkdir ./fli
mkdir ./mpg
plane=1
while [ "$plane" -ne 4 ]
do
  echo $plane
if [ "$plane" -eq 3 ]
then
    lnx=$nx
    lny=$ny
fi
if [ "$plane" -eq 2 ]
then
    lnx=$nz
    lny=$nx
fi
if [ "$plane" -eq 1 ]
then
    lnx=$ny
    lny=$nz
fi
cd ./imx$outtype-$maptype-$slicenum-$type/
ls imx$outtype-$maptype-$slicenum-$type-*.dat.$filetype > imx$outtype-$maptype-$slicenum-$type.lst
#ls imx$outtype-$maptype-$slicenum-$type-*.dat.$filetype.gz > imx$outtype-$maptype-$slicenum-$type.lst
#ls iimx$outtype-$maptype-$slicenum-$type-*.dat.$filetype.gz > imx$outtype-$maptype-$slicenum-$type.lst
#ls -rt | egrep '\.dat.ppm.gz$' > imx$outtype-$maptype-$slicenum-$type.lst
#ls -rt | egrep '\.dat.r8.gz$' > imx$outtype-$maptype-$slicenum-$type.lst
# below is best (err, correct even)
#ls | sort | egrep '\.dat.r8.gz$' > imx$outtype-$maptype-$slicenum-$type.lst

# convert 3D image to 2D image
for fil in `cat imx$outtype-$maptype-$slicenum-$type.lst`
  do
  echo converting $fil to c${plane}$fil
  ../column b 1 $fil c${plane}$fil $nx $ny $nz 1 $plane $norm
done
ls c${plane}imx$outtype-$maptype-$slicenum-$type-*.dat.$filetype > c${plane}imx$outtype-$maptype-$slicenum-$type.lst
#ppm2fli -p$palette -z $nx'x'$ny -g $nx'x'$ny -s 0 imx$outtype-$maptype-$slicenum-$type.lst ../fli/$outtype-$maptype-$slicenum-$type.fli < ../y.txt
ppm2fli -p$palette -N -fgunzip -g $lnx'x'$lny -z $lnx'x'$lny -s 0 c${plane}imx$outtype-$maptype-$slicenum-$type.lst ../fli/c${plane}$outtype-$maptype-$slicenum-$type.fli < ../y.txt ${11} ${12}
#mpeg2encode MPEG-1.par ../mpg/$outtype-$maptype-$slicenum-$type.mpg
#rm imx$outtype-$maptype-$slicenum-$type.lst
#rm c${plane}imx$outtype-$maptype-$slicenum-$type.lst
cd ..
plane=$(( $plane + 1 ))
done
