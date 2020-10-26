/*
EJERCICIO 38:
Hacer una cola con los valores muestreados de un cuarto de ciclo de 
una señal sinusoidal, en 8 bits, para luego recorrerla y recomponer 
la señal completa. Las muetras deberán ir de 127 a -127 utilizando 
el bit más significativo en 1 para los valores negativos y en 0 
para los valores positivos. Imprimir en pantalla los valores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    
    typedef unsigned char uint_8;
    struct cola{
        uint_8 muestra;
        struct cola *l;    
    };
    struct cola *p=NULL,*u=NULL,*aux;
    uint_8 x;//0 a 90
    double val = 3.14159265 / 180;
    for(x=0;x<90;x++){
        aux = (struct cola*)malloc(sizeof(struct cola));

        if(!p){
            p=u=aux;
            //aux->l=NULL;
        }
        else{
            aux->muestra = sin((double)x*val) * 127;
            //printf(" %d ",aux->muestra);
            u->l=aux;
            aux->l=NULL;
            u=aux;
       
        }
    }
    aux=p;
    while(aux){
        printf(" %d ",aux->muestra);
        aux=aux->l;
    }

}