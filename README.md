# Simulator

## build
```
cmake -B build_x64 -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=Output
cmake --build .\build_x64\
cmake --install .\build_x64\
```

执行上述命令后，Output/bin将会有两个可执行文件，分别运行主程序和测试程序，OpenGL目录下为封装的渲染功能
