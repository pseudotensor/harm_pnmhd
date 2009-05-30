#!/bin/sh
#
# get dir
kftp -i -n <<HERE
         open mss.ncsa.uiuc.edu
         user jmckinne
         cd chandran128-3
         dir >> mssdir.txt
         close
         quit
HERE


#for fil in `cat mssdir.txt`
#do
#    kftp -i -n <<HERE
#         open mss.ncsa.uiuc.edu
#         user jmckinne
#         put $fil
#         chmod 0644 $fil
#         close
#         quit
#HERE
#done

