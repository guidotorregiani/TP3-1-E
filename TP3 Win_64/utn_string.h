#ifndef UTN_STRING_H_INCLUDED
#define UTN_STRING_H_INCLUDED

int isValidIntNumber(char* cadena);
int isValidFloat(char str[]);
int validarLetra (char letras[]);
int getNumber(int *pResult,char *pMsg,char *pMsgError,int min,int max,int attempts);
int getString(char *pResult, char *pMsg, char *pMsgError, int min, int max, int intentos);
int getStringNumeros(char* pString, char* msg, char* msgE,int reintentos);
int getValidInt(int* input,char requestMessage[],char errorMessage[],int lowLimit, int hiLimit,int attemps);
void simpleGetString(char mensaje[],char input[]);
int isNum(char str[]);

#endif // UTN_STRING_H_INCLUDED
