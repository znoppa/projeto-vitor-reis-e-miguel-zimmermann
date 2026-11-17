#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fragata.h"

#define ARQUIVO_FROTA "fragatas.txt"

p_fragata frota[MAX_FRAGATAS];

void inicializar_frota(void) {
    for (int i = 0; i < MAX_FRAGATAS; i++) {
        frota[i] = NULL;
    }
}

void cadastrar_fragata(void) {
    Fragata fragata;
    char linha[200];
    char extra;

    printf("Codigo: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return;
    }
    linha[strcspn(linha, "\r\n")] = '\0';
    if (linha[0] == '\0' || strlen(linha) >= sizeof(fragata.codigo)) {
        printf("digite um codigo de ate 15 caracteres \n");
        return;
    }
    strcpy(fragata.codigo, linha);

    if (buscar_posicao_por_codigo(fragata.codigo) != -1) {
        printf("ja existe uma fragata com esse codigo! \n");
        return;
    }

    printf("Modelo: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return;
    }
    linha[strcspn(linha, "\r\n")] = '\0';
    if (linha[0] == '\0' || strlen(linha) >= sizeof(fragata.modelo)) {
        printf("digite um modelo de ate 50 caracteres.\n");
        return;
    }
    strcpy(fragata.modelo, linha);

    printf("Ano de fabricacao: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL || sscanf(linha, "%4d %c", &fragata.ano_fabricacao, &extra) != 1) {
        printf("Ano invalido \n");
        return;
    }

    printf("Distancia percorrida em anos-luz: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL ||
        sscanf(linha, "%lf %c", &fragata.distancia_percorrida, &extra) != 1) {
        // avisar sobre o . como separador decimal, testei e percebi que tem q avisar
        printf("Distancia invalida, use (.) ponto decimal \n");
        return;
    }

    printf("Valor da revisao em unidades: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL ||
        sscanf(linha, "%lf %c", &fragata.valor_revisao, &extra) != 1) {
        printf("Valor invalido, use (.) ponto decimal.\n");
        return;
    }

    if (guardar_fragata(fragata) == 1) {
        printf("Fragata cadastrada com sucesso.\n");
    } else {
        printf("Ocorreu um erro no cadastro, confira os dados e o espaco na frota.\n");
    }
}

// usar essa função tanto no cadastro quanto na leitura
int guardar_fragata(Fragata fragata) {
    if (fragata.codigo[0] == '\0' || fragata.modelo[0] == '\0' ||
        strchr(fragata.codigo, ';') != NULL ||
        strchr(fragata.modelo, ';') != NULL ||
        fragata.ano_fabricacao < 1 || fragata.ano_fabricacao > 9999) {
        return 0;
    }

    if (fragata.distancia_percorrida < 0 || fragata.valor_revisao < 0) {
        return 0;
    }

    if (buscar_posicao_por_codigo(fragata.codigo) != -1) {
        return 0;
    }

    for (int i = 0; i < MAX_FRAGATAS; i++) {
        if (frota[i] == NULL) {
            frota[i] = malloc(sizeof(Fragata));
            if (frota[i] == NULL) {
                return 0;
            }

            *frota[i] = fragata;
            return 1;
        }
    }

    return 0;
}

int buscar_posicao_por_codigo(char codigo[]) {
    for (int i = 0; i < MAX_FRAGATAS; i++) {
        if (frota[i] != NULL && strcmp(frota[i]->codigo, codigo) == 0) {
            return i;
        }
    }

    return -1;
}

void buscar_fragata_por_codigo(char codigo[]) {
    int posicao = buscar_posicao_por_codigo(codigo);

    if (posicao == -1) {
        printf("Fragata nao encontrada.\n");
    } else {
        imprimir_fragata(posicao);
    }
}

void imprimir_fragata(int posicao) {
    printf("\n //-----------------========------------------//");
    printf("\nCodigo: %s \n", frota[posicao]->codigo);
    printf("Modelo: %s \n", frota[posicao]->modelo);
    printf("Ano de fabricacao: %d \n", frota[posicao]->ano_fabricacao);
    printf("Distancia percorrida: %.2f anos-luz \n",frota[posicao]->distancia_percorrida);
    printf("Valor da revisao: %.2f unidades \n", frota[posicao]->valor_revisao);
    printf("\n //-----------------========------------------// \n ");
}

void listar_fragatas(void) {
    int total = 0;
    for (int i = 0; i < MAX_FRAGATAS; i++) {
        if (frota[i] != NULL) {
            imprimir_fragata(i);
            total++;
        }
    }

    if (total == 0) {
        printf("Nenhuma fragata cadastrada.\n");
    }
}

void gerar_relatorio(void) {
    int pos_maior = -1;
    int total = 0;
    double soma_revisoes = 0;

    for (int i = 0; i < MAX_FRAGATAS; i++) {
        if (frota[i] != NULL) {
            total++;
            soma_revisoes += frota[i]->valor_revisao;

            if (pos_maior == -1 || frota[i]->distancia_percorrida >
                frota[pos_maior]->distancia_percorrida) {
                pos_maior = i;
            }
        }
    }

    if (total == 0) {
        printf("Nenhuma fragata cadastrada \n");
        return;
    }

    printf("Fragata que mais viajou: \n");
    imprimir_fragata(pos_maior);
    printf("Custo medio de revisao: %.2f unidades \n", soma_revisoes / total);
}

void carregar_fragatas(void) {
    FILE *p_arq = fopen(ARQUIVO_FROTA, "r");
    char linha[200];
    char extra;
    Fragata fragata;

    if (p_arq == NULL) {
        return;
    }

    while (fgets(linha, sizeof(linha), p_arq) != NULL) {
        if (sscanf(linha, "%15[^;\r\n];%50[^;\r\n];%4d;%lf;%lf %c", fragata.codigo, fragata.modelo, &fragata.ano_fabricacao,
            &fragata.distancia_percorrida, &fragata.valor_revisao, &extra) == 5) {
            guardar_fragata(fragata);
        }
    }

    fclose(p_arq);
}

int salvar_fragatas(void) {
    FILE *p_arq = fopen(ARQUIVO_FROTA, "w");

    if (p_arq == NULL) {
        return 0;
    }

    for (int i = 0; i < MAX_FRAGATAS; i++) {
        if (frota[i] != NULL) {
            if (fprintf(p_arq, "%s;%s;%d;%.17g;%.17g\n",
                        frota[i]->codigo, frota[i]->modelo,
                        frota[i]->ano_fabricacao, frota[i]->distancia_percorrida,
                        frota[i]->valor_revisao) < 0) {
                fclose(p_arq);
                return 0;
            }
        }
    }

    return fclose(p_arq) == 0;
}

void liberar_frota(void) {
    for (int i = 0; i < MAX_FRAGATAS; i++) {
        if (frota[i] != NULL) {
            free(frota[i]);
            frota[i] = NULL;
        }
    }
}
