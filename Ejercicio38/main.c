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


struct cola{
    char muestra;
    struct cola *ant,*sig;    
};

int main(){
    char i;
    struct cola *cola = NULL, *aux = NULL, *local = NULL,*final;
    for(i=0;!(i==127);i++){
        aux = (struct cola*) malloc(sizeof(struct cola));
        aux->muestra = i;
        aux->sig = NULL;
        if(cola==NULL){
            cola = aux;
            local = aux;
            cola->ant = NULL;
        }else{
            local->sig = aux;
            aux->ant = local;
            local = aux;
        }
    }
    aux = (struct cola*) malloc(sizeof(struct cola));
    aux->muestra = 127;
    aux->sig = NULL; 
    local->sig = aux;
    aux->ant = local;
    local = aux;
    final=local;
    aux=cola;
    //Recorrer de 0_127  127_0  0_-127  -127_0

    //////////////////////////////////////0_127
    while(cola->sig != NULL){
        printf(" %d ",cola->muestra);
        cola = cola->sig;
    }
    printf(" %d ",cola->muestra);
    /////////////////////////////////////////////

    printf("\n***************************\n");

    /////////////////////////////////////127_0

    while(local->ant!=NULL){
        printf(" %d ",local->muestra);
        local = local->ant;
    }
    printf(" %d ",local->muestra);

    ///////////////////////////////////////////

    printf("\n***************************\n");

    ////////////////////////////////////0_-127

    local = final;
    while(local->ant!=NULL){
        printf(" %d ",local->muestra = local->muestra|(1<<7));
        local = local->ant;
    }
    ///////////////////////////////////////////
    
    printf("\n***************************\n");

    ////////////////////////////////////-127_0
    
    cola=aux;
    cola = cola->sig;
    while(cola->sig != NULL){
        printf(" %d ",cola->muestra = cola->muestra|(1<<7));
        cola = cola->sig;
    }
    printf(" %d ",cola->muestra = cola->muestra|(1<<7));
    
    ///////////////////////////////////////////
    return 0;

}

