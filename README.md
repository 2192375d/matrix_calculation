# matrix_calculation
This is a quick source code of C++ with a bunch of functionalities for matrix calculation stuffs

# how to start?
run the following commands to get build directory


``` bash
mkdir -p build && cd build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug - DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

Once build directory is present, inside the build directory run this to compile and run the program
```bash
cmake --build . -j
./linalg_repl
```
