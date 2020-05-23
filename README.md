# One-Pass-SIC-Assembler
One Pass SIC Assembler written in C++

## Usage
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