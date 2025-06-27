clang-12 -emit-llvm -fno-unroll-loops -O3 -o gemm.bc -c gemm.cpp
llvm-dis-12 gemm.bc -o gemmm.ll
