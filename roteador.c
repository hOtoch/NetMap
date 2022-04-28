#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "roteador.h"

struct roteador{
    int id;
    char* nome;
    char* operadora;
    Enlaces* listaEnlaces;
};

Enlaces* retornaEnlaces(Roteador* rot){
    return rot->listaEnlaces;

}




Roteador* CriaRoteador(int id,char* nome,char* operadora){
    Roteador* rot = (Roteador*)malloc(sizeof(Roteador));

    rot->id = id;
    rot->nome = strdup(nome);
    rot->operadora = strdup(operadora);

    rot->listaEnlaces = criaListaEnlaces();

    return rot;
}

int retornaIdRot(Roteador* rot){
    return rot->id;
}

char* retornaNomeRot(Roteador* rot){
    return rot->nome;
}

char* retornaOperadoraRot(Roteador* rot){
    return rot->operadora;
}


void ImprimeRoteador(Roteador* rot){
        
    printf("Nome do roteador: %s\nId do roteador: %d\nOperadora do roteador: %s\n",rot->nome,rot->id,rot->operadora);
    
    
}

void LiberaRoteador(Roteador* rot){
    free(rot->nome);
    free(rot->operadora);
    free(rot);
}


// -------------------------------------------------------------------------


struct celula_e{
    Celula_E* prox;
    Roteador* rot;
};

struct enlaces{
    Celula_E* prim;
    Celula_E* ult;
    int *tamanho;
};


void adicionaRotCelE(Celula_E* cel, Roteador* roteador){
    cel->rot = roteador;
}

Celula_E* retornaPrimEnlaces(Enlaces* enlaces){
    return enlaces->prim;
}

Celula_E* retornaUltEnlaces(Enlaces* enlaces){
   return enlaces->ult;
}

int* retornaTamanhoEnlaces(Enlaces* enlaces){
    return enlaces->tamanho;
}

Celula_E* retornaProxEnlaces(Celula_E* cel){
    return cel->prox;
}

Celula_E* buscaRoteadorEnlaces(Roteador* rot, Enlaces* lista, FILE* log,Roteador* rot2){
    int idRot = retornaIdRot(rot);

    Celula_E* p;
    int existeRot = 0;
    int listaVazia = 1;
    Roteador* rotP;

    for(p=retornaPrimEnlaces(lista);p!=NULL;p=retornaProxEnlaces(p)){
        listaVazia = 0;
        rotP = retornaRotEnlaces(p);
        if(retornaIdRot(retornaRotEnlaces(p))==idRot){
            return p;
            existeRot = 1;      
        }
    }
    if(existeRot==0 && listaVazia == 0){
        fprintf(log,"ERRO: O roteador %s nao esta conectado com o roteador %s.\n",retornaNomeRot(rot),retornaNomeRot(rot2));   
        return NULL;           
     }

    else if(listaVazia == 1){
        fprintf(log,"O roteador %s nao possui conexoes.\n",retornaNomeRot(rot2)); 
        return NULL;      
     }
}

Enlaces* criaListaEnlaces(){
    Enlaces* listaEnlaces = (Enlaces*)malloc(sizeof(Enlaces));

    listaEnlaces->prim = NULL;
    listaEnlaces->ult = NULL;

    listaEnlaces->tamanho = 0;

    return listaEnlaces;
}

Roteador* retornaRotEnlaces(Celula_E* cel){
    return cel->rot;
}

Enlaces* CadastraRoteadorEnlaces(Enlaces* listaEnlaces,Celula_E* cel){
    cel->prox = NULL;


    if(listaEnlaces->prim != NULL){
        listaEnlaces->ult->prox = cel;
        listaEnlaces->ult = cel;
    }
    else{
        
        listaEnlaces->prim = cel;
        listaEnlaces->ult = cel;
    }

    listaEnlaces->tamanho = (listaEnlaces->tamanho) + 1;

    return listaEnlaces;
}




void RemoveRoteadorEnlaces(Celula_E* cel,Enlaces* lista){
    Celula_E* p = lista->prim;
    Celula_E* ant = NULL;

    while(p!=NULL && retornaIdRot(p->rot)!=retornaIdRot(retornaRotEnlaces(cel))){
        ant = p;
        p = p->prox;
    }

    if(p == lista->prim && p == lista->ult){ // unica celula
        lista->prim = lista->ult = NULL;
    }

    else if(p == lista->prim){ // se for a primeira celula
        lista->prim = p->prox;
    }

    else if(p == lista->ult){ // se for a ultima celula
        lista->ult = ant;
        lista->ult->prox = NULL;
    } 

    else{ // caso comum
        ant->prox = p->prox;
    }

    free(p);

}



void ImprimeListaEnlaces(Enlaces* lista){ // Printa a lista de enlaces *******ANALISAR DNV temos que imprimir de tras pra frente
    Celula_E* p;
    for(p=lista->prim;p != NULL;p = p->prox){
        ImprimeRoteador(p->rot);
    }
}

size_t tamanhoCelE(){
    return sizeof(Celula_E);
}

void LiberaListaEnlaces(Enlaces* lista){ // Destroi a lista de roteadores
    Celula_E* p = lista->prim;
    Celula_E* t;

    while(p!= NULL){
        t = p->prox;
        LiberaRoteador(p->rot);
        free(p);
        p = t;
    }

    free(lista);
}

