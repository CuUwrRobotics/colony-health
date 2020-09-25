# @Author: Nick Steele <nichlock>
# @Date:   21:40 Sep 18 2020
# @Last modified by:   Nick Steele
# @Last modified time: 20:32 Sep 24 2020

echo Copying files...
cd $temporary_package_directory
mkdir /images

# Copy your packages here
cp -r colony-health/ $final_package_directory/colony-health

cp -r images/ /

# Copy our catkin Makefile
cp -r catkin-setups/Makefile $final_package_directory/../Makefile
