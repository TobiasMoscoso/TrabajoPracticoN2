/*
El proveedor de repuestos de CosmeFulanito informó que una partida 
de repuestos salió con falla y debe ser devuelta. Para identificar la 
partida, el proveedor indicó que la falla fue en el partNumber: 1234 que 
tiene números de serie con el bit 3 y 5 en 1.

Para estas tareas se solicita:

Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso.
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

struct cola{
    repuestos_t rep;
    struct cola *ant,*sig;
};

int main(){
    FILE *f,*bajaf;
    repuestos_t dato;

    struct cola *cola=NULL, *aux = NULL, *local = NULL;
    if(!(f = fopen("stock.dat","rb"))){
        printf("No se encuentra el archivo\n");
        return 0;
    }

    if(!(bajaf = fopen("baja.dat","wb"))){
        printf("No se encuentra el archivo\n");
        return 0;
    }
    fread(&dato,sizeof(repuestos_t),1,f);
    while(!feof(f)){
        if(dato.partNumber == 1234 && dato.serialNumber & (1<<5) && dato.serialNumber & (1<<3)){
            //hacer cola del registro
            aux = (struct cola*)malloc (sizeof(struct cola));

            strcpy(aux->rep.descripcion,dato.descripcion);
            aux->rep.partNumber = dato.partNumber;
            aux->rep.serialNumber = dato.serialNumber;
            strcpy(aux->rep.ubicacion,dato.ubicacion);

            aux->sig=NULL;
            if(!cola){
                cola = aux;
                local = aux;
                cola->ant=NULL;
            }
            else{
                local->sig = aux;
                aux->ant = local;
                local = aux;
            }
        }
        else {
            //Baja fisica
            fwrite(&dato,sizeof(repuestos_t),1,bajaf);
        }  

        fread(&dato,sizeof(repuestos_t),1,f);
    }
    fclose(f);
    fclose(bajaf);
    remove("stock.dat");
    rename("baja.dat","stock.dat");

    f = fopen("stockfallas.dat","wb");

    while(!local->ant){
        strcpy(dato.descripcion,local->rep.descripcion);
        dato.partNumber = local->rep.partNumber;
        dato.serialNumber = local->rep.serialNumber;
        strcpy(dato.ubicacion,local->rep.ubicacion);
        
        fwrite(&dato,sizeof(repuestos_t),1,f);
        local = local->ant;
    }
    strcpy(dato.descripcion,local->rep.descripcion);
    dato.partNumber = local->rep.partNumber;
    dato.serialNumber = local->rep.serialNumber;
    strcpy(dato.ubicacion,local->rep.ubicacion);
    
    fwrite(&dato,sizeof(repuestos_t),1,f);

    fclose(f);

    



    return 0; 
}