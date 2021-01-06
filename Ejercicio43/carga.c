/*
El servicio técnico de CosmeFulanito recibe órdenes de trabajo diarias. 
Las mismas son cargadas en un archivo secuencial por el personal de recepción 
bajo la siguiente estructura de datos:

typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;
Se pide:

Hacer una pila con las órdenes de trabajo de forma tal que la más vieja 
sea la última en cargarse.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

int menu();


int main(){
    FILE *f;
    int x=1;
    repuestos_t rep;
    printf("****Carga Archivo ordenes.dat****");

    f = fopen("ordenes.dat","wb");
    while(x){
        printf("\nCliente: ");
        fflush(stdin);
        gets(rep.cliente);
        printf("\nDescripcion de Falla: ");
        fflush(stdin);
        gets(rep.descripciondeFalla);
        printf("\nFecha: ");
        fflush(stdin);
        gets(rep.fecha);
        printf("\nHora: ");
        fflush(stdin);
        gets(rep.hora);
        printf("\nModelo: ");
        fflush(stdin);
        gets(rep.modelo);
        printf("\nNumero de Orden: ");
        fflush(stdin);
        scanf("%ld",&rep.numeroDeOrden);

        fwrite(&rep,sizeof(repuestos_t),1,f);
        printf("Seguir cargando? SI(1)/NO(0)\n");
        fflush(stdin);
        scanf("%d",&x);
    }
    fclose(f);

    return 0;
}
