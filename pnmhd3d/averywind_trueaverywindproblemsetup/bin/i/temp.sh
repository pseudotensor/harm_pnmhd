#
# set size of array
echo start
nx=$1
ny=$2

#./sumppm.sh $nx $ny s1 0 0
./sumppm.sh $nx $ny s2 0 0
./sumppm.sh $nx $ny s1 0 1
./sumppm.sh $nx $ny s2 0 1
./sumppm.sh $nx $ny s3 0 0
./sumppm.sh $nx $ny v1-0 0 0
./sumppm.sh $nx $ny v1-1 0 0
./sumppm.sh $nx $ny v1-2 0 0
./sumppm.sh $nx $ny v1-3 0 0
./sumppm.sh $nx $ny v1-0 0 1
./sumppm.sh $nx $ny v1-1 0 1
./sumppm.sh $nx $ny v1-2 0 1
./sumppm.sh $nx $ny v1-3 0 1

./sumppm.sh $nx $ny s1 1 0
./sumppm.sh $nx $ny s2 1 0
./sumppm.sh $nx $ny s1 1 1
./sumppm.sh $nx $ny s2 1 1
./sumppm.sh $nx $ny s3 1 0
./sumppm.sh $nx $ny v1-0 1 0
./sumppm.sh $nx $ny v1-1 1 0
./sumppm.sh $nx $ny v1-2 1 0
./sumppm.sh $nx $ny v1-3 1 0
./sumppm.sh $nx $ny v1-0 1 1
./sumppm.sh $nx $ny v1-1 1 1
./sumppm.sh $nx $ny v1-2 1 1
./sumppm.sh $nx $ny v1-3 1 1

echo end
