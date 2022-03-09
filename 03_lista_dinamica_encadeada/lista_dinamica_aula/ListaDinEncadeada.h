typedef struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
} Aluno;
typedef struct elemento * Lista;

Lista * cria_lista();
void libera_lista(Lista * li);

int tamanho_lista(Lista * li);
int lista_cheia(Lista * li); // lista dinamica encadeada nunca esta cheia, apenas quando a memoria do computador acaba.
int lista_vazia(Lista * li);

int insere_lista_inicio(Lista * li, Aluno aluno);
int insere_lista_final(Lista * li, Aluno aluno);
int insere_lista_ordenada(Lista * li, Aluno aluno);

int remove_lista_inicio(Lista * li);
int remove_lista_final(Lista * li);
int remove_lista(Lista * li, int matricula);

int consulta_lista_posicao(Lista * li, int posicao, Aluno * aluno);
int consulta_lista_matricula(Lista * li, int matricula, Aluno * aluno);
