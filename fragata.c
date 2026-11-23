#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fragata.h"

#define ARQUIVO_FROTA "fragatas.txt"
#define ANO_ATUAL 2500

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

int excluir_fragata_por_codigo(char codigo[]){
    int posicao = buscar_posicao_por_codigo(codigo);

    if (posicao == -1) {
        printf("Fragata nao encontrada.\n");
        return 0;
    }

    free(frota[posicao]);
    frota[posicao] = NULL;
    return 1;
}

void editar_fragata_por_codigo(char codigo[]) {
    int posicao = buscar_posicao_por_codigo(codigo);
    char linha[200];
    char extra;
    Fragata novos_dados;

    if (posicao == -1) {
        printf("Fragata nao encontrada.\n");
        return;
    }

    /* Mantém o código, pois ele é o identificador da fragata. */
    strcpy(novos_dados.codigo, frota[posicao]->codigo);

    printf("Novo modelo: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return;
    }

    linha[strcspn(linha, "\r\n")] = '\0';

    if (linha[0] == '\0' ||
        strlen(linha) >= sizeof(novos_dados.modelo) ||
        strchr(linha, ';') != NULL) {
        printf("Modelo invalido.\n");
        return;
    }

    strcpy(novos_dados.modelo, linha);

    printf("Novo ano de fabricacao: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL ||
        sscanf(linha, "%4d %c", &novos_dados.ano_fabricacao, &extra) != 1 ||
        novos_dados.ano_fabricacao < 1 ||
        novos_dados.ano_fabricacao > 9999) {
        printf("Ano invalido.\n");
        return;
    }

    printf("Nova distancia percorrida: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL ||
        sscanf(linha, "%lf %c", &novos_dados.distancia_percorrida, &extra) != 1 ||
        novos_dados.distancia_percorrida < 0) {
        printf("Distancia invalida.\n");
        return;
    }

    printf("Novo valor da revisao: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL ||
        sscanf(linha, "%lf %c", &novos_dados.valor_revisao, &extra) != 1 ||
        novos_dados.valor_revisao < 0) {
        printf("Valor invalido.\n");
        return;
    }

    *frota[posicao] = novos_dados;
    printf("Fragata atualizada com sucesso.\n");
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
    int pos_maior_distancia = -1;
    int pos_revisao_mais_cara = -1;
    int total = 0;

    double soma_revisoes = 0;
    double soma_anos = 0;

    for (int i = 0; i < MAX_FRAGATAS; i++) {
        if (frota[i] == NULL) {
            continue;
        }

        total++;
        soma_revisoes += frota[i]->valor_revisao;
        soma_anos += frota[i]->ano_fabricacao;

        if (pos_maior_distancia == -1 ||
            frota[i]->distancia_percorrida >
            frota[pos_maior_distancia]->distancia_percorrida) {
            pos_maior_distancia = i;
        }

        if (pos_revisao_mais_cara == -1 ||
            frota[i]->valor_revisao >
            frota[pos_revisao_mais_cara]->valor_revisao) {
            pos_revisao_mais_cara = i;
        }
    }

    if (total == 0) {
        printf("Nenhuma fragata cadastrada.\n");
        return;
    }

    double idade_media = ANO_ATUAL - (soma_anos / total);

    printf("\nRELATORIO DE FROTA\n");
    printf("Total de fragatas: %d\n", total);
    printf("Custo total das revisoes: %.2f unidades\n",
           soma_revisoes);
    printf("Custo medio das revisoes: %.2f unidades\n",
           soma_revisoes / total);
    printf("Ano medio de fabricacao: %.1f\n",
           soma_anos / total);
    printf("Idade media das fragatas: %.1f anos\n", idade_media);

    printf("\nFragata que percorreu a maior distancia:\n");
    imprimir_fragata(pos_maior_distancia);

    printf("\nFragata com a revisao mais cara:\n");
    imprimir_fragata(pos_revisao_mais_cara);
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
