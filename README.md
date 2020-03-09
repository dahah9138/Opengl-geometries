# Opengl-geometries

This project mainly comprises of basic geometries written for opengl.

It is highly recommended to compile this code using visual studios.

This code has only been tested on a PC. Unknown behaviors will likely arise on linux and mac.

Installation:

1. Create an empty vs project to place all the code

2. Copy all the headers and .cpp files into the main directory

3. Unzip the deps folder in the solution directory

4. In VC++ Directories, add the following paths:

$(SolutionDir)deps/include

$(SolutionDir)

5. In Linker, add the following to 'Additional Library Directories':

$(SolutionDir)deps/lib

6. Go back to the main VS interface. With that done, you should be able to click "Local Windows Debugger" and get some code on the screen.
