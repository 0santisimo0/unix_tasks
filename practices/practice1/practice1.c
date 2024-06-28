#include <stdio.h>

int add(int a, int b);
int add1(int* a, int* b);
int add2(int* a, int* b, int* c);

int main(int argc, char const *argv[])
{
   int x = 7;

   printf("x: %d\n", x);


   if (x == 7)
   {
       printf("Es 7 \n");
   }
   
   for (int i = 0; i < x; i++)
   {
       printf("i: %d\n", i);
   }
   
   int* x_address = &x;

   printf("x_address: %d\n", x_address);
   printf("x_address: %p\n", x_address); 
   printf("x_address: %ls", x_address); 

   int y = 6;
   int z = add(x,y);
   printf("z: %d\n", z);

   int j = add1(&x, &y);
   printf("j: %d\n", j);

   int p = 0;
   add2(&x, &y, &p);
   printf("p: %d\n", p);

   return 0;
}

int add(int a, int b){
   return a + b;
}

int add1(int* a, int* b){
   printf("a: %d\n", *a);
   printf("b: %d\n", *b);
   return *a + *b;
}

int add2(int* a, int* b, int* c){
   *c = *a + *b ;
}

// Compilación: gcc basic.c -o basic
// Concepto de Memoria