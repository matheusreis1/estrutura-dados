typedef struct cidade {
    char descricao;
    char nome;
    struct cidade *proximo;
    struct cidade *anterior;
} Cidade;

typedef struct cidadeHeader {
    int quantidade;
    Cidade *primeiro, *ultimo;
} CidadeHeader;

typedef struct rota {
    CidadeHeader *cidades;
    struct rota *proximo;
} Rota;

void inicia_lista_rotas(Rota ** rotas);
Rota * criar_rota();
void inserir_rota(Rota **rotas, char nomeRota, CidadeHeader *cidades);
void excluir_rota(Rota **rotas, char nomeRota);
void acessar_rota(Rota **rotas, char nomeRota); // busca ate achar o nome e entra no array de cidades

void inicializa_lista_cidades(CidadeHeader *cidades);
Cidade * criar_cidade();
void inserir_cidade(CidadeHeader *cidades, char nomeCidade, char descricaoCidade);
void apresentar_cidades(CidadeHeader *cidades);
