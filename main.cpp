// main.cpp

#include "nglib.h"

int main(){
  int returnci = nglci();
  if (returnci == 1) mainsi();
  else if (returnci == 2) startsici();
  return 0;
}
