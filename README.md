<pre>
========================================================

  _____________  ___     __  ___                      
 / ___/ ___/ _ \/ _ |   /  |/  /__ ____  ___  ___ ____
/ /__/ (_ / , _/ __ |  / /|_/ / _ `/ _ \/ _ \/ -_) __/
\___/\___/_/|_/_/ |_| /_/  /_/\_,_/ .__/ .__/\__/_/   
                                 /_/  /_/             

========================================================
</pre>

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

Fork of tancheng's [CGRA-Mapper](https://github.com/tancheng/CGRA-Mapper) for benchmarking [tetricks](https://github.com/charmerDark/tetricks) tensor compiler for CGRAs. Please find the original documentation below.


This is a CGRA (Coarse-Grained Reconfigurable Architecture) mapper to map the target loops onto the CGRA. The CGRA is parameterizable (e.g., CGRA size, type of the computing units in each tile, communication connection, etc.). Different advanced mapping strategies are built on top of this basic mapper. CGRA Mapper currently provides following features and functionalities:
- It takes the arch&kernel info in `JSON` format. 
- It can generate the DFG/CDFG of the target code region (in `.png`).
- Nested-loop and complex if/else control flows are supported with [partial predication](https://dl.acm.org/doi/abs/10.1145/2593069.2593100).
- Users can easily invoke loop-unrolling in the compile/run script (`opt --loop-unroll --unroll-count=4 -load PATH/libmapperPass.so -mapperPass kernel.bc`).
- It schedules and maps the DFG onto the CGRA arch that is represented in [MRRG](https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=1188678).
- The generated dfg.json and config.json can be taken as inputs for the simulation in the [OpenCGRA](https://github.com/tancheng/OpenCGRA) (register index needed to be manually added/distinguished).
- Benchmark including a set of representative kernels/applications with compilation scripts can be found [here](https://github.com/tancheng/CGRA-Bench).

Docker
--------------------------------------------------------
The docker image is available [here](https://hub.docker.com/layers/cgra/cgra-flow/demo/images/sha256-7ca327d24f555376d91cba6fa30e3fbaa4a4c0d4053a82ac9059c374a3dee5bd?context=repo).

### Build Docker image from Dockerfile
```shell
$ mkdir -p ${HOME}/cgra
$ cd ${HOME}/cgra
$ git clone https://github.com/tancheng/CGRA-Mapper.git
$ cd CGRA-Mapper/docker/
$ docker build -t cgramapper:v1 .
```

### Run Docker container
```shell
$ docker run --name mycgramapper cgramapper:v1 &
$ docker exec -it mycgramapper bash
```

### Run test in Docker container
```shell
root@host:/# cd /root/cgra/CGRA-Mapper/test/nonlinear/
root@host:/# sh compile.sh
root@host:/# sh run.sh
root@host:/# sh verify.sh
```
```shell
Nonlinear Test Pass!
```


Showcase
--------------------------------------------------------

```
// target FIR kernel
for (i = 0; i < NTAPS; ++i) {
    sum += input[i] * coefficient[i];
}
```
<p float="center">
  <img src="https://github.com/tancheng/CGRA-Mapper/blob/master/docs/fir_dfg.png" width="400" />
  <img src="https://github.com/tancheng/CGRA-Mapper/blob/master/docs/fir_map.png" width="230" /> 
</p>


Citation
--------------------------------------------------------------------------
```
@inproceedings{tan2020opencgra,
  title={OpenCGRA: An Open-Source Unified Framework for Modeling, Testing, and Evaluating CGRAs},
  author={Tan, Cheng and Xie, Chenhao and Li, Ang and Barker, Kevin J and Tumeo, Antonino},
  booktitle={2020 IEEE 38th International Conference on Computer Design (ICCD)},
  pages={381--388},
  year={2020},
  organization={IEEE}
}
```


License
--------------------------------------------------------------------------

CGRA-Mapper is offered under the terms of the Open Source Initiative BSD 3-Clause License. More information about this license can be found here:

  - http://choosealicense.com/licenses/bsd-3-clause
  - http://opensource.org/licenses/BSD-3-Clause


Build
--------------------------------------------------------

The mapper requires the following additional prerequisites:

 - LLVM 12.0
 - CMAKE 3.1

```
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
```

Execution
--------------------------------------------------------
- The pass should be built and run with the same version of the LLVM.

- A [param.json](https://github.com/tancheng/CGRA-Mapper/blob/master/test/param.json#L24) indicating the configuration of the target CGRA and the kernel should locate in the kernel folder. Explaination of each field in the [param.json](https://github.com/tancheng/CGRA-Mapper/blob/master/test/param.json#L24):
  - [kernel](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L2): indicating the [function name](https://github.com/tancheng/CGRA-Bench/blob/8f3f20167883680735d1d79cd6f2c1439c999950/kernels/fir/fir.ll#L33) shown in the generated IR file. Note that different versions of LLVM could lead to different generated function names, which should be explicitly indicated in the `param.json` by the users.
  - [targetFunction](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L3): whether targeting the entire function or only the loop. Set it as `false` as CGRA mainly focus on loop acceleration.
  - [targetNested](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L4): whether targeting nested loop or not. For now, the nested loop is therotically supported but not efficient. Set it as `false` to target the inner-most loop.
  - [targetLoops](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L5): indicating the loops need to be mapped/accelerated. One function might contains multiple loops. However, for now, we can only target single loop. So this field can be set as `[loopID]` (e.g., `[0]` or `[1]`). If it is set as `[0, 1]`, the first loop (i.e., loop `0`) will be selected.
  - [doCGRAMapping](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L6): indicating whether the mapping is performed. If you only care about the statistics (e.g., number of nodes/edges, loop-carry dependency length, number of loop-carry dependencies) of the loop DFG without mapping, this field can be set as `false`.
  - [row](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L7): the number of rows in the CGRA.
  - [column](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L8): the number of columns in the CGRA.
  - [precisionAware](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L9): whether distinguishing floating-point computation from fixed-point computation.
  - [heterogeneity](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L10): deprecated. Set as `false` and ignore it.
  - [isTrimmedDemo](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L11): simplifying the generated DFG (`.dot`).
  - [heuristicMapping](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L12): `true` indicates heuristic mapping while `false` indicates exhaustive mapping. The heuristic mapping runs much faster than the exhaustive one but cannot guarantee an optimal solution.
  - [parameterizableCGRA](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L13): used to integrate with [CGRA-Flow](https://github.com/tancheng/CGRA-Flow). Set as `false` by default.
  - [diagonalVectorization](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L14): `true` indicates half of the tiles (e.g., in a 16-tile CGRA, tile0, tile2, tile4, ..., tile14) additionally support vectorized operations, while `false` means all the tiles support vectorized operations. If the target function doesn't contain any vectorized operation, `true` or `false` in this field doesn't make any difference.
  - [bypassConstraint](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L15): Additional constraint to limit the max number of data streams can go through a router/crossbar simultaneously in one cycle. Normally, this field should be set as the number of ports on the crossbar (e.g., 2 for a ring, 4 for a mesh, and 8 for a king-mesh).
  - [isStaticElasticCGRA](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L16): used to map a kernel/DFG on the [Ultra-Elastic CGRA](https://ieeexplore.ieee.org/abstract/document/9407079). Set as `false` by default.
  - [ctrlMemConstraint](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L17): should be set as II (at least). So a larger number is prefered, which probably leads to a valid mapping solution.
  - [regConstraint](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L18): the number of registers used to temporarily hold the arrived data for later computation. Set as 8 by default.
  - [optLatency](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L19): used to support multi-cycle execution. If this field is not specified, every operation is done in one single-cycle. Note that there is currently no hardware support for this feature, which is supposed to be used for performance exploration only.
  - [optPipelined](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L23): used to enable pipelined execution of the multi-cycle operation (i.e., indicated in [optLatency](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L19)).
  - [additionalFunc](https://github.com/tancheng/CGRA-Mapper/blob/589fd61434966e4d4a44220b59854b1795bc7cde/test/param.json#L24): used to enable specific functionalities on target tiles. Normally, we don't need to set this field as all the tiles already include most functionalities. By default, the `ld`/`st` is only enabled on the left most tiles. So if you wanna enable the memory access on the other tiles, this field needs to be provided. 
  - [incrementalMapping](https://github.com/yyan7223/CGRA-Mapper/blob/10aa217e9e995b6dfa4242e0ce121b79668e9995/test/param.json#L28C1-L28C33) `true` indicates incremental mapping while `false` indicates heuristic/exhaustive mapping. Incremental mapping re-utilizes the previous mapping results of current kernel (e.g., on 4x4 CGRA) to accelerate its mapping on the new resource allocation decisions (e.g., on 5x5 CGRA). To simply check the acceleration effect of incremental mapping, calls heuristic mapping first to generate `increMapInput.json` for current kernel on 4x4 CGRA, then sets incrementalMapping to `true` and performs mapping on 5x5 CGRA again, finally checks the elapsed time differences. 
  
- Run:
```
 % opt -load ~/this repo/build/mapper/libmapperPass.so -mapperPass ~/target benchmark/target_kernel.bc
```

Related publications
--------------------------------------------------------------------------

- Cheng Tan, et al. _“DynPaC: Coarse-Grained, Dynamic, and Partially Reconfigurable Array for Streaming Applications.”_ The 39th IEEE International Conference on Computer Design. (ICCD'21), Oct 2021.
- Cheng Tan, et al. _“OpenCGRA: Democratizing Coarse-Grained Reconfigurable Arrays.”_ The 32nd IEEE International Conference on Application-specific Systems, Architectures and Processors (ASAP'21), A Virtual Conference, July 7-8, 2021.
- Cheng Tan, et al. _"ARENA: Asynchronous Reconfigurable Accelerator Ring to Enable Data-Centric Parallel Computing."_ IEEE Transactions on Parallel and Distributed Systems (TPDS'21).
- Cheng Tan, et al. _“AURORA: Automated Refinement of Coarse-Grained Reconfigurable Accelerators.”_ The 2021 Design, Automation & Test in Europe Conference, Grenoble, France. (DATE'21) February 1-5, 2021.
- Christopher Torng, et al. _"Ultra-Elastic CGRAs for Irregular Loop Specialization."_ 2021 IEEE International Symposium on High-Performance Computer Architecture (HPCA'21).
