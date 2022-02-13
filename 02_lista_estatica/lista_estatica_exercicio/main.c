#include <stdio.h>
#include "ListaEstatica.h"

ListaLinearEstatica * criar_lista() {
  ListaLinearEstatica * lista;
  lista = (ListaLinearEstatica*) malloc(sizeof(ED_LE));
  if (lista != NULL)
    lista->fim = 0;
  return lista;
}
void liberar_lista(ListaLinearEstatica * lista) {
  free(lista);
}

int lista_cheia(ListaLinearEstatica * lista) {
  if (lista == NULL)
    return -1;
  return (lista->fim == MAX);
}
int lista_vazia(ListaLinearEstatica * lista) {
  if (lista == NULL)
    return -1;
  return (lista->fim == 0);
}

int inserir_lista_inicio(ListaLinearEstatica * lista, ED_LE dado) {
  if (lista == NULL || lista_cheia(lista)) 
    return 0;
  
  int i;

  for (i = lista->fim - 1; i >= 0; i--)
    lista->dados[i+1] = lista->dados[i];
  
  lista->dados[0] = dado;
  lista->fim++;

  return 1;
}
int inserir_lista_fim(ListaLinearEstatica * lista, ED_LE dado) {
  if (lista == NULL || lista_cheia(lista))
    return 0;
  
  lista->dados[lista->fim] = dado;
  lista->fim++;
  return 1;
}
int inserir_lista_meio(ListaLinearEstatica * lista, ED_LE dado) {

}

int remover_lista_inico(ListaLinearEstatica * lista) {

}
int remover_lista_fim(ListaLinearEstatica * lista) {

}
int remover_lista_meio(ListaLinearEstatica * lista, int dado) {

}

int consulta_lista_conteudo(ListaLinearEstatica * lista, int dado, ED_LE * dado_struct) {

}
int consulta_lista_posicao(ListaLinearEstatica * lista, int posicao, ED_LE * dado_struct) {

}

void imprimir_item(ED_LE dado) {
  printf("Dado: %d\n", dado.dado);
}
void imprimir_lista(ListaLinearEstatica * lista) {
  if (lista == NULL || lista_vazia(lista))
    return 0;
  
  int i;

  for (i; i <= lista->fim - 1; i++)
    imprimir_item(lista->dados[i]);
}


int main() {
  int fim;
  int opcao_menu;

  while (!fim) {
    ListaLinearEstatica * lista;

    printf("\n"
      "1 - Criar lista estática\n"
      "2 - Liberar lista estática\n"
      "3 - Inserir no começo\n"
      "4 - Inserir no fim\n"
      "5 - Inseir no meio (ordenado)\n"  
      "6 - Remover do início\n"  
      "7 - Remover do fim\n"  
      "8 - Remover do meio\n"  
      "9 - Consultar pelo conteúdo\n"  
      "10 - Consultar pela posição\n"  
      "11 - Imprimir lista estática\n"  
      "12 - Sair\n"  
      );
    scanf("%d", &opcao_menu);
    switch (opcao_menu) {
      case 1:
        printf("Opcao %d - Criar lista estática\n", opcao_menu);
        lista = criar_lista();
        break;
      case 2:
        printf("Opcao %d\n - Liberar lista estática\n", opcao_menu);
        liberar_lista(lista);
        break;
      case 3:
        printf("Opcao %d\n - Inserir no começo\n", opcao_menu);
        printf("Insira o valor do dado\n");
        ED_LE dado;
        int dado_inteiro;
        scanf("%d", &dado_inteiro);
        dado.dado = dado_inteiro;
        inserir_lista_inicio(lista, dado);
        break;
      case 4:
        printf("Opcao %d\n - Inserir no fim\n", opcao_menu);
        break;
      case 5:
        printf("Opcao %d\n - Inseir no meio (ordenado)\n", opcao_menu);
        break;
      case 6:
        printf("Opcao %d\n - Remover do início\n", opcao_menu);
        break;
      case 7:
        printf("Opcao %d\n - Remover do fim\n", opcao_menu);
        break;
      case 8:
        printf("Opcao %d\n - Remover do meio\n", opcao_menu);
        break;
      case 9:
        printf("Opcao %d\n - Consultar pelo conteúdo\n", opcao_menu);
        break;
      case 10:
        printf("Opcao %d\n - Consultar pela posição\n", opcao_menu);
        break;
      case 11:
        printf("Opcao %d\n - Imprimir lista estática\n", opcao_menu);\
        imprimir_lista(lista);
        break;
      case 12:
        printf("Opcao %d\n - Sair\n", opcao_menu);
        fim = 1;
        break;
      default:
        printf("Opção inválida, digite novamente\n");
        break;
    }
  }
}

/*
*/
