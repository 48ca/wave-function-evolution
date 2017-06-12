# Quantum State Evolution
## Installation
Execute `cmake .` in the root of the project to generate the Makefile.
To compile the code, run `make`.  
The binary produced is `evolve` and symlinks are created to alias `-m` switches. `evolvequ` behaves like `evolve -m s`, and `evolvewv` behaves like `evolve -m c`.  
To install the code for the entire system, run `make install` after running `make`.
## Post-installation
To clean CMake installation files, you can use `clean_cmake.sh`.
## Options
Passing `-DNO_QUADMATH=TRUE` to cmake will prevent linkage to libquadmath.  
Passing `-DNO_OPENMP=TRUE` to cmake will prevent parallelization of evolution. This is recommended for laptops.
## Plotting
The plotting code is in the `plot/` folder. To install the code, make sure you have virtualenv and Tkinter installed on the system and run `install_plot.sh`. After this is done, you can run `./plot.py <filename>` to plot the output of the C++ code that performed the evolution. For example: `./plot.py ../out.txt`.
