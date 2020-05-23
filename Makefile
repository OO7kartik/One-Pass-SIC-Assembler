ifeq ($(OS),Windows_NT)
    all:
		assembler.exe Files/input_program.txt output.txt
else
    all:
		./assembler Files/input_program.txt output.txt
endif