/*
EJERCICIO 40:
Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, 
realizar una función que pase como parámetro, entre otros datos, 
la clave del registro (id).

La función ubicará el registro correspondiente al id pasado como 
parámetro, y utilizando punteros imprimirá la primera palabra del 
campo "desc" en forma inversa, además cambiará el estado del bit 3 
para luego actualizar el archivo. Además, se agregará a una pila la 
potencia cuando los bits 0 y 2, del campo estado, estén encendidos, 
en caso contrario se agregará el registro al archivo “salida.dat” 
de organización secuencial.
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

struct pila{
    struct datos data;
    struct pila *ant;
};
void funcion(int);
char *invCadena (char str[60]);
int main(){
    int id;
    struct datos d;
    printf("Introduzca el ID respectivo:\n");
    scanf("&d",&id);fflush(stdin);
    funcion(id);
   
}

void funcion(int id){
    FILE *f,*p;
    struct datos d;
    struct pila *pila=NULL, *aux=NULL;
    if(!(f = fopen("potencia.dat","rb+"))){
        printf("No se encuentra el archivo\n");
        return 0;
    }
    fseek(f,(long) id * sizeof(struct datos),0);
    fread(&d,sizeof(struct datos),1,f);
    printf("Hay algo?: %s",&d.desc);
    printf("Descripcion invertida: %s\n",invCadena(d.desc));
    d.estado = d.estado ^ (1<<3);
    fwrite(&d,sizeof(struct datos),1,f);

    if((d.estado & (1<<0))&&(d.estado & (1<<2))){
        //apilar
        aux=(struct pila*)malloc(sizeof(struct pila));
        aux->ant = pila;
        pila = aux;
    }else{
        p=fopen("salida.dat","ab");
        fwrite(&d,sizeof(struct datos),1,p);
    }
    fclose(f);
    fclose(p);

}
char *invCadena (char str[60]){
    char aux [60], *i, *s;

    s = &str[0];
    i = aux;
   while(*s) s++;
   s--;
   while(s != &str[0]){
        *i=*s;
        s--;
        i++;
    }
    *i=*s; 
    i++; 
    *i=0; 
    return strdup(aux);
}
