//Sistema de biblioteca - Aventureiro//
// Sistema de Territórios - Ataque (WAR)
// Cadastro, listagem e ataque utilizando alocação dinâmica, ponteiros e funções.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
    //Variáveis de definem o tamanho das string 'nome' e 'cor'
#define TAM_NOME 30
#define TAM_COR 10

    int total;
    int totalterritorios;


// Estrutura do território
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

    // Limpa o buffer de entrada de dados
    void limparBufferdeEntrada() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Cadastro dos territórios
    void CadastrarTerritorios(struct Territorio *mapa, int total) {
        printf("\n====================================\n");
        printf("\n----- CADASTRO DOS TERRITORIOS -----\n");
        printf("\n====================================\n");

        for (int i = 0; i < total; i++){
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);

        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        limparBufferdeEntrada();
        
        }
    }
    // Lista todos os territórios
    void listarTerritorios(struct Territorio *mapa, int totalterritorios) {

        printf("\n========================\n");
        printf("\n========= MAPA =========\n");
        printf("\n========================\n");

        if (mapa == NULL){
        return;
        } else {
            for (int i = 0; i < totalterritorios; i++) {

            printf("\n[%d]\n", i + 1);
            printf("Nome: %s\n", mapa[i].nome);
            printf("Cor: %s\n", mapa[i].cor);
            printf("Tropas: %d\n", mapa[i].tropas);
            }
        }
    }

    // Função de ataque
    void atacar(struct Territorio *atacante, struct Territorio *defensor) {

        // Não permite atacar aliados
        if (strcmp(atacante->cor, defensor->cor) == 0) {

            printf("\n Nao e permitido atacar um territorio aliado.\n");
            return;
        }

        // Atacante precisa de pelo menos 2 tropas
        if (atacante->tropas < 2) {

            printf("\n O atacante nao possui tropas suficientes.\n");
            return;
        }



        printf("\n===================\n");
        printf("\n      BATALHA      \n");
        printf("\n===================\n");

        printf("%s atacou %s\n", atacante->nome, defensor->nome);

        printf("Dado atacante: %d\n", dadoAtacante);
        printf("Dado defensor: %d\n", dadoDefensor);

        if (dadoAtacante > dadoDefensor) {

            printf("\n O ATACANTE venceu!\n");

            strcpy(defensor->cor, atacante->cor);

            int tropasTransferidas = atacante->tropas / 2;

            atacante->tropas -= tropasTransferidas;
            defensor->tropas = tropasTransferidas;

            } else {

            printf("\n O DEFENSOR venceu!\n");

            atacante->tropas--;

            if (atacante->tropas < 1)
            atacante->tropas = 1;
            }

        printf("\n=====================\n");
        printf("\n===== RESULTADO =====\n");
        printf("\n=====================\n");

        printf("%s - Cor: %s - Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);

        printf("%s - Cor: %s - Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
    }

int main() {
    srand(time(NULL));
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    // Variáveis de controle declaradas
    struct Territorio *mapa = NULL; 
    int opcao;
    int a, d; // Variáveis "a = atacante e d = defensor"

    do {
        printf("\n===========================\n");
        printf("\n=========== WAR ===========\n");
        printf("\n===========================\n");
        printf("1 - Quantidade de Territorios.\n");
        printf("2 - Cadastrar Territorios.\n");
        printf("3 - Listar territorios. \n");
        printf("4 - Atacar. \n");
        printf("0 - Sair. \n");
        printf("\n===========================\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparBufferdeEntrada();
            opcao = -1;
            continue;
        }
        limparBufferdeEntrada(); // Limpa o \n do menu para os próximos inputs funcionarem

        switch (opcao) {
            case 1: 
                printf("\n================================================");
                printf("\n----  Delimitando quantidade de territorios ----");
                printf("\n================================================");
                printf("\n---   Digite a quantidade de territorios!   ----\n");
                scanf("%d", &totalterritorios);
                limparBufferdeEntrada();

                // CORREÇÃO: Se já existia um mapa anterior, libera primeiro
                if (mapa != NULL) {
                    free(mapa);
                }

                // CORREÇÃO: Alocação movida para cá, usando a variável 'mapa'
                mapa = malloc(totalterritorios * sizeof(struct Territorio));

                if (mapa == NULL) {
                    printf("Erro crítico ao alocar memoria.\n");
                    return 1;
                }
                printf("\nMemoria alocada para %d territorios com sucesso!\n", totalterritorios);
                printf("\nPressione Enter para continuar...");
                getchar();
                break; // CORREÇÃO: Faltava o break aqui!

            case 2:
                if (mapa == NULL) {
                    printf("\n[Erro] Defina a quantidade de territorios (Opcao 1) primeiro!\n");
                } else {
                    CadastrarTerritorios(mapa, totalterritorios);
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 3:
                if (mapa == NULL) {
                    printf("\nNenhum mapa foi criado ainda.\n");
                } else {
                    listarTerritorios(mapa, totalterritorios);
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 4:
                if (mapa == NULL) {
                    printf("\nNenhum mapa foi criado ainda.\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
                }

                listarTerritorios(mapa, totalterritorios);

                printf("\nEscolha o territorio atacante: ");
                scanf("%d", &a);

                printf("Escolha o territorio defensor: ");
                scanf("%d", &d);
                limparBufferdeEntrada();

                if (a < 1 || a > totalterritorios || d < 1 || d > totalterritorios) {
                    printf("\nTerritorio invalido.\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
                }

                if (a == d) {
                    printf("\nO territorio nao pode atacar a si mesmo.\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    break;
                }

                atacar(&mapa[a - 1], &mapa[d - 1]);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            
            default:
                printf("\nOpcao invalida.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
        }
    } while (opcao != 0);

    // Liberação segura da memória
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemoria liberada com sucesso!\n");
    }

    return 0;
}
