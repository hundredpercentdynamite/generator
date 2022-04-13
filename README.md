# Macos build
1. Set path to Qt5 into CMAKE_PREFIX_PATH variable in CMakeLists.txt
2. mkdir release
3. cd ./release
4. cmake -DCMAKE_BUILD_TYPE=Release ..
5. cmake --build .
6. cmake --install . --prefix {install_path}

# Windows build
Suffer with visual studio