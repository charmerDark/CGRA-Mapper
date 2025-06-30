clang-12 -emit-llvm -fno-unroll-loops -O0 -o saxpy.bc -c saxpy.cpp
llvm-dis-12 saxpy.bc -o saxpy.ll
