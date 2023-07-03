#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<windows.h>

typedef struct 
{
    int id;
    char nome[100];
    int idade;
    float saldo;
}user;

typedef struct
{
    user *cliente;
    int tamanho;
    int qtd_id;
}controle;

int PegarPosicao(controle *Control, int id){
    int i;
    int posicao = -1;
    for (i = 0; i < Control->tamanho; i++)
    {
        if (Control->cliente[i].id == id)
        {
            posicao = i;
            break;
        }
    }
    return posicao;
}

void ExcluirUsuario(controle Control, int ide){
    int i = PegarPosicao(&Control,ide);
    int index;
    if(i > -1){
        for((index = i+1);(index < (Control.tamanho - 1));(index++)){
            Control.cliente[index - 1] = Control.cliente[index];
        }
        Control.tamanho -= 1;
        Control.cliente = (user*)realloc(Control.cliente,(Control.tamanho + 1) * sizeof(user));
        printf("Usuário %d excluído com sucesso!\n", ide);

        FILE *arq2;

        arq2 = fopen("teste.txt","w");
            if(arq2 == NULL){
                printf("Erro, nao foi possivel abrir o arquivo\n");
            }else{
                for(i=0; i < (Control.tamanho - 1); i++)
                    fprintf(arq2 ,"%d %s %d %.2f\n",Control.cliente[i].id, Control.cliente[i].nome, Control.cliente[i].idade, Control.cliente[i].saldo);
            }

        fclose(arq2);
    }
}
int main(){
    setlocale(LC_ALL,"pt_BR.UTF-8");

    controle controle;	
    controle.cliente = (user*)malloc(1*sizeof(user));
    controle.tamanho = 1;
    controle.qtd_id = 0;
    char url [] = "teste.txt";
    // char url2 [] = "BackupDados.txt";
    // char nome [100];
    // int id,idade;
    // float saldo;
    user ReadUser;
    // user WriteUser;
    int id_exclusao = 0;
        //Leitura do arquivo de dados já existente
    FILE *arq;
    arq = fopen(url,"r");
    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        while((fscanf(arq,"%d %s %d %f\n",&ReadUser.id, &ReadUser.nome[0], &ReadUser.idade, &ReadUser.saldo))!=EOF){
            // printf("ID: %d\nNome: %s\nIdade: %d\nSaldo: %.2f\n\n",id, nome, idade, saldo);
            controle.cliente = (user*)realloc(controle.cliente,(controle.tamanho + 1) *sizeof(user));
            controle.cliente[controle.tamanho - 1].id = ReadUser.id;
            strcpy(controle.cliente[controle.tamanho - 1].nome,ReadUser.nome);
            controle.cliente[controle.tamanho - 1].idade = ReadUser.idade;
            controle.cliente[controle.tamanho - 1].saldo = ReadUser.saldo;
            controle.tamanho++;
            controle.qtd_id = ReadUser.id;
        }
    }
    fclose(arq);

    puts("Digite o ID do usuário que deseja excluir:\n");
    scanf("%d",&id_exclusao);
    if(id_exclusao == 0 || PegarPosicao(&controle,id_exclusao) == -1){
        puts("ERRO: Você não pode excluir uma conta inexistente.\n");
        system("pause");
        return 1;
    }
    ExcluirUsuario(controle,id_exclusao);
    system("pause");
    return 2;

}