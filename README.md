# MuJoCo_Template

### Template Repo for Cross-platform both in macOS and ubuntu
* CMakeLists.txt의 핵심은 submodule, add_subdirectory, CMAKE_MODULE_PATH 추가.

```console
/* Follow instruction explained in libraries dir README.md first */
$ mkdir build && cd build
$ cmake ..
$ make -j16

$ ./bin/simulate or ./bin/template
```