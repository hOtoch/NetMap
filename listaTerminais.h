#ifndef listaTerminais_h
#define listaTerminais_h

#include "terminal.h"

typedef struct celula_t Celula_T;

typedef struct ListaDeTerminais ListaTerm;

ListaTerm* CriaListaTerm(); // cria a lista de terminais

Terminal* retornaTerm(Celula_T* cel); // retorna o terminal de uma celula T

void DesconectaTerminal(Celula_T* cel); // desconecta um terminal de um roteador

void CadastraTerminal(int id,char* nome,char* loc,ListaTerm* lista); // Cadastra um terminal a lista

void RemoveTerminal(Celula_T* CelTerm,ListaTerm* listaT,FILE* log); // Remove um terminal da lista

void FrequenciaTerminal(ListaTerm* listaT , char* loc,FILE* saida); // Imprime a quantidade de terminais cadastrados em uma localização

void ConectaTerminal(Celula_T* term,Celula_R* rot); //  conecta um terminal a um roteador

void ImprimeListaTerm(ListaTerm* listaT); // Imprime a lista de terminais

void EnviaPacotesDados(Celula_T* CelTerm1, Celula_T* CelTerm2,FILE*saida); // verifica se é possivel enviar dados do term1 para o term2

Celula_T* buscaCelTerminal(char* nomeTerm,ListaTerm* lista, FILE* log); // busca uma celula do tipo T pelo nome do seu terminal na lista de terminais

void LiberaListaTerm(ListaTerm* listaT); // Libera a lista de terminais

#endif

