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
1.Cargar un archivo con repuests_t; 2-lista mayor a menor; 3.Cargar pila
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

struct lista{
    repuestos_t data;
    struct lista *sig,*ant;
};

struct pila{
    repuestos_t data;
    struct pila *ant;
};
int main(){
    FILE *f;
    int x=1;
    repuestos_t rep;
    struct lista *lista=NULL, *local, *aux=NULL;
    struct pila *pila=NULL,*paux=NULL;
    
            if(!(f=fopen("ordenes.dat","rb"))){
                printf("No se encuentra el archivo\n");
                return 0;
            }
            fread(&rep,sizeof(rep),1,f);
            while(!feof(f)){
                
                aux = (struct lista*)malloc(sizeof(struct lista));
                strcpy(aux->data.cliente,rep.cliente);
                strcpy(aux->data.fecha,rep.fecha);
                strcpy(aux->data.descripciondeFalla,rep.descripciondeFalla);
                strcpy(aux->data.hora,rep.hora);
                strcpy(aux->data.modelo,rep.modelo);
                aux->data.numeroDeOrden = rep.numeroDeOrden;

                
                if(!lista){
                    lista=aux;
                    lista->sig = NULL;
                    //lista->ant = NULL;
                }else{
                    local=lista;

                    while((strcmp(local->data.fecha,aux->data.fecha)<=0)&&(local->sig!=NULL)){
                        local=local->sig;
                    }

                    if(strcmp(local->data.fecha,aux->data.fecha)>0){
                        
                        aux->ant = local->ant;
                        local->ant=aux;
                        aux->sig=local;
                        if(aux->ant!=NULL){
                            aux->ant->sig = aux;
                        }else 
                            lista=aux;
                    }else{
                        local->sig=aux;
                        aux->ant=local;
                        aux->sig=NULL;
                    }
                }
                
                fread(&rep,sizeof(rep),1,f);
            }
            

            fclose(f);

            //carga a pila
            while(lista){
                
                paux=(struct pila*)malloc(sizeof(struct pila));
                strcpy(paux->data.cliente,lista->data.cliente);
                strcpy(paux->data.fecha,lista->data.fecha);
                strcpy(paux->data.descripciondeFalla,lista->data.descripciondeFalla);
                strcpy(paux->data.hora,lista->data.hora);
                strcpy(paux->data.modelo,lista->data.modelo);
                paux->data.numeroDeOrden = lista->data.numeroDeOrden;

                paux->ant = pila;
                pila = paux; 

                lista=lista->sig;
            }

            //leer pila
            printf("--------------Lectura de Pila--------------\n");
            while(pila->ant!=NULL){
                printf("Cliente: %s\n",pila->data.cliente);
                printf("Fecha: %s\n",pila->data.fecha);
                printf("Descripcion de falla: %s\n",pila->data.descripciondeFalla);
                printf("Hora: %s\n",pila->data.hora);
                printf("Modelo: %s\n",pila->data.modelo);
                printf("Numero de Orden: %ld\n",pila->data.numeroDeOrden);
                printf("-------------------------------------------\n");
                paux = pila;
                pila = pila->ant;
                free(paux);
            }
            printf("Cliente: %s\n",pila->data.cliente);
            printf("Fecha: %s\n",pila->data.fecha);
            printf("Descripcion de falla: %s\n",pila->data.descripciondeFalla);
            printf("Hora: %s\n",pila->data.hora);
            printf("Modelo: %s\n",pila->data.modelo);
            printf("Numero de Orden: %ld\n",pila->data.numeroDeOrden);
            printf("-------------------------------------------\n");
            free(paux);
}