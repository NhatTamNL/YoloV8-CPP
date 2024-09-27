# gen Makefile
cmake . -Wno-dev

# Compile
make

# Remove cache
rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt main.o

# mkdir build
mv Yolov8CPPInference build/Yolov8CPPInference

# Run 
# ./build/Yolov8CPPInference