# eg. ./sumppm.sh 128 128 s1 0 0 0 r8 -p../genimages.pal
echo start
nx=$1
ny=$2
type=$3
outtype=$4
maptype=$5
slicenum=$6
filetype=$7
#$7 is palette command for r8s like: -p../genimages.pal
echo $nx $ny
echo $type
echo $outtype
echo $maptype
echo $filetype
echo $slicenum
mkdir ./fli
mkdir ./mpg
cd ./imx$outtype-$maptype-$slicenum-$type/
gzip *.dat*
#ls imx$outtype-$maptype-$slicenum-$type-*.dat.$filetype > imx$outtype-$maptype-$slicenum-$type.lst
ls imx$outtype-$maptype-$slicenum-$type-*.dat.gz > imx$outtype-$maptype-$slicenum-$type.lst
#ls iimx$outtype-$maptype-$slicenum-$type-*.dat.$filetype.gz > imx$outtype-$maptype-$slicenum-$type.lst
#ls -rt | egrep '\.dat.ppm.gz$' > imx$outtype-$maptype-$slicenum-$type.lst
#ls -rt | egrep '\.dat.r8.gz$' > imx$outtype-$maptype-$slicenum-$type.lst
#ppm2fli $8 -g $nx'x'$ny -s 0 imx$outtype-$maptype-$slicenum-$type.lst ../fli/$outtype-$maptype-$slicenum-$type.fli < ../y.txt
ppm2fli $8 -N -fgunzip -g $nx'x'$ny -z $nx'x'$ny -s 0 imx$outtype-$maptype-$slicenum-$type.lst ../fli/$outtype-$maptype-$slicenum-$type.fli < ../y.txt $8 $9
#mpeg2encode MPEG-1.par ../mpg/$outtype-$maptype-$slicenum-$type.mpg
rm imx$outtype-$maptype-$slicenum-$type.lst
cd ..
