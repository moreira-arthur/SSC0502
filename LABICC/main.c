#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

// Estrutura de usuario, que armazena todas as suas informações

typedef struct 
{
    int id;
    char nome[100];
    int idade;
    float saldo;
}user;

// Como em C, diferentemente de outras linguagens de mais alto nivel 
// não temos uma manipulação tão prática para obter o tamanho de vetores
// optamos por contruir uma outra Estrutura de controle, com o objetivo de 
// armazenar o tamanho do ponteiro, além de garantir a unicidade dos ids de
// cada usuário

typedef struct
{
    user *cliente;
    int tamanho;
    int qtd_id;
}controle;

void CriarArquivoFormatado(char url[],char url2[]){

    //  Para garantir que nenhum usuário será perdido, decidimos fazer um
    // arquivo de backup, com o objetivo de reguardar as informações
    // dos usuários, caso o arquivo principal seja corrompido
    // Além disso, o arquivo de backup é formatado de maneira mais expositiva, de modo a facilitar a leitura, sendo assim o arquivo final

    user ReadUser;
    FILE *arq;
    arq = fopen(url,"r");
    FILE *arq2;
    arq2 = fopen(url2,"w");
    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        while((fscanf(arq,"%d/%d/%f/%[^\n]\n",&ReadUser.id, &ReadUser.idade, &ReadUser.saldo, &ReadUser.nome[0]))!=EOF){
            fprintf(arq2 ,"%d: %s, %d, %.2f\n",ReadUser.id, ReadUser.nome, ReadUser.idade, ReadUser.saldo);                
        }
    }
    fclose(arq);
    fclose(arq2);
}

// Função criado com objetivo de mostrar para o usuário, todos os usuários presentes no sistema
// Além disso, possui uma forma de separar as informações dos usuários comuns dos administradores
// que possuem uma senha com objetivo de visualizar o banco de dados de maneira mais expositiva 

void MostrarTodos(FILE *arq2, char url[],int senha){
    user ReadUser;
    arq2 = fopen(url,"r");
    if(arq2 == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }else{
        if(senha == 918273645){
            while((fscanf(arq2,"%d/%d/%f/%[^\n]\n",&ReadUser.id, &ReadUser.idade, &ReadUser.saldo, &ReadUser.nome[0]))!=EOF){
            printf("\nID:%d\nNome: %s\nIdade: %d\nSaldo: %.2f\n", ReadUser.id, ReadUser.nome, ReadUser.idade, ReadUser.saldo);
            }
        }else{
            while((fscanf(arq2,"%d/%d/%f/%[^\n]\n",&ReadUser.id, &ReadUser.idade, &ReadUser.saldo, &ReadUser.nome[0]))!=EOF){
            printf("\nNome: %s\nIdade: %d\nSaldo: %.2f\n", ReadUser.nome, ReadUser.idade, ReadUser.saldo);
            }
        }
    }
    fclose(arq2);

}
void Saudacao(){
    puts("-------------------------------------------------------------------------------------\n");
    puts("BBBBBB     AAAAA    NNNN    NNNN   CCCCCC    OOOOOO         UUU   UUU   AAAAA   IIIII\n");
    puts("BB  BBB   AA   AA   NNNNNN  NNNN  CCC       OO    OO       UUU   UUU  AA   AA   III \n");
    puts("BBBBBB  AAAAAAAAA  NNN  NN NNNN CCC       OO    OO         UUU   UUU AAAAAAAAA  III \n");
    puts("BB  BBB  AA     AA  NNN   NNNNNN CCC       OO    OO          UUU   UUU AA     AA  III \n");
    puts("BBBBB   AA     AA  NNN    NNNNN  CCCCCC   OOOOOO            UUUUUU  AA     AA IIIII\n");
    puts("-------------------------------------------------------------------------------------\n");
    puts("-------------------------------Bem vindo ao Banco UaiBANK----------------------------\n");
}
// Para evitar escrever multiplas vezes o menu principal foi construida essa função,
// simplificando assim o entendimento do código principal

void MenuPrincipal(){
    puts("-------------------------------------------------------------------------------------\n");
    puts("-----------------------------------Menu Principal------------------------------------\n");
    puts("-------------------------------------------------------------------------------------\n");
    puts("\nEscolha uma das opcoes abaixo:\n");
    puts("1 - Cadastrar novo usuario.\n");
    puts("2 - Cadastrar novos usuarios.\n");
    puts("3 - Consulta de usuario\n");
    puts("4 - Transferencia.\n");
    puts("5 - Excluir usuario.\n");
    puts("6 - Mostrar todos os usuarios.\n");
    puts("7 - ADMIN: Listar todos os usuarios.\n");
    puts("0 - Sair.\n");
    puts("-------------------------------------------------------------------------------------\n");

}

// De forma análoga a de cima, foi feito uma função para se despedir do usuário

void Adeus(){

    puts("-------------------------------------------------------------------------------------\n");
    puts("--------------------------Obrigado por utilizar o UaiBANK----------------------------\n");
    puts("-------------------------------------------------------------------------------------\n");
    Sleep(2000);

}   
// Função de criação de novo usuário
// Possui como entrada a estrura de controle e a estrutura de Usuario
// a qual pela captação na parte principal do código obteve as informações 
// do usuário
void NovoUsuario(controle Control, user WriteUser){

    printf("Usuario cadastrado com sucesso!\n\nID do %s do usuario: %d\n",WriteUser.nome,WriteUser.id);
    
    FILE *arq;
    // Agora para armazenar as informações adicionadas no arquivo, ele é aberto no modo append, dessa forma adicionando apenas no final as novos informações
    arq = fopen("dados.txt","a");

    //Adiciona no final do ponteiro o novo usuário
    Control.cliente[Control.tamanho - 1]= WriteUser;
    //Redimenciona o tamanho do ponteiro
    Control.cliente = (user*)realloc(Control.cliente,(Control.tamanho + 1) *sizeof(user));
    // Se o redimencionamento falhar ela avisará
    if(Control.cliente == NULL){
        puts("ERRO: Nao foi possivel alocar memoria.\n");
        Control.tamanho = 0;
    }else{
        // senao ele foi redimencionado com sucesso e a variavel de controle possui seu tamanho aumentado em 1
        Control.tamanho++;
    }

    if(arq == NULL){
        printf("ERRO: Nao foi possivel abrir o arquivo\n");
    }else{
        // Escreve no arquivo de controle finalmente as informações do usuário;
        fprintf(arq ,"%d/%d/%.2f/%s\n",WriteUser.id, WriteUser.idade, WriteUser.saldo, WriteUser.nome);
    }

    fclose(arq);

}
// Função com o objetivo de captar o indice do usuário no ponteiro de structs
// sendo utilizado em outra partes do código como uma função complementar as 
// demais.
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

// Função com o objetivo de consultar um usuário especifico através de seu código de id
// Recebe como entrada a struct de controle e o id, e por se tratar de uma void function
// não oferece nenhum retorno
void ConsultarUsuario(controle Control,int id){

    // Pegando o indice do usuario através de seu id;
    int i = PegarPosicao(&Control,id);
    // Como convenção nesse código utilizamos o valor de -1 associado ao id para dizer que um usuário não existe 
    // Pode-se observar que essa convenção foi utilizado durante todo o código em que se é necessário fazer uma
    // manipulação de ids e usuários como controle.
    if(i == -1){
        printf("ERRO: Usuario %d nao encontrado.\n", id);
    }else{
        printf("ID: %d\nNome: %s\nIdade: %d\nSaldo: %.2f\n\n",Control.cliente[i].id, Control.cliente[i].nome, Control.cliente[i].idade, Control.cliente[i].saldo);
    }

}

//Função de tranferência de dinheiro entre os usuários
// Possui como entrada a struct de controle, o id de origem (ido), o id de destino (idd) e o valor a ser tranferido(valor)
void Transferencia(controle Control, int ido, int idd, float valor){
    int i1 = PegarPosicao(&Control,ido);
    int i2 = PegarPosicao(&Control,idd);
    int i;
//REVER SE ESTA FUNCIONANDO DESDE A CRIACAO DE UM NOVO ARQUIVO
    if(Control.cliente[i1].saldo < valor){
        // Faz uma verificação se o usuario com o ido possui saldo suficiente em sua conta
        printf("ERRO: Cliente %s possui saldo insuficiente.\n", Control.cliente[i1].nome);
    }else{
        // Se sim o valor é decrementado de sua conta e incrementado na conta do usário de idd;
        Control.cliente[i1].saldo -= valor;
        Control.cliente[i2].saldo += valor;
        printf("Transferencia realizada com sucesso!\n");
        
        // Como estamos modificando os valores de contas, optamos que a maneira mais simples seria reescrever o
        // arquivo de dados de controle, pois não pensamos em uma maneira mais eficiente de trocar essas informações
        // Por isso o arquivo é aberto em modo w
        FILE *arq2;
        arq2 = fopen("dados.txt","w");
            if(arq2 == NULL){
                printf("ERRO: Nao foi possivel abrir o arquivo\n");
            }else{
                for(i=0; i < (Control.tamanho - 1); i++)
                    fprintf(arq2 ,"%d/%d/%.2f/%s\n",Control.cliente[i].id, Control.cliente[i].idade, Control.cliente[i].saldo, Control.cliente[i].nome);
            }
        fclose(arq2);
    }
}
// obs: está funcionando, mas está estranho
void ExcluirUsuario(controle Control, int ide){
    int i = PegarPosicao(&Control,ide);
    int index;
    if(i > -1){
        for((index = i+1);(index < (Control.tamanho - 1));(index++)){
            Control.cliente[index - 1] = Control.cliente[index];
        }
        Control.tamanho -= 1;
        Control.cliente = (user*)realloc(Control.cliente,(Control.tamanho + 1) * sizeof(user));
        printf("Usuario %d excluido com sucesso!\n", ide);

        FILE *arq2;

        arq2 = fopen("dados.txt","w");
            if(arq2 == NULL){
                printf("ERRO: Nao foi possivel abrir o arquivo\n");
            }else{
                for(i=0; i < (Control.tamanho - 1); i++)
                    fprintf(arq2 ,"%d/%d/%.2f/%s\n",Control.cliente[i].id, Control.cliente[i].idade, Control.cliente[i].saldo, Control.cliente[i].nome);
            }

        fclose(arq2);
    }
}


int main(){

    controle controle;	
    controle.cliente = (user*)malloc(2*sizeof(user));
    controle.tamanho = 1;
    controle.qtd_id = 0;

    char url [] = "dados.txt";
    char url2 [] = "DadosFinais.txt";
    // char nome [100];
    // int id,idade;
    // float saldo;
    user ReadUser;
    user WriteUser;

    int opcao;
    int quantidade;
    int i;
    int id_consulta = 0;
    int id_origem = 0;
    int id_destino = 0;
    int id_exclusao = 0;
    float valor_transferencia = 0;
    int senha;

    //Leitura do arquivo de dados já existente
    FILE *arq;
    arq = fopen(url,"r");
    if(arq != NULL){
        while((fscanf(arq,"%d/%d/%f/%[^\n]\n",&ReadUser.id, &ReadUser.idade, &ReadUser.saldo, &ReadUser.nome[0]))!=EOF){
            // printf("ID: %d\nNome: %s\nIdade: %d\nSaldo: %.2f\n\n",id, nome, idade, saldo);
            controle.cliente = (user*)realloc(controle.cliente,(controle.tamanho + 1) *sizeof(user));
            controle.cliente[controle.tamanho - 1].id = ReadUser.id;
            strcpy(controle.cliente[controle.tamanho - 1].nome,ReadUser.nome);
            controle.cliente[controle.tamanho - 1].idade = ReadUser.idade;
            controle.cliente[controle.tamanho - 1].saldo = ReadUser.saldo;
            controle.tamanho++;
            controle.qtd_id = ReadUser.id;
        }
    }else{
        arq = fopen(url,"w");
    }
    fclose(arq);

    Saudacao();

    do{
        MenuPrincipal();
        scanf("%d",&opcao);

        switch (opcao)
        {
            //Adicionar um novo usuário
        case 1:
            getchar();
            puts("Preeencha suas informacoes abaixo:\n");
            puts("Padrao de preenchimento: Nome, Idade, Saldo\n");
            scanf("%[^,], %d, %f", WriteUser.nome, &WriteUser.idade, &WriteUser.saldo); setbuf(stdin,NULL);
            if(WriteUser.idade < 18){
                puts("ERRO: Voce nao pode se cadastrar, visto que ainda nao possui 18 anos.\n");
                break; 
            }else if (WriteUser.saldo < 0){
                puts("ERRO: Voce nao pode se cadastrar, saldo insuficiente.\n");
                break;
            }
            // Como o id é único, ele é incrementado a cada novo usuário
            controle.qtd_id += 1;
            WriteUser.id = controle.qtd_id;
            NovoUsuario(controle,WriteUser);
            Sleep(2000);
            break;
            //Adicionar vários usuários
        case 2:

            puts("Quantos usuarios deseja cadastrar?\n");
            scanf("%d",&quantidade);
            for(i=0; i < quantidade; i++){
                getchar();
                printf("Preeencha suas informacoes abaixo sobre o usuario: %d.\n",i+1);
                puts("Padrao de preenchimento: Nome, Idade, Saldo\n");
                scanf("%[^,], %d, %f", WriteUser.nome, &WriteUser.idade, &WriteUser.saldo); setbuf(stdin,NULL);
                if(WriteUser.idade < 18){
                    puts("ERRO: Você nao pode se cadastrar, visto que ainda nao possui 18 anos.\n");
                    break; 
                }else if (WriteUser.saldo < 0){
                    puts("ERRO: Você não pode se cadastrar, saldo insuficiente. \n");
                    break;
                }
                // Como o id é único, ele é incrementado a cada novo usuário
                controle.qtd_id += 1;
                WriteUser.id = controle.qtd_id;
                NovoUsuario(controle,WriteUser);
                Sleep(2000);
            }
            break;
            //Consulta de usuário
        case 3:
            getchar();
            puts("Digite o ID do usuario que deseja consultar:\n");
            scanf("%d",&id_consulta); setbuf(stdin,NULL);
            ConsultarUsuario(controle, id_consulta);
            system("pause");
            break;
            //Transferência de saldo
        case 4:
            puts("Digite o ID do usuario que deseja transferir:\n");
            scanf("%d",&id_origem); setbuf(stdin,NULL);
            if(id_origem == 0 || PegarPosicao(&controle,id_origem) == -1){
                puts("ERRO: Voce nao pode transferir de uma conta inexistente.\n");
                break;
            }
            puts("Digite o ID do usuário que deseja receber a transferencia:\n");
            scanf("%d",&id_destino); setbuf(stdin,NULL);
            if(id_destino == 0 || PegarPosicao(&controle,id_destino) == -1){
                puts("ERRO: Voce nao pode transferir para uma conta inexistente.\n");
                break;
            }
            puts("Digite o valor que deseja transferir:\n");
            scanf("%f",&valor_transferencia); setbuf(stdin,NULL);
            if(valor_transferencia < 0){
                puts("ERRO: Voce nao pode transferir um valor negativo.\n");
                break;
            }
            Transferencia(controle,id_origem,id_destino,valor_transferencia);
            system("pause");
            break;
            // Excluir usuário
        case 5:
            puts("Digite o ID do usuario que deseja excluir:\n");
            scanf("%d",&id_exclusao); setbuf(stdin,NULL);
            if(id_exclusao == 0 || PegarPosicao(&controle,id_exclusao) == -1){
                puts("ERRO: Voce nao pode excluir uma conta inexistente.\n");
                system("pause");
                break;
            }
            ExcluirUsuario(controle,id_exclusao);
            system("pause");
            break;
            //Mostrar todos os usuários 
        case 6:
            senha = 0;
            puts("Os usuarios presentes no sistema ate o momento sao:\n");
            MostrarTodos(arq, url, senha);
            system("pause");
            break;
        case 7:
            puts("Digite a senha de administrador: ");
            scanf("%d",&senha); setbuf(stdin,NULL);
            puts("Os usuarios presentes no sistema ate o momento sao:\n");
            MostrarTodos(arq, url, senha);
            system("pause");
            system("cls");
            break;
        case 0:
            Adeus();
            CriarArquivoFormatado(url,url2);
            break;
        default:
            puts("Opção inválida.\n");
            opcao = 0;
            CriarArquivoFormatado(url,url2);
            Adeus();
            break;
        }
    }while(opcao != 0);

    free(controle.cliente);

    return 0;

}