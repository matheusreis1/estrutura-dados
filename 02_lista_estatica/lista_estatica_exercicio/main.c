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
  if (lista == NULL)
    return 0;
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
  if (lista == NULL || lista_cheia(lista))
    return 0;

  int i, k = 0;

  while (i < lista->fim && lista->dados[i].dado < dado.dado)
    i++;

  for (k = lista->fim - 1; k >= i; k--)
    lista->dados[k+1] = lista->dados[k];

  lista->dados[i] = dado;
  lista->fim++;

  return 1;
}

int remover_lista_inico(ListaLinearEstatica * lista) {
  if (lista == NULL || lista_vazia(lista))
    return 0;

  int i;

  for (i; i <= lista->fim - 1; i++)
    lista->dados[i] = lista->dados[i + 1];

  lista->fim--;

  return 1;
}
int remover_lista_fim(ListaLinearEstatica * lista) {
  if (lista == NULL || lista_vazia(lista))
    return 0;

  lista->fim--;
  return 1;
}
int remover_lista_meio(ListaLinearEstatica * lista, int dado) {
  if (lista == NULL || lista_cheia(lista))
    return 0;

  int i, k = 0;

  while (i < lista->fim && lista->dados[i].dado != dado)
    i++;

  if (i == lista->fim)
    return 0;

  for (k = i; k < lista->fim - 1; k++)
    lista->dados[k] = lista->dados[k+1];

  lista->fim--;

  return 1;
}

int consulta_lista_conteudo(ListaLinearEstatica * lista, int dado, ED_LE * dado_struct) {
  if (lista == NULL || lista_vazia(0))
    return 0;

  int i, k = 0;

  while (i < lista->fim && lista->dados[i].dado != dado)
    i++;

  if (i == lista->fim)
    return 0;
  
  *dado_struct = lista->dados[i];
  return 1;
}
int consulta_lista_posicao(ListaLinearEstatica * lista, int posicao, ED_LE * dado_struct) {
  if (lista == NULL || lista_vazia(lista) || posicao <= 0 || posicao > lista->fim)
    return 0;
  
  *dado_struct = lista->dados[posicao - 1];
  return 1;
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
      "5 - Inserir no meio (ordenado)\n"  
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
        lista = NULL;
        break;
      case 3:
        printf("Opcao %d\n - Inserir no começo\n", opcao_menu);
        printf("Insira o valor do dado\n");
        ED_LE dado_inicio;
        int dado_inicio_lista;
        scanf("%d", &dado_inicio_lista);
        dado_inicio.dado = dado_inicio_lista;
        inserir_lista_inicio(lista, dado_inicio);
        break;
      case 4:
        printf("Opcao %d\n - Inserir no fim\n", opcao_menu);
        printf("Insira o valor do dado\n");
        ED_LE dado_final;
        int dado_final_lista;
        scanf("%d", &dado_final_lista);
        dado_final.dado = dado_final_lista;
        inserir_lista_fim(lista, dado_final);
        break;
      case 5:
        printf("Opcao %d\n - Inserir no meio (ordenado)\n", opcao_menu);
        printf("Insira o valor do dado\n");
        ED_LE dado_meio;
        int dado_meio_lista;
        scanf("%d", &dado_meio_lista);
        dado_meio.dado = dado_meio_lista;
        inserir_lista_meio(lista, dado_meio);
        break;
      case 6:
        printf("Opcao %d\n - Remover do início\n", opcao_menu);
        remover_lista_inico(lista);
        break;
      case 7:
        printf("Opcao %d\n - Remover do fim\n", opcao_menu);
        remover_lista_fim(lista);
        break;
      case 8:
        printf("Opcao %d\n - Remover do meio\n", opcao_menu);
        printf("Insira o valor do dado que deseja remover\n");
        int dado_remover_meio_lista;
        scanf("%d", &dado_remover_meio_lista);
        remover_lista_meio(lista, dado_remover_meio_lista);
        break;
      case 9:
        printf("Opcao %d\n - Consultar pelo conteúdo\n", opcao_menu);
        int dado_consultar_conteudo;
        scanf("%d", &dado_consultar_conteudo);
        ED_LE dado_struct_consultar_conteudo;
        
        int encontrou_conteudo = consulta_lista_conteudo(lista, dado_consultar_conteudo, &dado_struct_consultar_conteudo);
        if (encontrou_conteudo)
          printf("Encontrado!:\n");
          imprimir_item(dado_struct_consultar_conteudo);

        break;
      case 10:
        printf("Opcao %d\n - Consultar pela posição\n", opcao_menu);
        int dado_consultar_posicao;
        scanf("%d", &dado_consultar_posicao);
        ED_LE dado_struct_consultar_posicao;
        
        int encontrou_posicao = consulta_lista_posicao(lista, dado_consultar_posicao, &dado_struct_consultar_posicao);
        if (encontrou_posicao)
          printf("Encontrado!:\n");
          imprimir_item(dado_struct_consultar_posicao);
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
