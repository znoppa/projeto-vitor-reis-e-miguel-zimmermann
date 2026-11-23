#include <stdio.h>
#include <string.h>
#include "fragata.h"

int montar_menu(void);

int main(void) {
    int opcao;
    int salvou = 0;
    char codigo[200];

    inicializar_frota();
    carregar_fragatas();

    do {
        opcao = montar_menu();

        switch (opcao) {
            case 1:
                cadastrar_fragata();
                break;

            case 2:
                printf("Codigo da fragata que deseja buscar: ");
                if (fgets(codigo, sizeof(codigo), stdin) != NULL) {
                    codigo[strcspn(codigo, "\r\n")] = '\0';
                    buscar_fragata_por_codigo(codigo);
                }
                break;

            case 3:
                listar_fragatas();
                break;

            case 4:
                gerar_relatorio();
                break;
            case 5:
                printf("Codigo da fragata que deseja editar: ");

                if (fgets(codigo, sizeof(codigo), stdin) != NULL) {
                    codigo[strcspn(codigo, "\r\n")] = '\0';
                    editar_fragata_por_codigo(codigo);
                }
                break;
            case 6:
                printf("Codigo da fragata que deseja excluir: ");

                if (fgets(codigo, sizeof(codigo), stdin) != NULL) {
                    codigo[strcspn(codigo, "\r\n")] = '\0';
                    excluir_fragata_por_codigo(codigo);
                }
                break;
            case 7:
                salvou = salvar_fragatas();

                if (salvou == 1) {
                    printf("A frota foi salva, encerrando o programa.\n");
                } else {
                    printf("Erro ao salvar -> fragatas.txt\n");
                }
                break;
                default:
                printf("Opcao invalida.\n");
                break;
            }
    } while (salvou == 0 && opcao != -1);

    liberar_frota();

    if (salvou == 0) {
        return 1;
    }

    return 0;
}

int montar_menu(void) {
    char linha[200];
    char extra;
    int opcao;

    printf("\n --=-=-=-- Gestao de Frota e Manutencao de Fragatas --=-=-=-- \n");
    printf("1. Cadastrar fragata\n");
    printf("2. Buscar fragata por codigo\n");
    printf("3. Listar fragatas\n");
    printf("4. Exibir relatorio\n");
    printf("5. Editar fragata\n");
    printf("6. Excluir fragata\n");
    printf("7. Salvar e sair\n");
    printf("Escolha uma opcao: ");

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return -1;
    }

    if (sscanf(linha, "%d %c", &opcao, &extra) != 1) {
        return 0;
    }

    return opcao;
}
