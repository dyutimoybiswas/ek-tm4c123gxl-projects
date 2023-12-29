# Execute this script to generate bin file. Provide project directory name as argument.

PROJ_DIR=$1
cd $PROJ_DIR
rm -rf build
mkdir build && cd build
cmake ..
make