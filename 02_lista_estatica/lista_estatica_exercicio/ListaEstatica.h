#define MAX 5

typedef struct ed_le {
    int dado;
} ED_LE;
struct lista_linear_estatica {
    int fim;
    ED_LE dados[MAX];
};
typedef struct lista_linear_estatica ListaLinearEstatica;

ListaLinearEstatica * criar_lista();
void liberar_lista(ListaLinearEstatica * lista);

int lista_cheia(ListaLinearEstatica * lista);
int lista_vazia(ListaLinearEstatica * lista);

int inserir_lista_inicio(ListaLinearEstatica * lista, ED_LE dado);
int inserir_lista_fim(ListaLinearEstatica * lista, ED_LE dado);
int inserir_lista_meio(ListaLinearEstatica * lista, ED_LE dado);

int remover_lista_inico(ListaLinearEstatica * lista);
int remover_lista_fim(ListaLinearEstatica * lista);
int remover_lista_meio(ListaLinearEstatica * lista, int dado);

int consulta_lista_conteudo(ListaLinearEstatica * lista, int dado, ED_LE * dado_struct);
int consulta_lista_posicao(ListaLinearEstatica * lista, int posicao, ED_LE * dado_struct);

void imprimir_item(ED_LE dado);
void imprimir_lista(ListaLinearEstatica * lista);
