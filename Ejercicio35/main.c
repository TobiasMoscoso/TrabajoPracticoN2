/* EJERCICIO 35:
    Hacer un programa que tome los datos de contacto de una persona 
    (Nombre, Apellido, edad, teléfono, mail) 
    y los cargue, en forma directa, en una pila de memoria dinámica. 
    Imprimir en pantalla y cargar en un archivo llamado 
    "contactos.dat", de organización secuencial, los registros 
    ingresados por el usuario 
    si la persona tiene una edad mayor a 21 años.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    struct datos{
    char nombre[20];
    char apellido[20];
    char edad;
    long tel;
    char mail[40];
};

struct pila{
    struct datos d;
    struct pila *l;
};
    struct pila *p=NULL,*aux;
    struct datos ej;
    char op = 'y';
    FILE *file;
    int i=0,c=0;
    
    do{
        ////////////////////////////////////////////
        c++;
        aux=(struct pila*) malloc(sizeof(struct pila));

        ///////////////////////////Datos
        printf("\nNombre: ");
        gets(aux->d.nombre);
        printf("\nApellido: ");
        gets(aux->d.apellido);
        printf("\nEdad: ");
        scanf("%d",&aux->d.edad);fflush(stdin);
        printf("\nTelefono: ");
        scanf("%ld",&aux->d.tel);fflush(stdin);
        printf("\nMail: ");
        gets(aux->d.mail);
        printf("\n");
        //////////////////////////////////
        aux->l = p;
        p = aux;
        ///////////////////////////////////////////
        system("cls");

        printf("Desea agregar mas personas? Y/N");
        scanf("%c",&op);fflush(stdin);
        system("pause");
    }while(toupper(op) == 'Y');

    //Imprimir en pantalla y cargar archivo contactos.dat
    
        
    while(c != 0){
        c--;
        //Personas mayor a 21 años?
        if(aux->d.edad > 21){
            //Cargo el registro
            printf("\nNombre: ");
            puts(aux->d.nombre);
            printf("\nApellido: ");
            puts(aux->d.apellido);
            printf("\nEdad: %d",aux->d.edad);
            printf("\nTelefono: %d",aux->d.tel);
            printf("\nMail: ");
            puts(aux->d.mail);
            printf("\n");

            system("pause");

            strcpy(ej.nombre,aux->d.nombre);
            strcpy(ej.apellido,aux->d.apellido);
            ej.edad = aux->d.edad;
            ej.tel = aux->d.tel;
            strcpy(ej.mail,aux->d.mail);

            if(!(file = fopen("contactos.dat","ab"))){
                printf("Error al abrir el archivo\n");
            }
            fwrite(&ej,sizeof(ej),1,file);
            fclose(file);
        }
        aux=aux->l;
    }
        
    //Leer contacto.dat
    system("cls");
    printf("Lectura de archivo...\n");
    system("pause");
    system("cls");
    if(!(file = fopen("contactos.dat","rb"))){
        printf("Error al abrir el archivo\n");
    }
    printf("Archivo Abierto:\n");
    
    fread(&ej,sizeof(ej),1,file);
    while(!feof(file)){
        printf("\nNombre: %s",ej.nombre);
        printf("\nApellido: %s",ej.apellido);
        printf("\nEdad: %d",ej.edad);
        printf("\nTelefono: %d",ej.tel);
        printf("\nMail: %s",ej.mail);
        printf("\n");
        fread(&ej,sizeof(ej),1,file);
    }
    fclose(file);
    free(p);
    return 1;
}