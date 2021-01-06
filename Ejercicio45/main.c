/*
La lista creada en el ejercicio 44 es procesada por el depósito. 
Para dicha tarea se pide hacer un programa que:

Descuente las cantidades solicitadas del archivo de stock, creado en el 
Ejercicio 41.
Hacer una cola con los repuestos en los que no se encontró stock suficiente 
para poder notificar a los clientes la demora de la reparación.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/////////////////////////////////////
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
//////////////////////////////////////

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
struct cola{
    repuestos_t rep;
    int cantidad;
    struct cola* sig;
};

///////////////////////////////////////////
int main(){
    FILE *f;
    FILE *stock;
    FILE *memo;
    int x=1,g=0;
    repuestosA_t rep;
    repuestos_t dep;
    struct lista *lista=NULL, *local, *aux=NULL;
    struct pila *pila=NULL,*paux=NULL;
    struct listaR *listar=NULL, *localR, *auxR=NULL;
    struct cola *cola=NULL, *auxC=NULL,*localC=NULL;

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
        //system("cls");
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


    //Ej45
    if(!(stock = fopen("stock.dat","rb+"))){
        printf("No se encuentra el archivo");
        return 0;
    }
    if(!(memo = fopen("memo.dat","wb"))){
        printf("No se encuentra el archivo");
        return 0;
    }

    
    while(localR->ant!=NULL){
        localR = localR->ant;
    }
    while(localR->sig!=NULL){

        c = localR->data.cantidad;
        fseek(stock,0,0);
        fread(&dep,sizeof(dep),1,stock);
        while(!feof(stock)){
            if(!c && localR->data.repuesto.partNumber==dep.partNumber && localR->data.repuesto.serialNumber == dep.serialNumber){
                printf("No necesito mas de %ld\n",localR->data.repuesto.partNumber);
                fwrite(&dep,sizeof(dep),1,memo);
            }

            if(c!=0 &&localR->data.repuesto.partNumber==dep.partNumber && localR->data.repuesto.serialNumber == dep.serialNumber){
                c--;
            }

            fread(&dep,sizeof(dep),1,stock);
        }
        if(c!=0){
            //faltan registros
            printf("faltan %d registros de %ld\n",c,localR->data.repuesto.partNumber);
            //hacer la cola
            auxC=(struct cola*)malloc(sizeof(struct cola));
            auxC->rep.partNumber=localR->data.repuesto.partNumber;
            auxC->rep.serialNumber=localR->data.repuesto.serialNumber;
            strcpy(auxC->rep.descripcion,localR->data.repuesto.descripcion);
            strcpy(auxC->rep.ubicacion,localR->data.repuesto.ubicacion);
            auxC->cantidad = c;

            auxC->sig =NULL;
            if(cola==NULL){
                cola=auxC;
                localC=auxC;
            }else{
                localC->sig=auxC;
                localC=auxC;
            }
        }

        localR=localR->sig;
    }    

    c = localR->data.cantidad;
    fseek(stock,0,0);
        fread(&dep,sizeof(dep),1,stock);
        while(!feof(stock)){
            if(c!=0 &&localR->data.repuesto.partNumber==dep.partNumber && localR->data.repuesto.serialNumber == dep.serialNumber){
                c--;
            }
    
            if(!c && localR->data.repuesto.partNumber==dep.partNumber && localR->data.repuesto.serialNumber == dep.serialNumber){
                printf("No necesito mas de %ld\n",localR->data.repuesto.partNumber);
                fwrite(&dep,sizeof(dep),1,memo);
            }

            fread(&dep,sizeof(dep),1,stock);
        }
        if(c!=0){
            //faltan registros
            printf("faltan %d registros de %ld\n",c,localR->data.repuesto.partNumber);
            //hacer la cola
            auxC=(struct cola*)malloc(sizeof(struct cola));
            auxC->rep.partNumber=localR->data.repuesto.partNumber;
            auxC->rep.serialNumber=localR->data.repuesto.serialNumber;
            strcpy(auxC->rep.descripcion,localR->data.repuesto.descripcion);
            strcpy(auxC->rep.ubicacion,localR->data.repuesto.ubicacion);
            auxC->cantidad = c;

            auxC->sig =NULL;
            if(cola==NULL){
                cola=auxC;
                localC=auxC;
            }else{
                localC->sig=auxC;
                localC=auxC;
            }
        }
    fclose(stock);
    fclose(memo);
    remove("stock.dat");
    rename("memo.dat","stock.dat");


    printf("-------------------Repuestos faltantes-------------------\n");
    while(cola->sig!=NULL){
        printf("Cantidad que falta: %d\n",cola->cantidad);
        printf("Part Number: %ld\n",cola->rep.partNumber);
        printf("Serial Number: %ld\n",cola->rep.serialNumber);
        printf("Descripcion: %s\n",cola->rep.descripcion);
        printf("Ubicacion: %s\n",cola->rep.ubicacion);
        printf("---------------------------------------------------------\n");
        cola=cola->sig;
    }
    printf("Cantidad que falta: %d\n",cola->cantidad);
    printf("Part Number: %ld\n",cola->rep.partNumber);
    printf("Serial Number: %ld\n",cola->rep.serialNumber);
    printf("Descripcion: %s\n",cola->rep.descripcion);
    printf("Ubicacion: %s\n",cola->rep.ubicacion);
    printf("---------------------------------------------------------\n");
    return 0;
}

