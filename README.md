# CAD-Contest-Problem-A

## Authors
b08901061 Yung-Chin, Chen  
b08901062 Chia-Hsiang, Chang  
b08901048 Yu-Chen, Chen  
Department of Eletrical Engineering, National Taiwan University

## Files
```
project
|   README.md
|   final_presentation.pptx
|   report.pdf
|   a.exe
|---src
|   |   main.cpp
|   |   Compare_pattern.cpp
|   |   Compare_pattern_ctrl.cpp
|   |   deleteBuf.cpp
|   |   deleteNot.cpp
|   |   evaluate.cpp
|   |   find_ctrl.cpp
|   |   findSubgraph.cpp
|   |   graph2rtl.cpp
|   |   graphReduction.cpp
|   |   netlist2graph.cpp
|   |   Pattern_Controller.cpp
|   |   PQM.cpp
|   |   SubCircuitEC.cpp
|   |   (Corresponding .h files)
|---release
|   |---test01
|   |   |   top_primitive.v
|   |---test02
|   |   |   top_primitive.v
|   |   ...
|   |---test20
|   |   |   top_primitive.v
|---references
|   |   (The reference papers)
```

## Compile
In the root file, run below command in command line to compile the c++ files:
```
$ g++ src/*.cpp
```
The generated .exe file is originally attached in this directory.

## Run
Run the generated .exe file:
```
$ a.exe
```
and type the number of test case which is going to be tested:
```
which test case?
06
```
The available numbers of test cases are 01~20. Note that for the first 9 test cases, we should type 01, 02, ..., 09.

## Result
The related information should be printed in the command line, such as deleted buf, deleted dummy not, reduction rate and completing messages.  
The output Verilog file `Top.v` is generated in the root directory.