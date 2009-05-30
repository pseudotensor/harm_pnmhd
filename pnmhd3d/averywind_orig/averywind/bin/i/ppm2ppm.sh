#!/bin/sh
#
# probably had to do this since kept in rgb, need ppm: (but can't with pipe)
# could use ppm2fli to use convert to pipe anything
for fil in `/bin/ls frame????.ppm.gz`
do
        prefa=`echo $fil | sed "s/\./ /"`
        pref=`echo $prefa | awk '{print $1}'`
        echo $pref
        convert $pref.ppm.gz - | gzip -cf > $pref.new.ppm
        echo $pref done
done
