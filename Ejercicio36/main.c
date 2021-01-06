/*
EJERCICIO 36:
Hacer un programa que lea al archivo "contactos.dat" 
creado en el Ejercicio 35 y crear una lista, 
en memoria dinámica, ordenada alfabéticamente. 
Una vez creada la lista guardarla en un archivo de 
organización directa llamado "contactos_ordenados.dat" 
imprimiendola en pantalla.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct datos{
    char nombre[20];
    char apellido[20];
    char edad;
    long tel;
    char mail[40];
};

struct lista{
    struct datos d;
    struct lista *sig,*ant;
};

int main(){
    FILE *file;
    struct lista *lista=NULL, *aux=NULL, *local;
    struct datos d;
    

    if(!(file = fopen("contactos.dat","rb"))){
        printf("No se encuentra el archivo\n");
        return 0;
    }

    fread(&d,sizeof(d),1,file);
    while(!feof(file)){
        aux = (struct lista*)malloc(sizeof(struct lista));
        strcpy(aux->d.nombre,d.nombre);

        if(!lista){
            lista=aux;
            lista->sig = NULL;
        }else{
            local=lista;

            while((strcmp(local->d.nombre,aux->d.nombre)<=0)&&(local->sig!=NULL)){
                local=local->sig;
            }

            if(strcmp(local->d.nombre,aux->d.nombre)>0){
                if(aux->ant){
                    aux->ant->sig = aux;
                }else 
                    lista=aux;
                aux->ant = local->ant;
                local->ant=aux;
                aux->sig=local;
            }else
            {
                local->sig=aux;
                aux->ant=local;
                aux->sig=NULL;
            }
        }
        fread(&d,sizeof(d),1,file);
    }
    fclose(file);
    printf("Lista ordenada A-Z:\n");
    while(lista){
        printf("%s\n",lista->d.nombre);
        lista=lista->sig;
    }

    //free(aux);
    return 0;
}