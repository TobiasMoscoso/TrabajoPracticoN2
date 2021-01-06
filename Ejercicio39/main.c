/*
Hacer un programa que tome los datos de medición de potencia, 
cargados por el usuario, de un sistema de medición a distancia.

Los datos que cargará el usuario tienen la siguiente estructura:

    char desc[60];
    unsigned char potencia;
    unsigned int estado;
Donde estado es la multiplicación del valor ASCII de la primer letra 
de la descripción por la potencia. Los datos cargados se deberán 
guardar en una lista ordenada, de mayor a menor, del valor de potencia. 
Una vez finalizada la carga guardar los datos en un archivo de 
organización directa llamado "potencia.dat" imprimiendo en pantalla 
los datos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct datos{
    int id;
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct lista{
    struct datos data;
    struct lista *sig,*ant;
};

int main(){
    FILE *f;
    int i;
    char x=1;
    struct lista *lista=NULL,*local=NULL,*aux=NULL;
    struct datos d;
    
    while(x){
        aux = (struct lista*)malloc(sizeof(struct lista));

        printf("Potencia: ");
        scanf("%d",&aux->data.potencia);fflush(stdin);
        printf("\nDescripcion: ");
        gets(aux->data.desc);
        aux->data.estado = aux->data.desc[0] * aux->data.potencia;
    
        if(!lista){
            lista=aux;
            lista->sig = NULL;
        }else{
            local=lista;

            while((local->data.potencia>=aux->data.potencia)&&(local->sig!=NULL)){
                local=local->sig;
            }

            if(local->data.potencia<aux->data.potencia){
                if(aux->ant){
                    aux->ant->sig = aux;
                }else 
                    lista=aux;
                aux->ant = local->ant;
                local->ant=aux;
                aux->sig=local;
            }else{
                local->sig=aux;
                aux->ant=local;
                aux->sig=NULL;
            }
        }

        printf("Seguir cargando datos? SI(1)/NO(0)\n");
        scanf("%d",&x);fflush(stdin);
    }

    if(!(f=fopen("potencia.dat","wb"))){
        printf("No se encuentra el archivo\n");
        return 0;
    }
    i=0;
    printf("Guardando datos en potencia.dat...\n");
    printf("------------------------\n");
    struct datos final;
    while(lista){
        lista->data.id=i;
        final.potencia = lista->data.potencia;
        strcpy(final.desc,lista->data.desc);
        final.estado = lista->data.estado;
        final.id = lista->data.id;
        printf("Potencia: %d\n",lista->data.potencia);
        printf("Descripcion: %s\n",lista->data.desc);
        printf("Estado: %d\n",lista->data.estado);
        printf("ID en Archivo: %d\n",lista->data.id);
        printf("------------------------\n");
        fwrite(&final,sizeof(struct datos),1,f);
        lista=lista->sig;
        i++;
    }
       
    fclose(f);
    return 0;
}
