# Execute this script to generate bin file.

PROJ_DIR=$1
cd $PROJ_DIR
rm -rf build
mkdir build && cd build
cmake ..
make