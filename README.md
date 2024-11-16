# TOPCOM: Triangulations of Point Configurations and Oriented Matroids

This repository contains the [TOPCOM package](https://www.wm.uni-bayreuth.de/de/team/rambau_joerg/TOPCOM/index.html), developed by Jörg Rambau. The [upstream branch](https://github.com/ariostas/TOPCOM/tree/upstream) contains the original code released on the [TOPCOM website](https://www.wm.uni-bayreuth.de/de/team/rambau_joerg/TOPCOM-Downloads/index.html), and other branches include some modifications to allow the implementation of Python bindings. More information and documentation can be found at the [TOPCOM website](https://www.wm.uni-bayreuth.de/de/team/rambau_joerg/TOPCOM/index.html).

## Building and installing

TOPCOM can now be built using CMake. First, generate the build configuration with
```bash
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
```

Optionally, the install location can be specified with
```bash
-D CMAKE_INSTALL_PREFIX=[your custom path]
```

Then, build the package with
```bash
cmake --build build -j 4
```

Optionally, the binaries can then be installed with
```bash
cmake --build build --target install
```

## Usage

Please consult the [TOPCOM website](https://www.wm.uni-bayreuth.de/de/team/rambau_joerg/TOPCOM/index.html) for detailed instructions.


## License

TOPCOM was originally written by Jörg Rambau and is distributed under the GPLv3 license.
