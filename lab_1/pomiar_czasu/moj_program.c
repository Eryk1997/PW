
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>
#include "pomiar_czasu.h"



int main(){

inicjuj_czas();
double suma = 0;
printf("hello\n");
for(int i=0;i<100;i++){
	suma +=i;
}
printf("Suma: %f", suma);
printf("\n");
drukuj_czas();

double function(double a, double b){
	double suma = 0;
	for(int i=0;i<1000000000;i++)
	   suma += a * b + a;
	return suma;
}

inicjuj_czas();
printf("\nSuma: %f\n", function(2,4));
drukuj_czas();
return 0;

}
