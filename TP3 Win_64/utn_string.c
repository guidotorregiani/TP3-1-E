#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Utn_String.h"

int validarLetra (char letras[])
{
    int ret=0;
    int i=0;
    int CantidadLetras;
    CantidadLetras=strlen(letras);
    while (i<CantidadLetras && ret==0)
    {
        if ((letras[i]!=' ')&&(letras[i]<'a'||letras[i]>'z')&&(letras[i]<'A'||letras[i]>'Z'))
        {
            i++;
        }
        else
        {
            ret=-1;
        }
    }
    return ret;
}

int isValidIntNumber(char* cadena)
{
    int i = 0;
    int ret = -1;

    if(cadena[i] == '-')
    {
        i++;
    }
    for(;cadena[i] != '\0'; i++)
    {
        if(cadena[i] < '0' || cadena[i] > '9')
        {
            ret = 0;
            break;
        }

    }
    return ret;
}

int getString(char *pResult, char *pMsg, char *pMsgError, int min, int max, int intentos)
{
    int ret=-1;
    char arrayAuxiliar[4096];
    while(intentos>0)
    {
        printf(pMsg);
        fflush(stdin); //LIMPIA BUFFER WINDOWS
        //__fpurge(stdin); //LIMPIA BUFFER LINUX
        fgets(arrayAuxiliar,sizeof(arrayAuxiliar),stdin);
        arrayAuxiliar[strlen(arrayAuxiliar)-1] = '\0';

        if(pResult != NULL && strlen(arrayAuxiliar) >= min && strlen(arrayAuxiliar) <= max && validarLetra(arrayAuxiliar)==0)
        {
            strncpy(pResult,arrayAuxiliar,max);
            ret=0;
            break;
        }
        else
        {
            printf(pMsgError);
        }
        intentos--;
    }
    return ret;
}


int getStringNumeros(char* pString, char* msg, char* msgE,int reintentos)
{
    char bufferStr[4096];
    int retorno=-1;
    while(retorno==-1 && reintentos>0)
    {
        if(pString!=NULL)
        {
            simpleGetString(msg,bufferStr);
            if(isNum(bufferStr))
            {
                strncpy(pString,bufferStr,sizeof(bufferStr));
                retorno=0;
            }
        }
        else
        {
            printf(msgE);
            retorno=-1;
            reintentos--;
        }
    }
    return retorno;
}

int getStringNumerico(char mensaje[],char input[])
{
    char aux[256];
    simpleGetString(mensaje,aux);
    if(isNum(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}
//----

int getValidInt(int* input,char requestMessage[],char errorMessage[],int lowLimit,int hiLimit,int attemps)
{
    char auxStr[256];
    int auxInt, i, retorno = -1;

    for(i=0;i<attemps;i++)
    {
        if(!getStringNumerico(requestMessage,auxStr))
        {
            printf ("%s",errorMessage);
            break;
        }
        auxInt = atoi(auxStr);
        if(auxInt < lowLimit || auxInt > hiLimit)
        {
            printf ("%s",errorMessage);
            break;
        }
        *input = auxInt;
        retorno = 0;
        break;

    }
    return retorno;

}

void simpleGetString(char mensaje[],char input[])
{
    printf("%s",mensaje);
    fflush(stdin);
    scanf ("%[^\n]s", input);
}

int isNum(char str[])
{
   int i=0;
   while(str[i] != '\0')
   {
       if (i == 0 && str[i] == '-')
       {
           i++;
           continue;
       }
       if(str[i] < '0' || str[i] > '9')
       {
           return 0;
       }
       i++;
   }
   return 1;
}
