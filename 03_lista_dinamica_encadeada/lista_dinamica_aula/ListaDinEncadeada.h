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
