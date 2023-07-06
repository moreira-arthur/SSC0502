#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>

int VerificaNumeroNome( char nome[]){
    int controle_nome = 0;
    int i;
    for(i = 0; i < strlen(nome); i++){
        if(!isalpha(nome[i])){
            controle_nome -= 1;
        }
        if(isspace(nome[i])){
            controle_nome += 1;
        }
    }
    if(controle_nome != 0){
        printf("ERRO: A string contem caracteres nao alfabeticos\n");
        return -1;            
    }
    return 0;
}

int main(){
    char str[100];
    int controle = 0;
    int i;
    int retorno;
    gets(str);
    retorno = VerificaNumeroNome(str);
    if( retorno == -1){
        puts("Nome inválido");
    }else{
        puts("Nome valido");
    }   
    printf("%d", controle);
}