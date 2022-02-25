# raylib-gui
Simple gui code for the raylib library

## Used libraries
The following libraries are used to compile the project
- [raylib](https://www.raylib.com/)

## About compiling
### Raylib
The project was made to be compiled on Windows via WSL.  

The raylib library was compiled with `x86_64-w64-mingw32-gcc` on WSL with the help of this [tutorial](http://bedroomcoders.co.uk/looking-again-at-compiling-a-windows-raylib-app/).  

### The project
The actual project is then compiled with `x86_64-w64-mingw32-g++`.  

It seems to be a bad idea to not compile raylib and the project with the same compiler, but it works. Using the g++ compiler on raylib was throwing a bunch of errors and I did not bother looking into it.

A full Linux makefile will follow, for now just do
- `ln -s Makefile.win Makefile`  

to be able to use *make*.
