clang-12 -emit-llvm -fno-unroll-loops -O3 -o mttkrp.bc -c mttkrp.cpp
llvm-dis-12 mttkrp.bc -o mttkrp.ll
