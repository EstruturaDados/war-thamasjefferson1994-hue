//Sistema de biblioteca - Novato//
// Implementar o cadastro e alistagem de livros usando array estatico //
#include <stdio.h> //
#include <string.h> // para strcspn()

// constantes globais 
#define MAX_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// Definição da estrutura (struct)
struct Territorio{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// função para limpar o buffer de entrada//
void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// função principal

int main() {
    struct Territorio territorios[MAX_TERRITORIOS];
    int totalterritorios = 0;
    int opcao;


    //laço principal do menu

    do{

        // exibe o menu de opções 
        printf("==========================\n");
        printf("      Territorios - Parte 01\n");
        printf("==========================\n");
        printf("1 - Cadastrar Novo Território\n");
        printf("2 - Listar Todos Os Territórios\n");
        printf("0 - Sair\n");
        printf("--------------------------\n");
        printf("Escolha uma opção: ");

        // Lê a opção do usuário.
        scanf("%d", &opcao);
        limparbufferentrada(); //Limpa o '\n' deixado pelo scanf.
        
        //Processamento da opção.

        switch (opcao){
            case 1: //Cadastro de territórios
                printf("--- Cadastro de novo Território ---\n\n"); 

                if(totalterritorios < MAX_TERRITORIOS){
                    printf("Digite o nome do território: ");
                    scanf("%s", &territorios->nome);

                    printf("Digite a cor ex(azul amarelo): ");
                    scanf("%s", &territorios->cor);

                    printf("Digite o número de tropas: ");
                    scanf("%d", &territorios->tropas);


                 totalterritorios++;
                }
            break;
            case 2: // imprime terrítórios e atributos na tela
                printf("============================\n\n");
                printf("---     MAPA DO MUNDO    ---\n\n");
                printf("============================\n\n");

                //loop de impressão até imprimir os 5 territórios
                
                for(int i = 0; i < totalterritorios; i++){
                        printf("-----------------------------\n");
                        printf("Território %d\n", i + 1);
                        printf("Nome: %s\n", &territorios[i].nome);
                        printf("Dominado por: %s\n", &territorios[i].cor);
                        printf("Tropas: %d\n", &territorios[i].tropas);

                
                    printf("------------------------------");
                }


                printf("\n Pressione Enter para continuar...");
                getchar();
                
             break;
            case 0: //sair
                printf("\nSaindo do sistema... \n");
            break;
            default: //opção inválida
                printf("\nOpção inválida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();

             break;

        }

    }while (opcao != 0);

return 0;

}

