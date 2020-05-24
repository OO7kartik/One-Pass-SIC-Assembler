# One-Pass-SIC-Assembler
One Pass SIC Assembler written in C++

# Files
    ├── assembler  (Executable for Linux)
    ├── assembler.cpp (Source Code in C++)
    ├── assembler.exe (Executable for windows)
    ├── Files
    │   ├── input_program.txt (Example input SIC program)
    │   └── optab.txt   
    ├── headers
    │   ├── Optab.hpp
    │   ├── parser.hpp
    │   ├── Symtab.hpp
    │   └── Utils.hpp
    ├── output.txt (Output object program)
    └── README.md

# About
assembler.cpp converts SIC program to corresponding object program

assembler.cpp executable takes in two arguments ```<INPUTFILE>``` and ```<OUTPUTFILE>```

by default 
            
```<INPUTFILE> = 'Files/input_program.txt'``` (input program in SIC)

```<OUTPUTFILE> = 'output.txt'``` (output object program)

## Usage
To compile:
```
g++ assembler.cpp -o assembler 
```

To run: 

windows:  

    assembler.exe <INPUTFILE> <OUTPUTFILE>

linux:     

    ./assembler <INPUTFILE> <OUTPUTFILE>

example for default program,

windows: 
> assembler.exe Files/input_program.txt output.txt

linux: 
> ./assembler Files/input_program.txt output.txt

## Notes
 - Forward refrences for <strong>Data</strong> symbols are prohibited.  
 - The first source line must be "START" line.