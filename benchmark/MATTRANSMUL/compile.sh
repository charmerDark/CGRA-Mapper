clang-12 -emit-llvm -fno-unroll-loops -O0 -o mattransmul.bc -c mattransmul.cpp
llvm-dis-12 mattransmul.bc -o mattransmul.ll
