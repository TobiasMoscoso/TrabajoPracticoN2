/*
El depósito de la empresa CosmeFulanito necesita cargar su 
stock de repuestos en forma ordenada. Para dicha tarea se 
solicitó categorizar a los respuestos bajo la siguiente 
estructura de datos:

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   chat ubicacion[100];        
}repuestos_t;
Los repuestos no están ordenados, se solicita cargarlos 
en una lista, la cual ordene por descripción a los repuestos 
para luego guardarlos en un archivo de stock con organización 
secuencial.

Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas 
productos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;

struct lista{
    repuestos_t rep;
    struct lista *sig,*ant;
};

int main(){
    FILE *f;
    int x=1;
    struct lista *lista=NULL,*local=NULL,*aux=NULL;
    repuestos_t stock;

    while(x){
        aux = (struct lista*)malloc(sizeof(struct lista));
        printf("Numero de Parte: \n");
        fflush(stdin);
        scanf("%ld",&aux->rep.partNumber);
        printf("Numero de Serie: \n");
        fflush(stdin);
        scanf("%ld",&aux->rep.serialNumber);
        printf("Descripcion: \n");
        fflush(stdin);
        gets(aux->rep.descripcion);
        printf("Ubicacion: \n");
        fflush(stdin);
        gets(aux->rep.ubicacion);

        if(!lista){
            lista=aux;
            lista->sig = NULL;
            lista->ant = NULL;
        }else{
            local=lista;

            while((strcmp(local->rep.descripcion,aux->rep.descripcion)>=0)&&(local->sig!=NULL)){
                local=local->sig;
            }

            if(strcmp(local->rep.descripcion,aux->rep.descripcion)<0){
                
                aux->ant = local->ant;
                local->ant=aux;
                aux->sig=local;
                if(aux->ant){
                    aux->ant->sig = aux;
                }else{
                    lista=aux;
                }
            }else{
                
                local->sig=aux;
                aux->ant=local;
                aux->sig=NULL;
            }
        }

        printf("Continuar? SI(1)/NO(0)\n");
        fflush(stdin);
        scanf("%d",&x);
        system("cls");
    }

    f = fopen("stock.dat","wb");
    local = lista;
    while((local->sig!=NULL)) local = local->sig;
    printf("------:::::REPUESTOS:::::------\n");
    while(local->ant != NULL){
        printf("Numero de Parte: %ld\n",local->rep.partNumber);
        printf("Numero de Serie: %ld\n",local->rep.serialNumber);
        printf("Descripcion: %s\n",local->rep.descripcion);
        printf("Ubicacion: %s\n",local->rep.ubicacion);
        printf("------------------------------\n");
        stock.partNumber = local->rep.partNumber;
        stock.serialNumber = local->rep.serialNumber;
        strcpy(stock.descripcion,local->rep.descripcion);
        strcpy(stock.ubicacion,local->rep.ubicacion);
        fwrite(&stock,sizeof(stock),1,f);
        local = local->ant;
    }
    printf("Numero de Parte: %ld\n",local->rep.partNumber);
    printf("Numero de Serie: %ld\n",local->rep.serialNumber);
    printf("Descripcion: %s\n",local->rep.descripcion);
    printf("Ubicacion: %s\n",local->rep.ubicacion);
    printf("------------------------------\n");
    stock.partNumber = local->rep.partNumber;
    stock.serialNumber = local->rep.serialNumber;
    strcpy(stock.descripcion,local->rep.descripcion);
    strcpy(stock.ubicacion,local->rep.ubicacion);
    fwrite(&stock,sizeof(stock),1,f);


    //free(aux);
    fclose(f);
    return 0;
}