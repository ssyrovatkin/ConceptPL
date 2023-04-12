#### Notation:
* R... - register
* [R...] - register value as an address in memory
* V... - int32 value
* U... - int16 value

#### Special register names, supported by assembler
* `PC = 33` - program counter
* `SP = 34` - stack pointer
* `FLG = 35` - flags register
* `LR = 30` - link register (x30)

### VM commands
* `mov Rx, Vy`: Rx <- Vy
* `movr Rx, Ry`: Rx <- Ry
* `sub Rx, Ry, Rz`: Rx <- Ry - Rz
* `add Rx, Ry, Rz`: Rx <- Ry + Rz

* `print Vx, Us`: print memory[Vx:Vx+Us] values to console
* `print_s Rx, Ry`: print memory[Rx:Rx+Ry] values to console
* `print_r Rx`: print Rx value to console
* `print_c Rx`: print Rx value to console as a char
* `inp Rx`: read value from console to Rx

* `EXIT`: end execution

* `b Vx`: PC <- Vx
* `bl Vx`: LR <- PC, PC <- Vx
* `cmp Rx, Ry`: write comparison result (Rx - Ry) to FLG
* `bLE Vx`: check FLG,  if <= 0 PC <- Vx
* `bEQ Vx`: check FLG,  if == 0 PC <- Vx

* `str Rx, [Ry]`: store Rx in memory at address=Ry value
* `load Rx, [Ry]`: load value from memory at address=Ry value and put into Rx

* `ret`: PC <- LR
* `loadstr Rx, Ry, Ux, Uy`: Rx <- Ux, Ry <- Uy

### Assembler commands
* `mov Rx, Vy`: Rx <- Vy
* `movr Rx, Ry`: Rx <- Ry
* `sub Rx, Ry, Rz`: Rx <- Ry - Rz
* `add Rx, Ry, Rz`: Rx <- Ry + Rz

* `print <string>`: print \<string> to console
* `print_s Rx, Ry`: print memory[Rx:Rx+Ry] values to console
* `print_r Rx`: print Rx value to console
* `print_c Rx`: print Rx value to console as a char
* `inp Rx`: read value from console to Rx

* `EXIT`: end execution

* `b .<label>`: jump to .\<label>
* `bl .<label>`: jump to .\<label> with saving return address in LR
* `cmp Rx, Ry`: write comparison result (Rx - Ry) to FLG
* `bLE .<label>`: check FLG,  if <= 0 jump to .\<label>
* `bEQ .<label>`: check FLG,  if == 0 jump to .\<label>

* `str Rx, [Ry]`: store Rx in memory at address=Ry value
* `load Rx, [Ry]`: load value from memory at address=Ry value and put into Rx

* `ret`: jump to return address (saved in LR)

* `loadstr Rx, Ry, <string>`: save \<string> in memory, Rx <- string address, Ry <- string size 


