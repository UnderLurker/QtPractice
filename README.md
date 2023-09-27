# 项目介绍
这是一个用clion来写qt的项目，用此项目来学习qt和cmake
# 目录结构
我的目的是越复杂越好，因为写CMakeLists.txt就更多，可以练。可以说<strong>不求简单只求复杂</strong><br>

此项目只使用test中的文件，Sources里的只是摆设（当然Sources里的是可以运行的）
# 运行
如果你想运行此项目，只需要将根目录里的CMAKE_PREFIX_PATH设置为你qt安装目录mingw/lib/cmake即可，<br>
例如，我项目里设置的
```c++
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")
```

# 子项目
[<strong>ButtonTest</strong>](./test/ButtonTest/README.md)