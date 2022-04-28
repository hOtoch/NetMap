#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaRoteadores.h"
#include "roteador.h"


struct celula_r{ // Celula da lista de roteadores
    Celula_R* prox;
    Roteador* rot;
};


struct ListaDeRoteadores{// Sentinela da lista de roteadores
    Celula_R* prim;
    Celula_R* ult;
    int tamanho;
};

Roteador* retornaRot(Celula_R* cel){
    return cel->rot;
}

ListaRot* CriaListaRot(){
    ListaRot* lista = (ListaRot*)malloc(sizeof(ListaRot));

    lista->prim = NULL;
    lista->ult = NULL;

    lista->tamanho = 0;

    return lista;
}



int verificaRoteador(Celula_R* cel,ListaRot* lista){
    Celula_R* p;
    int existe = 0;
    Roteador* rotProcurado = retornaRot(cel);
    char* nomeProcurado = retornaNomeRot(rotProcurado);

    for(p=lista->prim;p!=NULL;p=p->prox){
        Roteador* rotP = retornaRot(p);
        char* nomeP = retornaNomeRot(rotP);
        if(strcmp(nomeProcurado,nomeP)==0){
            existe = 1;
        }
    }

    return existe;
}



void CadastraRoteador(ListaRot* lista,int idRot,char* nomeRot,char* nomeOperadora){
   
    Celula_R* nova = (Celula_R*)malloc(sizeof(Celula_R));
    

    nova->rot = CriaRoteador(idRot,nomeRot,nomeOperadora);
    

    nova->prox = NULL;
    
    if(lista->prim != NULL){
        lista->ult->prox= nova; 
        lista->ult = nova;     
    }
    else{
        lista->prim = nova;   
        lista->ult = nova; 
    }
    
  

    lista->tamanho = lista->tamanho + 1;

}

void ConectaRoteadoresEnlaces(Celula_R* cel1,Celula_R* cel2){  
    Celula_E* nova1 = (Celula_E*)malloc(sizeof(tamanhoCelE()));

    Roteador* rot1 = retornaRotEnlaces(nova1);
    rot1 = retornaRot(cel1);
    adicionaRotCelE(nova1,rot1);
    // nova1->rot = rot1;

    Celula_E* nova2 = (Celula_E*)malloc(sizeof(tamanhoCelE()));

    Roteador* rot2 = retornaRotEnlaces(nova2);
    rot2 = retornaRot(cel2);
    adicionaRotCelE(nova2,rot2);
    // nova2->rot = rot2;

    // Enlaces* listaEnlacesROTEADOR1 = criaListaEnlaces();
    // Enlaces* listaEnlacesROTEADOR2 = criaListaEnlaces();

    Enlaces* listaEnlacesROTEADOR1 = retornaEnlaces(rot1);
    Enlaces* listaEnlacesROTEADOR2 = retornaEnlaces(rot2);



    listaEnlacesROTEADOR1 = CadastraRoteadorEnlaces(listaEnlacesROTEADOR1, nova2);
    
    Roteador * roteTESTE = retornaRotEnlaces(retornaPrimEnlaces(listaEnlacesROTEADOR1));

    if(roteTESTE ==NULL){
        printf(" SOU NULL\n");
    }

    listaEnlacesROTEADOR2 = CadastraRoteadorEnlaces(listaEnlacesROTEADOR2, nova1);

    // ImprimeListaEnlaces(listaEnlacesROTEADOR1);
    // printf("-------------------\n");
    // ImprimeListaEnlaces(listaEnlacesROTEADOR2);
    // printf("XXXXXXXXXXXXXXXXXXXXXXXXXXx\n");
}

void DesconectaRoteadoresEnlaces(Celula_R* cel1,Celula_R* cel2,FILE* log){

    Roteador* rot1 = retornaRot(cel1);
    Roteador* rot2 = retornaRot(cel2);

    Enlaces* listaEnlaces1 = retornaEnlaces(rot1);
    Enlaces* listaEnlaces2 = retornaEnlaces(rot2);

    Celula_E* cel_E_lista1 = buscaRoteadorEnlaces(rot2,listaEnlaces1,log,rot1);
    
    Celula_E* cel_E_lista2 = buscaRoteadorEnlaces(rot1,listaEnlaces2,log,rot2);


    RemoveRoteadorEnlaces(cel_E_lista1,listaEnlaces2); // remover uma celula_E de uma lista de enlaces de um roteador
    RemoveRoteadorEnlaces(cel_E_lista2,listaEnlaces1); 
    
}

Celula_R* buscaCelRot(char* nomeRot,ListaRot* lista, FILE* log){
    Celula_R* p;

    int existeRot = 0;
    int listaVazia = 1;

    for(p=lista->prim;p!=NULL;p=p->prox){
        listaVazia = 0;
        if(strcmp(retornaNomeRot(p->rot),nomeRot)==0){          
            return p;
            existeRot = 1;
        }
    }
    if(existeRot==0 && listaVazia == 0){
        fprintf(log,"ERRO: Roteador %s inexistente no NetMap!\n",nomeRot);
        return NULL;            
    }

    else if(listaVazia == 1){
        fprintf(log,"O NetMap não contém roteadores.\n"); 
        return NULL;   
    }
}
void RemoveRoteador(Celula_R* cel,ListaRot* listaR){
    Celula_R* p = listaR->prim;
    Celula_R* ant = NULL;
    int existeEnlaces = 0;

    int idP = retornaIdRot(p->rot);

    
    Roteador* rotCel = retornaRot(cel); 
    int idCel = retornaIdRot(rotCel);

    while(p->prox!=NULL && idP != idCel){
        ant = p;
        p = p->prox;
        idP = retornaIdRot(p->rot);
    } 


    if(p == listaR->prim && p == listaR->ult){ // unica celula
        listaR->prim = listaR->ult = NULL;
    }

    else if(p == listaR->prim){ // se for a primeira celula
        listaR->prim = p->prox;
    }

    else if(p == listaR->ult){ // se for a ultima celula    
        listaR->ult = ant;
        listaR->ult->prox = NULL;
    } 

    else if(p != listaR->prim && p != listaR->ult){ // caso comum
        ant->prox = p->prox;            
    } 

    Celula_E* celE;
    Roteador* rotCel_E = retornaRotEnlaces(celE);

    rotCel_E = rotCel;

    Enlaces* listaEnlaces = retornaEnlaces(rotCel_E);
    Enlaces* listaEnlacesQ;

    Celula_E* q;
    q=retornaPrimEnlaces(listaEnlaces); // APONTANDO P NULL
    
    for(q=retornaPrimEnlaces(listaEnlaces);q!=NULL;q = retornaProxEnlaces(q)){
        listaEnlacesQ = retornaEnlaces(retornaRotEnlaces(q));
        ImprimeListaEnlaces(listaEnlacesQ);
        existeEnlaces = 1;
        RemoveRoteadorEnlaces(celE,listaEnlacesQ);
        printf("---------------------------------------\n");
        ImprimeListaEnlaces(listaEnlacesQ);
    }
    if(existeEnlaces==1){
        LiberaListaEnlaces(listaEnlacesQ); // ERRO!
    }
    free(p); 

}

void FrequenciaOperadora(ListaRot* listaR,char* operadora, FILE* saida){ // Imprime a quantidade de roteadores cadastrados de uma operadora
    int cont = 0;
    Celula_R* p = listaR->prim;

    while(p!=NULL){
        if(strcmp(retornaOperadoraRot(p->rot),operadora)){
            cont++;
        }
    }



    fprintf(saida,"FREQUENCIAOPERADORA %s: %d\n",operadora,cont);

}

void ImprimeListaRot(ListaRot* listaR){ // Printa a lista de roteadores 
    Celula_R* p;
    for(p=listaR->prim;p != NULL;p = p->prox){
        ImprimeRoteador(p->rot);
    }
}

void LiberaListaRot(ListaRot* listaR){ // Destroi a lista de roteadores
    Celula_R* p = listaR->prim;
    Celula_R* t;

    while(p!= NULL){
        t = p->prox;
        LiberaRoteador(p->rot);
        free(p);
        p = t;
    }

    free(listaR);
}
