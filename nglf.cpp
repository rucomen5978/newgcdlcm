// ngl functions
// nglf.cpp
//
// wrtim: without reduce to mixed fraction

#include "nglib.h"
#include <iostream>
using namespace std;

int gcd(int a, int b){
  while (b != 0){
    int temp = b;
    b = a % b;
    a = temp; 
  }
  return a;
}

int lcm(int a, int b) { return a * b / gcd(a, b); }

// add fraction wrtim
fraction addfraction(fraction first, fraction second){
 int cd = lcm(first.denom, second.denom);
 first.num *= cd / first.denom;
 second.num *= cd / second.denom;
 first.num += second.num;
 first.denom = cd;
 return first;
}

// sub fraction wrtim
fraction subfraction(fraction first, fraction second){
  int cd = lcm(first.denom, second.denom);
  first.toimproperfraction();
  second.toimproperfraction();

  first.num *= cd / first.denom;
  second.num *= cd / second.denom;
  first.num -= second.num;
  first.denom = cd;
  return first;
} 

// mul fraction wrtim
fraction mulfraction(fraction first, fraction second){
  first.toimproperfraction();
  second.toimproperfraction();
  first.num *= second.num;
  first.denom *= second.denom;
  return first;
}

// div fraction wrtim
fraction divfraction(fraction first, fraction second){
  first.toimproperfraction();
  second.toimproperfraction();
  first.num *= second.denom;
  first.denom *= second.num;
  return first;
}
