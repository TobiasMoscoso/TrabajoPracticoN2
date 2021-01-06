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

Si tipo tiene 1 en el bit 4 ----> Apilo clave y pos fisica
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pila *apilarconClave(long,struct pila*);
int menu(int o);

struct pila{
    long clave;
    long memo;
    struct pila *l;
};

struct d{                                                                                            
        long clave; //Clave o Id del registro
        char d[30]; // Descripcion                                                                                          
        unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
        char b; //'A':Alta 'B':Baja                                                                                                                                                                          
};

int main(){
    FILE *f;
    struct d dato;
    struct pila *p=NULL,*aux=NULL;
    long cl;
    int op;
    char x = 1;

    switch(menu(op)){
        case 1: //Crear archivo
            if(!(f= fopen("datos.dat","ab"))){
                printf("No se encuentra el archivo\n");
                return 0;
            }

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
            while(x){
                printf("\nIntroduzca la clave: ");
                scanf("%ld",&cl);fflush(stdin);
                p=apilarconClave(cl,p);

                printf("Seguir? SI(1)/NO(0)");
                scanf("%d",&x);fflush(stdin);
            }
            
            if(!(f = fopen("datos.dat","rb"))){
                printf("Archivo no encontrado\n");
                return 0;
            }
            while(p->l!=NULL){
                fseek(f,p->memo*(long)sizeof(struct d),SEEK_SET);
                fread(&dato,sizeof(dato),1,f);
                printf("Desc: %s\n",dato.d);

                aux = p;
                p = p->l;
                free(aux);
            }
            fseek(f,p->memo*(long)sizeof(struct d),SEEK_SET);
            fread(&dato,sizeof(dato),1,f);
            printf("Desc: %s\n",dato.d);
            free(aux);
            fclose(f);
            break;
    }

}


struct pila *apilarconClave(long clave,struct pila *p){
    FILE *f;
    struct d dato;
    long pos = 0;
    struct pila *aux;

    if(!(f = fopen("datos.dat","rb"))){
        printf("Archivo no encontrado\n");
        return 0;
    }
    fread(&dato,sizeof(dato),1,f);
    while(!feof(f)){ 
        if(dato.clave==clave){
            if(dato.tipo & (1<<4)){
                printf("Detected!\n");
                aux=(struct pila*)malloc(sizeof(struct pila));

                aux->clave = clave;
                aux->memo = pos;
                
                if(!p){
                    aux->l=NULL;
                }
                else{
                    aux->l = p;
                }

                fclose(f);
                return aux;
            }else{
                printf("Tipo incorrecto\n");
                return p;
            }
        }
        fread(&dato,sizeof(dato),1,f);
        pos++;
    }
    printf("Registro no encontrado\n");
    fclose(f);
    return p;
}


int menu(int o){
    printf("***Ej37***\n");
    printf("1.Crear Archivo\n");
    printf("2.Buscar Clave\n");

    scanf("%d",&o);fflush(stdin);
    system("cls");
    return o;
}