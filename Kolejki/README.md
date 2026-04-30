# Projekt kolejek priorytetowych

Do kompilacji dla linuxa
```bash
mkdir build_linux
cmake -B build_linux -DTARGET_OS=linux
cd build_linux 
make
```

Do kompilacji dla windows
```bash
mkdir build_windows
cmake -B build_windows -DTARGET_OS=windows -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_SYSTEM_NAME=Windows
cd build_windows
make
```