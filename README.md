# new gcd legacy

## install
* ubuntu/debian - sudo apt install gcc
* arch/monjaro  - sudo pacman -S gcc
* ```bash
  git clone --branch nglegacy --single-branch https://github.com/rucomen5978/nglegacy
  cd ngl
  gcc main.c -o ngl -lm
  ./ngl

## use
in the program, all interaction occurs through entering the function name and arguments to them into the console.
the program consists of small functions that take from 1 to 4 arguments (except the first four).
here is the list:

* ex exit cl clear add sub mul div rod gcd lcm pow cos sin tan rd itm tif af sf mf df dtf

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

* gcd - accepts 2 digits and outputs gcd
* lcm - accepts 2 digits and outputs lcm
### example for all listed functions
* ``` ngl
  add 2 2
  4.0000000
  sub 2 3
  -1.0000000
  mul 4 4
  16.0000000
  div 16 8
  2.0000000
  rod 36 7
  1
  pow 7 2
  49.0000000
  gcd 7 14
  7
  lcm 12 36
  36
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
  1.619775
### fraction part
* rd  - takes an improper fraction (num and denom) and outputs the reduced num with the denom and gcd of the fraction you entered
* itm - takes an improper fraction and outputs a proper fraction
* tif - takes a proper fraction (integer part, numerator, denominator) and outputs an improper fraction
* af - takes two improper fractions (i.e. 4 numbers) and outputs the sum of the two fractions as an unabridged and improper fraction, then outputs the number by which the fraction can be reduced
* sf mf df - do the same thing as af, only different actions (i.e. sf - subtracts, mf - multiplies, df - divides)
* dtf - takes a decimal fraction and converts it to an improper fraction

### example
* ``` ngl
  af 1 2 3 4
  5/4 1
  sf 7 8 1 6
  17/24 1
  mf 2 5 7 8
  14/40 2
  rd 14 40
  7/20 2
  df 7 32 2 69
  483/64 1
  itm 483 64
  7 35/64
  tif 6 7 8
  55/8
  dtf 0.44
  11/25
  dtf 0.45
  9/20
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
