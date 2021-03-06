# MicroVM
A very small 16 bit VM loosely based on the [P'' formal language](https://en.wikipedia.org/wiki/P′′).

## Features
* MicroVM supports 16 bit addresses.
* The MicroVM word is 2 bytes, it is the smallest piece of memory that can be referenced in MicroVM.
* MicroVM supports a native language with assembly like mnemonics, unlike P'' and its own six symbol language.
* MicroVM has more operators than P''.
* MicroVM is capable of IO unlike the origional P''.
* MicroVM is turing complete by design.

MicroVM's memory is made up to 65536 (or 2<sup>16</sup>) cells, each cell can hold two bytes.
Some operations allow you to move the reading head (also called the memory counter) allowing you to read and write to/from a specific cell.

# Specifications
Memory: 131 kb (131072 b)

## Registers
Registers store data temporarily.

|Register|Size|
|---|---|
|Program counter|2 bytes|
|Memory counter|2 bytes|
|Instruction Register|4 bytes|

**Note**: Instruction register requires 4 bytes to store a 2 byte opcode and a 2 byte operand.

## Flags
Flags are boolean values which are set on/off based on certain conditions.

|Flag|Size|Condition|
|---|---|---|
|Zero flag|2 bytes|Set to 1 when CPZ encounters a memory cell with value 0, set to 0 otherwise|
|Jump flag|2 bytes|Temporarily set to 1 by jump operations, set to 0 during program cycle|
|Error flag|2 bytes|Set to 1 when a fatal error occurs, 0 otherwise|
|Halt flag|2 bytes|0 by default, set to one by HLT instruction, causes the VM to halt|

## Operators
Heres is a list of supported operators and their opcodes.

|OPCODE|Operator|Hex|Effect|
|---|---|---|---|
|NOP|No operation|0x0|No effect|
|NXT|Next cell|0x1|Moves memory counter forward by one|
|PRV|Previous cell|0x2|Moves memory counter backwards by one|
|INC|Increment|0x3|Increments current cell|
|DEC|Decrement|0x4|Decrements current cell|
|JMP|Jump|0xB|Jumps to address in next cell|
|CPZ|Zero check|0x9|Checks if current cell is zero, sets zero flag to 1 on success, 0 on failure|
|JEZ|Jump if zero|0x5|Equivalent to JMP otherwise but only jumps if zero flag is 1|
|JNZ|Jump if not zero|0x6|Equivalent to JMP otherwise but only jumps if zero flag is 0|
|JMM|Jump cell|0xC|Set memory counter to address in next cell|
|DSP|Display|0x7|Outputs current cell to screen|
|LDS|Load from screen|0x8|Loads data to cell|
|HLT|Halt|0xA|Sets halt flag to 1, this causes the VM to halt|
|PUT|Put character|0xD|Put the ASCII character corresponding to value at current memory cell on screen|
