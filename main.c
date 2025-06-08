#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

int lcm(int a, int b) { return a * b / gcd(a, b); }

int main() {
  char action[256];
  while (1) {
    scanf("%s", action);

    // Program part
    if (!strcmp(action, "exit") || !strcmp(action, "ex"))
      return 0;

    if (!strcmp(action, "clear") || !strcmp(action, "cl"))
      system("clear");

    // Base actions
    if (!strcmp(action, "add")) {
      long double fn, sn;
      scanf("%Lf%Lf", &fn, &sn);
      printf("%Lf\n", fn + sn);
    }

    if (!strcmp(action, "sub")) {
      long double fn, sn;
      scanf("%Lf%Lf", &fn, &sn);
      printf("%Lf\n", fn - sn);
    }

    if (!strcmp(action, "mul")) {
      long double fn, sn;
      scanf("%Lf%Lf", &fn, &sn);
      printf("%Lf\n", fn * sn);
    }

    if (!strcmp(action, "div")) {
      long double fn, sn;
      scanf("%Lf%Lf", &fn, &sn);
      printf("%Lf\n", fn / sn);
    }

    if (!strcmp(action, "rod")) {
      int fn, sn;
      scanf("%d%d", &fn, &sn);
      printf("%d\n", fn % sn);
    }

    if (!strcmp(action, "gcd")) {
      int fn, sn;
      scanf("%d%d", &fn, &sn);
      printf("%d\n", gcd(fn, sn));
    }

    if (!strcmp(action, "lcm")) {
      int fn, sn;
      scanf("%d%d", &fn, &sn);
      printf("%d\n", lcm(fn, sn));
    }

    if (!strcmp(action, "pow")) {
      long double fn, sn;
      scanf("%Lf%Lf", &fn, &sn);
      printf("%Lf\n", powl(fn, sn));
    }

    if (!strcmp(action, "cos")) {
      long double num;
      scanf("%Lf", &num);
      printf("%Lf\n", cosl(num));
    }

    if (!strcmp(action, "sin")) {
      long double num;
      scanf("%Lf", &num);
      printf("%Lf\n", sinl(num));
    }

    if (!strcmp(action, "tan")) {
      long double num;
      scanf("%Lf", &num);
      printf("%Lf\n", tanl(num));
    }

    // Fraction part
    if (!strcmp(action, "rd")) {
      int fn, sn, gcdval;
      scanf("%d%d", &fn, &sn);
      gcdval = gcd(fn, sn);
      printf("%d/%d %d\n", fn / gcdval, sn / gcdval, gcdval);
    }

    if (!strcmp(action, "itm")) {
      int fp, num, denom;
      scanf("%d%d", &num, &denom);
      fp = num / denom;
      num %= denom;
      printf("%d %d/%d\n", fp, num, denom);
    }

    if (!strcmp(action, "tif")) {
      int fp, num, denom;
      scanf("%d%d%d", &fp, &num, &denom);
      num = denom * fp + num;
      printf("%d/%d\n", num, denom);
    }

    if (!strcmp(action, "af") || !strcmp(action, "sf")) {
      int fn, fd, sn, sd, cd, gcdval;
      scanf("%d%d%d%d", &fn, &fd, &sn, &sd);
      cd = lcm(fd, sd);
      fn *= cd / fd;
      sn *= cd / sd;
      if (!strcmp(action, "af"))
        fn += sn;
      else
        fn -= sn;
      gcdval = gcd(fn, cd);
      printf("%d/%d %d\n", fn, cd, gcdval);
    }

    if (!strcmp(action, "mf") || !strcmp(action, "df")) {
      int fn, fd, sn, sd, cd, gcdval;
      scanf("%d%d%d%d", &fn, &fd, &sn, &sd);
      if (!strcmp(action, "mf")) {
        fn *= sn;
        fd *= sd;
      } else {
        fn *= sd;
        fd *= sn;
      }
      gcdval = gcd(fn, fd);
      printf("%d/%d %d\n", fn, fd, gcdval);
    }

    if (!strcmp(action, "dtf")) {
      int num, denom, gcdval;
      long double decimal;
      denom = 1e6;
      scanf("%Lf", &decimal);
      num = (int)(decimal * denom);
      gcdval = gcd(num, denom);
      num /= gcdval;
      denom /= gcdval;
      printf("%d/%d\n", num, denom);
    }
  }
  return 0;
}
