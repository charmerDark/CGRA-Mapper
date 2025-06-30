clang-12 -emit-llvm -fno-unroll-loops -O0 -o residual.bc -c residual.cpp
llvm-dis-12 residual.bc -o residul.ll
