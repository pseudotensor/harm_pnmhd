# $4 is for taking in the -p../genimage.pal a pallete command for ppm2fli
# eg. ./block2tileall.sh 32 32 32 tile.r8
#
# set size of array
echo start
nx=$1
ny=$2
nz=$3
type=$4

# slice #0 
./block2tile.sh $nx $ny $nz s1 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s1 0 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 0 1 0 $type $4 $5 $6 $7 $8 $9
# ./block2tile.sh $nx $ny $nz s3 0 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 0 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 0 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 0 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 0 1 0 $type $4 $5 $6 $7 $8 $9

./block2tile.sh $nx $ny $nz v2-0 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 0 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-0 0 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 0 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 0 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 0 1 0 $type $4 $5 $6 $7 $8 $9

./block2tile.sh $nx $ny $nz s1 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s1 1 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 1 1 0 $type $4 $5 $6 $7 $8 $9
# ./block2tile.sh $nx $ny $nz s3 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 1 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 1 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 1 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 1 1 0 $type $4 $5 $6 $7 $8 $9

./block2tile.sh $nx $ny $nz v2-0 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 1 0 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-0 1 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 1 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 1 1 0 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 1 1 0 $type $4 $5 $6 $7 $8 $9

# slice #1

./block2tile.sh $nx $ny $nz s1 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s1 0 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 0 1 1 $type $4 $5 $6 $7 $8 $9
# ./block2tile.sh $nx $ny $nz s3 0 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 0 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 0 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 0 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 0 1 1 $type $4 $5 $6 $7 $8 $9

./block2tile.sh $nx $ny $nz v2-0 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 0 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-0 0 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 0 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 0 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 0 1 1 $type $4 $5 $6 $7 $8 $9

./block2tile.sh $nx $ny $nz s1 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s1 1 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz s2 1 1 1 $type $4 $5 $6 $7 $8 $9
# ./block2tile.sh $nx $ny $nz s3 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-0 1 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-1 1 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-2 1 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v1-3 1 1 1 $type $4 $5 $6 $7 $8 $9

./block2tile.sh $nx $ny $nz v2-0 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 1 0 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-0 1 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-1 1 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-2 1 1 1 $type $4 $5 $6 $7 $8 $9
./block2tile.sh $nx $ny $nz v2-3 1 1 1 $type $4 $5 $6 $7 $8 $9

echo end
