nx=$1
ny=$2
name=$3
mkdir ../fli
ls *.new.ppm.gz > $name.lst
#ls iimx$outtype-$maptype-$slicenum-$type-*.dat.$filetype.gz > imx$outtype-$maptype-$slicenum-$type.lst
#ls -rt | egrep '\.ppm.gz$' > $name.lst
#ls -rt | egrep '\.dat.r8.gz$' > imx$outtype-$maptype-$slicenum-$type.lst
#ppm2fli $8 -g $nx'x'$ny -s 0 imx$outtype-$maptype-$slicenum-$type.lst ../fli/$outtype-$maptype-$slicenum-$type.fli < ../y.txt
ppm2fli -N -fgunzip -g $nx'x'$ny -s 0 $name.lst ../fli/$name.fli < ../y.txt
#mpeg2encode MPEG-1.par ../mpg/$outtype-$maptype-$slicenum-$type.mpg
rm $name.lst

