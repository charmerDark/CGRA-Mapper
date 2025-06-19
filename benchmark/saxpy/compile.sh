clang-12 -emit-llvm -fno-unroll-loops -O3 -o saxpy.bc -c saxpy.cpp
#llvm-dis saxpy.bc -o saxpy.ll
