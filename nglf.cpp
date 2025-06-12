// ngl functions
// nglf.cpp
//
// wrtif: without reduce to mixed fraction

#include "nglib.h"
#include <random>
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

// add fraction wrtif
fraction addfraction(fraction first, fraction second){
 int cd = lcm(first.denom, second.denom);
 first.num *= cd / first.denom;
 second.num *= cd / second.denom;
 first.num += second.num;
 first.denom = cd;
 return first;
}

// sub fraction wrtif
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

// mul fraction wrtif
fraction mulfraction(fraction first, fraction second){
  first.toimproperfraction();
  second.toimproperfraction();
  first.num *= second.num;
  first.denom *= second.denom;
  return first;
}

// div fraction wrtif
fraction divfraction(fraction first, fraction second){
  first.toimproperfraction();
  second.toimproperfraction();
  first.num *= second.denom;
  first.denom *= second.num;
  return first;
}

int getranum(int min, int max){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}
