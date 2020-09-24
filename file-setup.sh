# @Author: Nick Steele <nichlock>
# @Date:   21:40 Sep 18 2020
# @Last modified by:   nichlock
# @Last modified time: 19:07 Sep 19 2020

echo Copying files...
cd $temporary_package_directory
mkdir /images

# Copy your packages here
# cp -r opencv_ch2/hsv_set $final_package_directory/[package_name]

# Copy our catkin Makefile
cp -r catkin-setups/Makefile $final_package_directory/../Makefile
