#ifndef listaRoteadores_h
#define listaRoteadores_h

#include "roteador.h"

#include <stdio.h>
#include <stdlib.h>




typedef struct celula_r Celula_R;

typedef struct ListaDeRoteadores ListaRot;


ListaRot* CriaListaRot(); // cria a lista de roteadores



void CadastraRoteador(ListaRot* lista,int idRot,char* nomeRot,char* nomeOperadora);// Cadastra o roteador na lista de roteadores

void RemoveRoteador(Celula_R* cel,ListaRot* listaR);// Remove o roteador da lista de roteadores

void FrequenciaOperadora(ListaRot* listaR,char* operadora, FILE* saida); // Imprime a quantidade de roteadores cadastrados de uma operadora

Roteador* retornaRot(Celula_R* cel); // retorna o roteador de uma celula R

void ConectaRoteadoresEnlaces(Celula_R* cel1,Celula_R* cel2); // conecta dois roteadores

void DesconectaRoteadoresEnlaces(Celula_R* cel1,Celula_R* cel2,FILE* log); // desconecta dois roteadores

void ImprimeListaRot(ListaRot* listaR);// Printa a lista de roteadores

Celula_R* buscaCelRot(char* nomeRot,ListaRot* lista, FILE* log); // busca uma celula R pelo nome do roteador dela na lista de roteadores

int verificaRoteador(Celula_R* cel,ListaRot* lista); // verifica se o roteador existe na lista de roteadores

void LiberaListaRot(ListaRot* listaR);// Destroi a lista de roteadores


#endif
