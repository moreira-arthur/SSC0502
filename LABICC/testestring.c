#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char str[100];
    gets(str);
    for(int i = 0; i < strlen(str); i++){
        if(!isalpha(str[i])){
            printf("ERRO: A string contem caracteres nao alfabeticos\n");
            break;
        }
    }

}