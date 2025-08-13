Check the C files in this project root for example code.

Check the .bat files to see how to build.

There is 3 examples here:
- Just loading in a resource file at runtime - the typical way you probably expect. This is just here for comparison with other methods
- Using the Windows `rc.exe` program to convert a resource file into a compiled resource for linking
- Using `objcopy` program to convert a resource file into a .o file for linking
  - I used an objcopy distributed with winlibs MINGW64, though you can probably use the equivelant objcopy unix utility on unix-like toolchains and workflows
