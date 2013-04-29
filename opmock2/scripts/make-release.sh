#!/bin/sh

# make a binary release of of opmock 
# as a statically linked executable
# plus support files and samples files.

HERE=`pwd`
cd $HOME
rm -rf opmock2
mkdir $HOME/opmock2
cd $HERE
cd ..
cp -rf ./support $HOME/opmock2
cp -rf ./documentation $HOME/opmock2
cp -rf ./samples $HOME/opmock2
cp scripts/refresh_tests.sh $HOME/opmock2
cp *.txt $HOME/opmock2
cp readme $HOME/opmock2
make clean && make
strip opmock2
cp opmock2 $HOME/opmock2/

#remove .svn folders
find $HOME/opmock2 -name '.svn' -exec rm -rf {} \;
find $HOME/opmock2 -name '*~' -exec rm -f {} \;

cd $HOME
tar czf opmock2.0.1-x86_64-linux-min-2.6.8.tgz opmock2
