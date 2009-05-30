#!/bin/bash
# type is for taking in the -p../genimage.pal a pallete command for ppm2fli
# eg. sh ./csumallppm.sh 128 128 128 1 r8 ../genimages.pal
# eg. sh ./sumallppm.sh 344 168 128 1 ppm
# set size of array
echo start
nx=$1
ny=$2
nz=$3
norm=$4
type=$5

# slice #0 
sh ./csumppm.sh $nx $ny $nz $norm s1 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s1 0 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 0 1 0 $type  $6 $7 $8 $9
# sh ./csumppm.sh $nx $ny $nz $norm s3 0 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 0 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 0 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 0 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 0 1 0 $type  $6 $7 $8 $9

sh ./csumppm.sh $nx $ny $nz $norm v2-0 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 0 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-0 0 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 0 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 0 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 0 1 0 $type  $6 $7 $8 $9

sh ./csumppm.sh $nx $ny $nz $norm s1 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s1 1 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 1 1 0 $type  $6 $7 $8 $9
# sh ./csumppm.sh $nx $ny $nz $norm s3 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 1 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 1 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 1 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 1 1 0 $type  $6 $7 $8 $9

sh ./csumppm.sh $nx $ny $nz $norm v2-0 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 1 0 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-0 1 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 1 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 1 1 0 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 1 1 0 $type  $6 $7 $8 $9

# slice #1

sh ./csumppm.sh $nx $ny $nz $norm s1 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s1 0 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 0 1 1 $type  $6 $7 $8 $9
# sh ./csumppm.sh $nx $ny $nz $norm s3 0 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 0 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 0 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 0 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 0 1 1 $type  $6 $7 $8 $9

sh ./csumppm.sh $nx $ny $nz $norm v2-0 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 0 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-0 0 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 0 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 0 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 0 1 1 $type  $6 $7 $8 $9

sh ./csumppm.sh $nx $ny $nz $norm s1 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s1 1 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm s2 1 1 1 $type  $6 $7 $8 $9
# sh ./csumppm.sh $nx $ny $nz $norm s3 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-0 1 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-1 1 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-2 1 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v1-3 1 1 1 $type  $6 $7 $8 $9

sh ./csumppm.sh $nx $ny $nz $norm v2-0 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 1 0 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-0 1 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-1 1 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-2 1 1 1 $type  $6 $7 $8 $9
sh ./csumppm.sh $nx $ny $nz $norm v2-3 1 1 1 $type  $6 $7 $8 $9

echo end
