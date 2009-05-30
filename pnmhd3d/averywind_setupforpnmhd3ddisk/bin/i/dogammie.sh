cd ./$1/images/
LIMIT=9
first="im"
second="p????.r8.gz"
p=0
while [ $p -le "$LIMIT" ]
do
echo -n "$p "
#ls "im $p p????.r8.gz" > im.lst
ls $first$p$second > im.lst
# below with no header
#ppm2fli -p /home/jon/research/current/bin/i/john.pal -N -g $2'x'$3 -z $2'x'$3 -s 0 im.lst $1-$p.fli
ppm2fli -p /home/jon/research/current/bin/i/john.pal -N -g $2'x'$3 -s 0 im.lst $1-$p.fli < ../../y.txt
p=$(($p+1))
done
