# Cabe
Text editor

# Building

Clone the repository with all the submodules:

```console
git clone --recurse-submodules https://github.com/grx6741/Cabe.git
```

Switch the imgui submodule to docking branch:

```console
cd imgui
git checkout docking
cd ..
```

Now invoke Cmake to generate the build files:

```console
cmake -B build -S .
```

Finally, build the project:

```console
cmake --build build
```

Build binaries will be located in `build/src` directory.

# Running

```console
build/src/Cabe.exe # Windows
./build/src/Cabe # Linux
```

# TODO

[ ] Gap Buffers
[ ] Rope
[ ] Config with toml
[ ] Show only file names on the tabs
[ ] Tests with cmake
[ ] test on Linux