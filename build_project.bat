rmdir /s /q ".\build"
mkdir build
"C:\Program Files\CMake\bin\cmake.EXE" --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=C:\msys64\ucrt64\bin\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=C:\msys64\ucrt64\bin\g++.exe "-S." "-B./build" -G Ninja
cd build
cmake --build .
cd ..
start .\build\src\application\app.exe