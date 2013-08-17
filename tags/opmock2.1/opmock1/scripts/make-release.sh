#!/bin/sh

# make a binary release of the Java parts of opmock 
# plus support files and samples files.
# To be uploaded later on sourceforge.

HERE=`pwd`
cd $HOME
rm -rf opmock
mkdir $HOME/opmock
cd $HERE
cd ..
cp -rf ./support $HOME/opmock
cp -rf ./documentation $HOME/opmock
cp -rf ./samples $HOME/opmock
cp scripts/opmock.sh $HOME/opmock
cp scripts/refresh_tests.sh $HOME/opmock
cp *.txt $HOME/opmock
mvn clean && mvn package
cp target/opmock*.jar $HOME/opmock/opmock.jar

#remove .svn folders
find $HOME/opmock -name '.svn' -exec rm -rf {} \;
find $HOME/opmock -name '*~' -exec rm -f {} \;

cd $HOME
tar czf opmock-0.9.2.tgz opmock
