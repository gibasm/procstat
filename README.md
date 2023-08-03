# procstat - cli cpu usage utility

procstat is a small terminal utlity for presenting the CPU utilization on GNU/Linux

# Building

## Prerequisites:

- C compiler (clang or gcc) with C23 support

- CMake

- GNU Make / Ninja

## Steps:

1. Clone this repository

2. Create a build directory and cd into it

```
mkdir build
cd build
```

3. Run CMake:

- for clang:

```
cmake .. -DCMAKE_C_COMPILER=clang
```

- for gcc:

```
cmake .. -DCMAKE_C_COMPILER=gcc
```

4. Run make:

```
make -j`nproc`
```

5. To run the app:

```
./src/pstat
```

* to stop the app use the following key combination: CTRL+C

6. To run tests:

```
./src/tests/test
```
