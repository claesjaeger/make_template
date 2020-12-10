# Makefile template project for C and C++
This is a small make project where you can add source files without adding them to the make file directly.

1. Select if the project is C or C++
2. change the name of the main file in the project
3. Update the libraries you are using in your project

## Setup
You have to edit the following options in the `makefile` to compile your project
```
# Select Cor C++. [c, c++]
PROJECT = c
# define the executable file 
MAIN = weathercollect
```
### Libs
Remember to add the libraries you use to the `LIBS` variable
```
# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm -lreadline
```
