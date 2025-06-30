clang-12 -emit-llvm -fno-unroll-loops -O0 -o ttm.bc -c ttm.cpp
llvm-dis-12 ttm.bc -o ttm.ll
