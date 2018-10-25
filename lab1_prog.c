#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>
int main () {
    int x, y, z;
    printf("print here x, y, z:\n");
    while(true) {
     x = get_int("x:");
     if (x == 0 || x == 1){
      break;
     }
     else {
      printf("x should be 0 or 1 \n");
     }
    }
    while(true) {
     y = get_int("y:");
     if (y == 0 || y == 1){
      break;
     }
     else {
      printf("y should be 0 or 1 \n");
     }
    }
    while(true) {
     z = get_int("z:");
     if (z == 0 || z == 1){
      break;
     }
     else {
      printf("z should be 0 or 1 \n");
     }
    }
    int c = !(x == y) || ( !( !(y == z) || (z == x) ) || (x == z) );
    printf("this is the result: %d\n", c);
}