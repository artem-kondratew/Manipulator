#!/bin/sh


target_dir=/usr/local/bin
cd $target_dir
rm -rf Manipulator
git clone https://github.com/artem-kondratew/Manipulator.git
cd Manipulator/App
cmake CMakeLists.txt
make
cp Manipulator $target_dir/manipulator
cd $target_dir
touch $target_dir/connect-manipulator
touch $target_dir/c
echo "$target_dir/manipulator" > $target_dir/connect-manipulator
echo "$target_dir/manipulator" > $target_dir/c
cd $target_dir
chmod a+x ./c
chmod a+x ./connect-manipulator
echo "*---------------------------*"
echo "USAGE: connect-manipulator"
echo "USAGE: c"
echo "*---------------------------*"
