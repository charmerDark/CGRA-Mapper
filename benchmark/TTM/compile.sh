clang-12 -emit-llvm -fno-unroll-loops -O3 -o ttm.bc -c ttm.cpp
llvm-dis-12 ttm.bc -o ttm.ll
