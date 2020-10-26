#ifndef _LIBS
#define _LIBS

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
    struct lista *l;
};

int strOrden(int t,char n1[t], char n2[t]){
    int  i;
    for(i=0;i<t;i++){
        if(tolower(n1[i]) < tolower(n2[i])){
            return 1;//1.n1 2.n2
        }
        else if(tolower(n1[i]) > tolower(n2[i])){
            return 0;
        }
    }
}

#endif