/*
El servicio técnico utiliza la pila generada en el ejercicio 43 en su 
labor diaria. Cada técnico toma una tarea de la pila y genera un orden 
de extracción de repuestos al depósito. Para optimizar los viajes al 
depósito se arma una lista con los repuestos que cada orden necesita 
utilizando la siguiente estructura:

typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;

Se pide cargar la lista de repuestos solicitados por los técnicos. 
Tener en cuenta que varios técnicos pueden necesitar la misma parte, 
y en esos casos se debe incrementar la cantidad pedida en la lista.

traduccion: agarran de la pila -> generan orden de extraccion -> Arma lista con repuestos 
1.generar lista 

que saque el primer elemento de la pila y pregunto que repeusto quiere y que cantidad
Eso se guarda en una lista y se ordena de menor a mayor (o al reves). Ademas tiene que haber un if que compare si son iguales
en ese caso se suman las cantidades.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/////////////////////////////////////EJ43
typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestosA_t;
struct lista{
    repuestosA_t data;
    struct lista *sig,*ant;
};
struct pila{
    repuestosA_t data;
    struct pila *ant;
};
//////////////////////////////////////NUEVO

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;

typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;

struct listaR{
    extraccionRepuestos_t data;
    struct listaR *sig,*ant;
};
///////////////////////////////////////////

int main(){
    FILE *f;
    int x=1;
    repuestosA_t rep;
    struct lista *lista=NULL, *local, *aux=NULL;
    struct pila *pila=NULL,*paux=NULL;
    struct listaR *listar=NULL, *localR, *auxR=NULL;

    f=fopen("ordenes.dat","rb");
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
    int c=1;
    //Crear listado ordenes de extraccion
    while(pila->ant!=NULL){
        printf("--------------Caracteristicas del aparato %d--------------\n",c);
        printf("Cliente: %s\n",pila->data.cliente);
        printf("Descripcion de falla: %s\n",pila->data.descripciondeFalla);
        printf("Fecha: %s\n",pila->data.fecha);
        printf("Hora: %s\n",pila->data.hora);
        printf("Modelo: %s\n",pila->data.modelo);
        printf("Numero de Orden: %ld\n",pila->data.numeroDeOrden);  
        ///////////////////////////////////////////////////////////////////////////////
        auxR = (struct listaR*)malloc(sizeof(struct listaR));

        printf("--------------Realize la orden de repuestos---------------\n");
        printf("Part Number: ");
        fflush(stdin);
        scanf("%ld",&auxR->data.repuesto.partNumber);
        printf("Serial Number: ");
        fflush(stdin);
        scanf("%ld",&auxR->data.repuesto.serialNumber);
        printf("Descripcion: ");
        fflush(stdin);
        gets(auxR->data.repuesto.descripcion);
        printf("Ubicacion: ");
        fflush(stdin);
        gets(auxR->data.repuesto.ubicacion);
        printf("Cantidad: \n");
        fflush(stdin);
        scanf("%d",&auxR->data.cantidad);

        if(!listar){
                listar=auxR;
                listar->sig = NULL;
                listar->ant = NULL;
            }else{
                localR=listar;

                while((localR->data.repuesto.partNumber > auxR->data.repuesto.partNumber)&&(localR->sig!=NULL)){
                    localR=localR->sig;
                }

                if(localR->data.repuesto.partNumber < auxR->data.repuesto.partNumber){
                    auxR->ant = localR->ant;
                    localR->ant=auxR;
                    auxR->sig=localR;
                    if(auxR->ant!=NULL){
                        auxR->ant->sig = auxR;
                    }else 
                        listar=auxR;
                }else if(localR->data.repuesto.partNumber != auxR->data.repuesto.partNumber){
                    localR->sig=auxR;
                    auxR->ant=localR;
                    auxR->sig=NULL;
                }
                if(localR->data.repuesto.partNumber == auxR->data.repuesto.partNumber){
                    localR->data.cantidad = localR->data.cantidad + auxR->data.cantidad;
                }
            }
        ///////////////////////////////////////////////////////////////////////////////

        paux = pila;
        pila = pila->ant;
        c++;
        system("cls");
    }
    printf("--------------Caracteristicas del aparato %d--------------\n",c);
    printf("Cliente: %s\n",pila->data.cliente);
    printf("Descripcion de falla: %s\n",pila->data.descripciondeFalla);
    printf("Fecha: %s\n",pila->data.fecha);
    printf("Hora: %s\n",pila->data.hora);
    printf("Modelo: %s\n",pila->data.modelo);
    printf("Numero de Orden: %ld\n",pila->data.numeroDeOrden);
    printf("----------------------------------------------------------\n");

    ///////////////////////////////////////////////////////////////////////////////////
    auxR = (struct listaR*)malloc(sizeof(struct listaR));

    printf("--------------Realize la orden de repuestos---------------\n");
    printf("Part Number: ");
    fflush(stdin);
    scanf("%ld",&auxR->data.repuesto.partNumber);
    printf("Serial Number: ");
    fflush(stdin);
    scanf("%ld",&auxR->data.repuesto.serialNumber);
    printf("Descripcion: ");
    fflush(stdin);
    gets(auxR->data.repuesto.descripcion);
    printf("Ubicacion: ");
    fflush(stdin);
    gets(auxR->data.repuesto.ubicacion);
    printf("Cantidad: \n");
    fflush(stdin);
    scanf("%d",&auxR->data.cantidad);

    if(!listar){
        
            listar=auxR;
            listar->sig = NULL;
            listar->ant = NULL;
        }else{
            localR=listar;

            while((localR->data.repuesto.partNumber > auxR->data.repuesto.partNumber)&&(localR->sig!=NULL)){
                localR=localR->sig;
            }

            if(localR->data.repuesto.partNumber < auxR->data.repuesto.partNumber){
                auxR->ant = localR->ant;
                localR->ant=auxR;
                auxR->sig=localR;
                if(auxR->ant!=NULL){
                    auxR->ant->sig = auxR;
                }else 
                    listar=auxR;
            }else if(localR->data.repuesto.partNumber != auxR->data.repuesto.partNumber){
                localR->sig=auxR;
                auxR->ant=localR;
                auxR->sig=NULL;
            }
            if(localR->data.repuesto.partNumber == auxR->data.repuesto.partNumber){
                localR->data.cantidad = localR->data.cantidad + auxR->data.cantidad;
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////


    //Leo la listaR
    printf("--------------Lista de ordenes de extraccion--------------\n");
    while(localR->ant!=NULL){
        localR = localR->ant;
    }
    while(localR->sig!=NULL){
        
        printf("Part Number: %ld\n",localR->data.repuesto.partNumber);
        printf("Serial Number: %ld\n",localR->data.repuesto.serialNumber);
        printf("Descripcion: %s\n",localR->data.repuesto.descripcion);
        printf("Ubicacion: %s\n",localR->data.repuesto.ubicacion);
        printf("Cantidad: %d\n",localR->data.cantidad);
        printf("----------------------------------------------------------\n");

        localR=localR->sig;
    }
    printf("Part Number: %ld\n",localR->data.repuesto.partNumber);
    printf("Serial Number: %ld\n",localR->data.repuesto.serialNumber);
    printf("Descripcion: %s\n",localR->data.repuesto.descripcion);
    printf("Ubicacion: %s\n",localR->data.repuesto.ubicacion);
    printf("Cantidad: %d\n",localR->data.cantidad);
    printf("----------------------------------------------------------\n");

    return 0;
}

