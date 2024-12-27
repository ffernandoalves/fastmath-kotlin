# fastmath
---

Implementation of a simple matrix multiplication API in C for Kotlin using JNI

Compile
```bash
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
$ cmake --build build
$ kotlinc src/Main.kt -include-runtime -d out/Main.jar
```

Execute
```bash
$ cd out
$ java -jar Main.jar
```