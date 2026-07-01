// Sistema de Territórios - Ataque (WAR) - nível mestre
// Cadastro, listagem e ataque utilizando alocação dinâmica,
// ponteiros, funções e sistema de missões.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR 10
#define TAM_MISSAO 100
#define TOTAL_MISSOES 5

int totalterritorios;

// Estrutura do território
struct Territorio{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// Vetor de missões
char *missoes[TOTAL_MISSOES]={
    "Conquistar 3 territorios",
    "Eliminar exercito Vermelho",
    "Dominar todos os territorios",
    "Controlar metade do mapa",
    "Expandir imperio"
};

// função de limpeza de buffer
void limparBufferdeEntrada(){

    int c;

    while((c=getchar())!='\n' && c!=EOF);

}

// função para sorteio da missão
void atribuirMissao(char *destino,char *missoes[],int totalMissoes){

    int sorteio=rand()%totalMissoes;

    strcpy(destino,missoes[sorteio]);

}

// função para exibir missão
void exibirMissao(char *missao){

    printf("\n=============================\n");
    printf("      SUA MISSAO\n");
    printf("=============================\n");
    printf("%s\n",missao);
    printf("=============================\n");

}

// função para cadastro de territórios
void CadastrarTerritorios(struct Territorio *mapa,int total){

    printf("\n====================================\n");
    printf("----- CADASTRO DOS TERRITORIOS -----\n");
    printf("====================================\n");

    for(int i=0;i<total;i++){

        printf("\nTerritorio %d\n",i+1);

        printf("Nome: ");
        fgets(mapa[i].nome,sizeof(mapa[i].nome),stdin);

        mapa[i].nome[strcspn(mapa[i].nome,"\n")]='\0';

        printf("Cor do exercito: ");
        scanf("%9s",mapa[i].cor);

        printf("Numero de tropas: ");
        scanf("%d",&mapa[i].tropas);

        limparBufferdeEntrada();

    }

}

// função para listar territórios
void listarTerritorios(struct Territorio *mapa,int totalterritorios){

    printf("\n=========================\n");
    printf("========== MAPA =========\n");
    printf("=========================\n");

    if(mapa==NULL){

        return;

    }

    for(int i=0;i<totalterritorios;i++){

        printf("\n[%d]\n",i+1);
        printf("Nome: %s\n",mapa[i].nome);
        printf("Cor: %s\n",mapa[i].cor);
        printf("Tropas: %d\n",mapa[i].tropas);

    }

}

// Verificação da missão
int verificarMissao(char *missao,struct Territorio *mapa,int tamanho){

    int azul=0;
    int vermelho=0;

    for(int i=0;i<tamanho;i++){

        if(strcmp(mapa[i].cor,"Azul")==0)
            azul++;

        if(strcmp(mapa[i].cor,"Vermelho")==0)
            vermelho++;

    }

    if(strcmp(missao,"Conquistar 3 territorios")==0){

        if(azul>=3)
            return 1;

    }

    if(strcmp(missao,"Eliminar exercito Vermelho")==0){

        if(vermelho==0)
            return 1;

    }

    if(strcmp(missao,"Dominar todos os territorios")==0){

        if(azul==tamanho)
            return 1;

    }

    if(strcmp(missao,"Controlar metade do mapa")==0){

        if(azul>=tamanho/2)
            return 1;

    }

    if(strcmp(missao,"Expandir imperio")==0){

        if(azul>=4)
            return 1;

    }

    return 0;

}



int main(){

    srand(time(NULL));

    struct Territorio *mapa = NULL;
    char *missaoJogador = NULL;

    int opcao;
    int a, d;

    // Alocação de memória para a missão
    missaoJogador = (char*) malloc(TAM_MISSAO * sizeof(char));

    if(missaoJogador == NULL){

        printf("Erro ao alocar memoria para a missao.\n");
        return 1;

    }

    // Sorteia e exibe a missão apenas uma vez
    atribuirMissao(missaoJogador, missoes, TOTAL_MISSOES);

    printf("\n====================================");
    printf("\n        BEM-VINDO AO WAR");
    printf("\n====================================");

    exibirMissao(missaoJogador);
    // Menu do jogo 
    do{

        printf("\n===========================\n");
        printf("=========== WAR ===========\n");
        printf("===========================\n");
        printf("1 - Quantidade de Territorios\n");
        printf("2 - Cadastrar Territorios\n");
        printf("3 - Listar Territorios\n");
        printf("4 - Atacar\n");
        printf("0 - Sair\n");
        printf("===========================\n");
        printf("Opcao: ");

        if(scanf("%d",&opcao)!=1){

            limparBufferdeEntrada();
            opcao=-1;
            continue;

        }

        limparBufferdeEntrada();

        switch(opcao){

        case 1:

            printf("\nQuantidade de territorios: ");
            scanf("%d",&totalterritorios);

            limparBufferdeEntrada();

            if(mapa != NULL)
                free(mapa);

            mapa = (struct Territorio*) malloc(totalterritorios * sizeof(struct Territorio));

            if(mapa == NULL){

                printf("Erro de memoria.\n");
                return 1;

            }

            printf("\nMapa criado com sucesso!\n");

            break;

        case 2:

            if(mapa == NULL){

                printf("\nCrie o mapa primeiro.\n");

            }else{

                CadastrarTerritorios(mapa,totalterritorios);

            }

            break;

        case 3:

            if(mapa == NULL){

                printf("\nNenhum mapa criado.\n");

            }else{

                listarTerritorios(mapa,totalterritorios);

            }

            break;

        case 4:

            if(mapa == NULL){

                printf("\nNenhum mapa criado.\n");
                break;

            }

            listarTerritorios(mapa,totalterritorios);

            printf("\nEscolha o territorio atacante: ");
            scanf("%d",&a);

            printf("Escolha o territorio defensor: ");
            scanf("%d",&d);

            limparBufferdeEntrada();

            if(a < 1 || a > totalterritorios ||
               d < 1 || d > totalterritorios){

                printf("\nTerritorio invalido.\n");
                break;

            }

            if(a == d){

                printf("\nUm territorio nao pode atacar a si mesmo.\n");
                break;

            }

            atacar(&mapa[a-1],&mapa[d-1]);

            // Verificação da missão ao final do turno
            if(verificarMissao(missaoJogador,mapa,totalterritorios)){

                printf("\n====================================\n");
                printf("PARABENS!\n");
                printf("VOCE CUMPRIU SUA MISSAO!\n");
                printf("VOCE VENCEU A PARTIDA!\n");
                printf("====================================\n");

                opcao = 0;

            }

            break;

        case 0:

            printf("\nEncerrando o jogo...\n");

            break;

        default:

            printf("\nOpcao invalida.\n");

        }

    }while(opcao != 0);

    liberarMemoria(mapa,missaoJogador);

    printf("\nMemoria liberada com sucesso!\n");

    return 0;

}
