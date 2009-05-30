# $4 is for taking in the -p../genimage.pal a pallete command for ppm2fli
# eg. ./sumallppm.sh 128 64 r8 -p../genimages.pal
# eg. ./sumallppm.sh 344 168 ppm
# set size of array
echo start
nx=$1
ny=$2

./sumallppm.sh $1 $2 r8 -p../genimages.pal
echo end
