# MicroVM
A very small  VM loosely based on the [P'' formal language](https://en.wikipedia.org/wiki/P′′).

## Features
* MicroVM supports 16 bit addresses.
* The MicroVM word is 2 bytes, it is the smallest piece of memory that can be referenced in MicroVM.
* MicroVM supports a native language with assembly like mnemonics, unlike P'' and its own six symbol language.
* MicroVM has more operators than P''.
* MicroVM is capable of IO unlike the origional P''.
* MicroVM is turing complete by design.

# Specifications
Memory: 131 kb (131072 b)

## Registers
Registers store data temporarily.

|Register|Size|
|---|---|
|Program counter|2 bytes|
|Memory counter|2 bytes|
|Instruction Register|4 bytes|

**Note**:Instruction register requires 4 bytes to store a 2 byte opcode and a 2 byte operand.

## Flags
Flags are boolean values which are set on/off based on certain conditions.

|Flag|Size|Condition|
|---|---|---|
|Zero flag|2 bytes|Set to 1 when CPZ encounters a 0 operand, set to 0 otherwise.|
|Jump flag|2 bytes|Temporarily set to 1 by jump operations, set to 0 during program cycle.|
|Error flag|2 bytes|Set to 1 when a fatal error occurs, 0 otherwise.|
|Halt flag|2 bytes|0 by default, set to one by HLT instruction, causes the VM to halt.|

## Operators
Heres is a list of supported operators and their opcodes.

|OPCODE|Operator|Hex|Effect|
|---|---|---|---|
|NOP|No operation|0xC|No effect|
|NXT|Next cell|0x0|Moves memory counter forward by one|
