
#ifndef FRAGATA_H
#define FRAGATA_H

#define MAX_FRAGATAS 100

typedef struct {
    char codigo[16];
    char modelo[51];
    int ano_fabricacao;
    double distancia_percorrida;
    double valor_revisao;
} Fragata;

typedef Fragata *p_fragata;
extern p_fragata frota[MAX_FRAGATAS];

// Inicializa o vetor de ponteiros com NULL em todas as posições
void inicializar_frota(void);

// Cadastrar uma fragata nova no sistema
void cadastrar_fragata(void);

// Salvar a fragata no sistema
int guardar_fragata(Fragata fragata);

// Encontrar a posição no indice
int buscar_posicao_por_codigo(char codigo[]);

// Buscar a Fragata pelo código dela
void buscar_fragata_por_codigo(char codigo[]);

// Mostrar a fragata
void imprimir_fragata(int posicao);

// Editar uma fragata
void editar_fragata_por_codigo(char codigo[]);

// Exlcuir uma fragata
int excluir_fragata_por_codigo(char codigo[]);

// Mostrar todas as fragatas
void listar_fragatas(void);

// Exibir o relatório de fragata mais rodada e custo médio de revisão.
void gerar_relatorio(void);

// Carregar as fragatas do arquivo
void carregar_fragatas(void);

// Salvar as fragastas no arquivo
int salvar_fragatas(void);

//Libera com free() toda a memoria alocada dinamicamente e aterra os ponteiros
void liberar_frota(void);

#endif