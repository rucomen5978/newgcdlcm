# newgcdlcm


## install
* ubuntu/debian - sudo apt install gcc sdl2
* arch/monjaro  - sudo pacman -S gcc sdl2
* ```bash
  git clone https://github.com/rucomen5978/newgcdlcm
  cd ngl
  g++ main.cpp nglib.h nglf.cpp nglci.cpp ngraphicsl.cpp -o newgcdlcm -lm -lSDL2
  ./newgcdlcm

# console interface:
## use
in the program, all interaction occurs through entering the function name and arguments to them into the console.
the program consists of small functions that take from 1 to 4 arguments (except the first four).
here is the list:

* ex exit cl clear add sub mul div rod gcd lcm pow cos sin tan rd itm tif af00 sf00 mf00 df00 af10 sf10 mf10 df10 af11 sf11 mf11 df11 af01 sf01 mf01 df01 dtf ranum graphics

### program part
* ex exit - exit the program
* cl clear - claar the console

### numbers part
* add - accepts 2 digits and outputs the sum                    (+)
* sub - accepts 2 digits and outputs the difference             (-)
* mul - accepts 2 digits and outputs the product                (*)
* div - accepts 2 digits and outputs the quotient               (/)
* rod - accepts 2 digits and outputs the remainder of division  (%)
* pow - accepts 2 digits and outputs the power                  (^)
* ranum - accepts 2 digits and outputs random number

* gcd - accepts 2 digits and outputs gcd
* lcm - accepts 2 digits and outputs lcm
### example for all listed functions
* ``` ngl
  add 2 2
  4
  sub 2 3
  -1
  mul 4 4
  16
  div 16 8
  2
  rod 36 7
  1
  pow 7 2
  49
  gcd 7 14
  7
  lcm 12 36
  36
  ranum 0 100
  81
### trigonometry part
* cos - takes 1 number and outputs the cosine of the number
* sin - takes 1 number and outputs the sine of the number
* tan - takes 1 number and outputs the tangent of the number

### example
* ``` ngl
  cos 3.14
  -0.999999
  sin 90
  0.893997
  tan 45
  1.61978
### fraction part
* rd  - takes an improper fraction (num and denom) and outputs the reduced num with the denom and gcd of the fraction you entered
* itm - takes an improper fraction and outputs a proper fraction
* tif - takes a proper fraction (integer part, numerator, denominator) and outputs an improper fraction
* af - adds a fraction
* sf mf df - do the same thing as af, only different actions (i.e. sf - subtracts, mf - multiplies, df - divides)
* dtf - takes a decimal fraction and converts it to an improper fraction

### whats for 00 10 11 10?
* the first digit is responsible for entering a fraction, i.e. if the first digit is 1 (10, 11), then the whole fraction will be entered (full part, numerator, denominator).
* if the second digit is 1 (11, 01), then the result will be automatically reduced
* in any case you will get an improper fraction, to convert it to a proper one use "itm"

### what does the last digit in 10 and 00 mean?
* greatest common divisor

### example
* ``` ngl
  af00 1 2 3 4
  5/4 1
  sf00 7 8 1 6
  17/24 1
  mf00 2 5 7 8
  14/40 2
  rd 14 40
  7/20 2
  df00 7 32 2 69
  483/64 1
  itm 483 64
  7 35/64
  tif 6 7 8
  55/8
  dtf 0.44
  11/25
  dtf 0.45
  9/20

# sdl interface
to go to sdl interface you need to enter "graphics", after which you will see a window with a size of 1280 by 720 pixels
so far, there is no particularly strong functionality in si, but it will be added for now, you can create an infinite number of points using the "new" command


### there are two types of objects, simple points and lines that connect these points
#### if you want to interact with dots in some way then at the end of the name of the mnemonic you should add "po" from the word "point"
#### if you want to interact with the lines in some way, then at the end of the name of the mnemonic, you should add "li" from the word "line"
##### also each object has its own indexes. for example, when creating a point, you are given an index of the points, lines will have other indexes
###### also also the indices of all objects start from 1 and not from 0

### mnemonics si:
* newpo - creates a point at the given coordinates (x, y)
* newrapo - creates a point at a random location within a given range (minx, maxx, miny, maxy)
* rpfs - creates a point at a random location within the window size range 
* edipo - creates a point at the given coordinates, displays it, and gives it an index (index, newx, newy)
* newli || nl - creates a line between two points, displays it, and creates a special line index (indexp1, indexp2)
* infoli - shows line data through its index (indexli)
* pali - Prints All LInes (meaning all that exist and all their data)
* infopo - shows point data through its index (indexpo)
* papo - Prints All POints (meaning all that exist and all their data)
* eci - Enable Console Interface (nglci in si)
* delpo - DELete POint (indexpo)
* cap - Connect All Points
* dpal - Delete Points And Lines
* lrpfs - Loop RPFS (count, delay)
* lnewrapo - Loop NEWRAPO (count, delay, minx, maxx, miny, maxy)
* lrpfscap - Loop RPFS Connect All Points (count, delay)
* lnewrapocap - Loop NEWRAPO Connect All Points (count, delay, minx, maxx, miny, maxy)
* setpointstyle || sps - can change style of point (index, new size, form)
* setscreencenter || scc - changes the center of the screen (centerx, centery, inverty)
* setscale - multiplies the initial coordinates of the point by the number you specify (scale)
* setcolorline || scl - changes changes line color (indexli, r, g, b, a)
* measureangle || ma - outputs the degree of the angle of 3 points (vertex point, indexp1, indexp2)

### abbreviations
* add - additions
* sub - subtraction
* mul - multiplication
* div - division
* rod - remainder of division
* pow - power
* gcd - greatest common divisor
* lcm - lowest common multiple
* cos - cosine
* sin - sine
* tan - tangent
* rd  - reduce
* num - numerator
* denom - denominator
* itm - improper to mixed
* tif - to improper fraction
* af - add fraction
* sf - sub fraction
* dtf - decimal to fraction
* mf - mul fraction
* df - div fraction
* dtf - decimal to fraction
* laspo - last point
* renpo - render points
* newpo - new point
* edipo - edit point
* newli - new line
* infoli - info line
* pali - prints all lines
* infopo - info point
* eci - enable console interface
* ranum - random number
* newrapo - new random point
* rpfs - (new) random point full screen
* delpo - delete point
* cap - connect all points
* dpal - delete points and lines
* lrpfs - loop random point full screen
* lnewrapo - loop new random points
* lnrpfscap - loop random point full screen connect all points
* lnewrapocap - loop new random points connect all points
