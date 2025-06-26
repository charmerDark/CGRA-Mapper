clang-12 -emit-llvm -fno-unroll-loops -O3 -o mattransmul.bc -c mattransmul.cpp
llvm-dis-12 mattransmul.bc -o mattransmul.ll
