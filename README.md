# One-Pass-SIC-Assembler
One Pass SIC Assembler written in C++

# About
assembler.cpp converts SIC program to corresponding object program

assembler.cpp executable takes in two arguments ```<INPUTFILE>``` and ```<OUTPUTFILE>```

by default 
            
```<INPUTFILE> = 'Files/input_program.txt'``` (input program in SIC)

```<OUTPUTFILE> = 'output.txt'``` (output object program)

## Usage
### Default I/O program
To run
```
make 
```

### Custom I/O program
To compile:
```
g++ assembler.cpp -o assembler 
```

To run:  
```     
./assembler <INPUTFILE> <OUTPUTFILE>
```
For example,
```
./assembler Files/input_program.txt output.txt
```

## Notes
 - Forward refrences for <strong>Data</strong> symbols are prohibited.  
 - The first source line must be "START" line.