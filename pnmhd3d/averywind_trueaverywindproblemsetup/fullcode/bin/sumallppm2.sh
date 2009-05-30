# $4 is for taking in the -p../genimage.pal a pallete command for ppm2fli
# eg. ./sumallppm.sh 128 64 r8 -p../genimages.pal
# eg. ./sumallppm.sh 344 168 ppm
# set size of array
echo start
nx=$1
ny=$2
type=$3

# slice #0 
./sumppm2.sh $nx $ny s1 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s1 0 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 0 1 0 $type $4 $5 $6 $7 $8 $9
# ./sumppm2.sh $nx $ny s3 0 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 0 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 0 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 0 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 0 1 0 $type $4 $5 $6 $7 $8 $9

./sumppm2.sh $nx $ny v2-0 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 0 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-0 0 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 0 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 0 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 0 1 0 $type $4 $5 $6 $7 $8 $9

./sumppm2.sh $nx $ny s1 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s1 1 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 1 1 0 $type $4 $5 $6 $7 $8 $9
# ./sumppm2.sh $nx $ny s3 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 1 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 1 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 1 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 1 1 0 $type $4 $5 $6 $7 $8 $9

./sumppm2.sh $nx $ny v2-0 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 1 0 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-0 1 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 1 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 1 1 0 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 1 1 0 $type $4 $5 $6 $7 $8 $9

# slice #1

./sumppm2.sh $nx $ny s1 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s1 0 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 0 1 1 $type $4 $5 $6 $7 $8 $9
# ./sumppm2.sh $nx $ny s3 0 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 0 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 0 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 0 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 0 1 1 $type $4 $5 $6 $7 $8 $9

./sumppm2.sh $nx $ny v2-0 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 0 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-0 0 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 0 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 0 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 0 1 1 $type $4 $5 $6 $7 $8 $9

./sumppm2.sh $nx $ny s1 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s1 1 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny s2 1 1 1 $type $4 $5 $6 $7 $8 $9
# ./sumppm2.sh $nx $ny s3 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-0 1 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-1 1 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-2 1 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v1-3 1 1 1 $type $4 $5 $6 $7 $8 $9

./sumppm2.sh $nx $ny v2-0 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 1 0 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-0 1 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-1 1 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-2 1 1 1 $type $4 $5 $6 $7 $8 $9
./sumppm2.sh $nx $ny v2-3 1 1 1 $type $4 $5 $6 $7 $8 $9

echo end
