/*
EJERCICIO 37:
Existe un archivo llamado "datos.dat", de tipo binario, 
cuya organización es secuencial. Los datos están organizados 
según la siguiente estructura:

struct d{                                                                                            
    long clave; //Clave o Id del registro
    char d[30]; // Descripcion                                                                                          
    unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
    char b; //'A':Alta 'B':Baja                                                                                                                                                                          
}

Se Pide: Realizar una funciún que pase como parámetro la clave, 
entre otros parámetros, y apile dos valores, 
la Clave y su posición física respecto al archivo 
(registro 1, 2, etc), si es que el campo tipo tiene el bit 4 
con valor 1. En caso de no encontrarlo mostrar por pantalla 
"Registro no encontrado". La función debe devolver el puntero 
de pila. Realizar el main con varias llamadas a dicha función y 
proceder a mostrar las descripciones del archivo, mediante 
la pila como acceso directo, NO USAR VARIABLES GLOBALES.

Traduccion:
Si tipo tiene 1 en el bit 4 ----> Apilo clave y pos fisica
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pila *apilarconClave(long clave,long ing,unsigned char x,struct pila *aux,struct pila *p);
    struct pila{
        long clave;
        long memo;
        struct pila *l;
    };

int main(){

    struct d{                                                                                            
        long clave; //Clave o Id del registro
        char d[30]; // Descripcion                                                                                          
        unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
        char b; //'A':Alta 'B':Baja                                                                                                                                                                          
    };

    
    FILE *f;
    struct pila *p,*aux;
    struct d dato;
    long cl;
    int op;

    
    
    switch(menu(op)){
        case 1: //Crear archivo
            f= fopen("datos.dat","ab");
            printf("Ingrese datos:\n");
            printf("Clave: ");
            scanf("%ld",&dato.clave);fflush(stdin);
            printf("\nDescripcion: ");
            gets(dato.d);
            printf("\nTipo: ");
            scanf("%d",&dato.tipo);fflush(stdin);
            printf("\nAlta (A) o Baja (B): ");
            scanf("%c",&dato.b);fflush(stdin);
            printf("\n");
            fwrite(&dato,sizeof(dato),1,f);
            fclose(f);
            break;
        case 2:
            printf("Introduzca la clave: ");
            scanf("%ld",&cl);

            if(!(f = fopen("datos.dat","rb"))){
                printf("Archivo no encontrado\n");
                return 0;
            }

            fread(&dato,sizeof(dato),1,f);
            while(!feof(f)){ 
                
                aux=apilarconClave(dato.clave,cl,dato.tipo,&aux,&p);

                printf("%d",aux->l);
                
                fread(&dato,sizeof(dato),1,f);
            }
            fclose(f);
            break;
    }
}


struct pila *apilarconClave(long clave,long ing,unsigned char x,struct pila *aux,struct pila *p){
    
    if(clave == ing){
        if(x & 0b00010000 == 0b00010000){
            aux = (struct pila*)malloc(sizeof(struct pila));
            aux->clave=clave;
            
            aux->l = p;
            p = aux;
            printf("Clave: %ld\n",aux->clave);
            aux = (struct pila*)malloc(sizeof(struct pila));
            aux->memo=(long*)aux->l;
            aux->l = p;
            printf("Direccion: %d\n",aux->memo);
            return aux->l;
        }
    }else{
        printf("Registro no encontrado\n");
    }
}


int menu(int o){
    printf("***Ej37***\n");
    printf("1.Crear Archivo\n");
    printf("2.Buscar Clave\n");

    scanf("%d",&o);fflush(stdin);
    system("cls");
    return o;
}