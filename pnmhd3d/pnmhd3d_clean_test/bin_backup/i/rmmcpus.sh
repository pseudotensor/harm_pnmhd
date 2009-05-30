#gets all mutiple cpu data(only not zipped)
#command=ls | egrep '\.dat\.....\.r8$' | xargs rm
cd imx0-0-s1
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-s2
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-1-s1
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-1-s2
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-s3
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-1-s3
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-v1-1
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-v1-2
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-v1-3
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-v2-1
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-v2-2
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ../imx0-0-v2-3
ls | egrep '\.dat\.....\.r8$' | xargs rm
cd ..
