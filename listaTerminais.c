#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaTerminais.h"


struct celula_t{ // Celula da lista de terminais
    Celula_T* prox;
    Terminal* term;
};


struct ListaDeTerminais{// Sentinela da lista de terminais
    Celula_T* prim;
    Celula_T* ult;
};

ListaTerm* CriaListaTerm(){
    ListaTerm* listaT = (ListaTerm*)malloc(sizeof(ListaTerm));

    listaT->prim = NULL;
    listaT->ult = NULL;

    return listaT;
}

void CadastraTerminal(int id,char* nome,char* loc,ListaTerm* lista){
    Celula_T* nova = (Celula_T*)malloc(sizeof(Celula_T));
    
    nova->term = CriaTerminal(id,nome,loc);

    nova->prox = NULL;
    
    if(lista->prim != NULL){
        lista->ult->prox= nova;
        lista->ult = nova;
    }
    else{
        lista->prim = nova;
        lista->ult = nova;
    }
    
  
}

Terminal* retornaTerm(Celula_T* cel){
    return cel->term;   
}

void ConectaTerminal(Celula_T* celT,Celula_R* celR){
    
    if(celT != NULL){
        char * nome1;
        char * nome2;
        Terminal* term = retornaTerm(celT);

        Celula_R* celRTerm = retornaCelRTerm(term);

        celRTerm = celR;

        // printf("%s",retornaNomeRot(retornaRot(celR)));
       
        //term->celRot->rot->nome = celR->rot->nome; ERA PRA ACONTECER ISSO!!!!!!!!


        //PRINT PARA TESTES!!!
        ImprimeTerminal(term);
        printf("XXXXXXXXXXXXXXXXXXXXx\n");
        ImprimeRoteador(retornaRot(celR));
        printf("--------------\n");
    }




}


void RemoveTerminal(Celula_T* CelTerm,ListaTerm* listaT,FILE* log){
    Celula_T* p = listaT->prim;
    Celula_T* ant = NULL;
    int listaVazia = 1;

    while(p!=NULL && retornaIdTerm(p->term)!=retornaIdTerm(CelTerm->term)){
        ant = p;
        p = p->prox;
        listaVazia = 0;
    }

    if(p==NULL && listaVazia==0){ // não encontrou o terminal na lista
        fprintf(log,"ERRO: Terminal %s inexistente no NetMap!\n",retornaNomeTerm(CelTerm->term));
        exit(0);
    }

    if(p==NULL && listaVazia==1){ // lista vazia
        fprintf(log,"O NetMap não contém terminais.\n");
        exit(0);
    }

    if(p == listaT->prim && p == listaT->ult){ // unica celula
        listaT->prim = listaT->ult = NULL;
    }

    else if(p == listaT->prim){ // se for a primeira celula
        listaT->prim = p->prox;
    }

    else if(p == listaT->ult){ // se for a ultima celula
        listaT->ult = ant;
        listaT->ult->prox = NULL;
    } 

    else{ // caso comum
        ant->prox = p->prox;
    }

    free(p);
}

void EnviaPacotesDados(Celula_T* CelTerm1, Celula_T* CelTerm2,FILE*saida){
    Terminal* t1 = retornaTerm(CelTerm1);
    Terminal* t2 = retornaTerm(CelTerm2);

    Celula_R* celR1 = retornaCelRTerm(t1);
    Celula_R* celR2 = retornaCelRTerm(t2);
    char* resposta;

    char* nomeTerm1 = retornaNomeTerm(CelTerm1->term);
    char* nomeTerm2 = retornaNomeTerm(CelTerm2->term);


    if(retornaEnlaces(retornaRot(celR1)) == NULL || retornaEnlaces(retornaRot(celR2)) == NULL){
        resposta = strdup("NAO");
        fprintf(saida,"ENVIARPACOTESDADOS %s %s: NAO\n",nomeTerm1,nomeTerm2);
    }else{
        resposta = strdup("SIM");
        fprintf(saida,"ENVIARPACOTESDADOS %s %s: SIM\n",nomeTerm1,nomeTerm2);
    }

}


void FrequenciaTerminal(ListaTerm* listaT , char* loc,FILE* saida){
    int cont = 0;
    Celula_T* p = listaT->prim;

    while(p!=NULL){
        if(strcmp(retornaLocTerm(p->term),loc)==0){
            cont++;
        }
        p = p->prox;
    }
 
    fprintf(saida,"FREQUENCIATERMINAL %s: %d\n",loc,cont);

}

void DesconectaTerminal(Celula_T* cel){
    Terminal* term = retornaTerm(cel);
    Celula_R* celR;
    Roteador* rotTerm;

    celR = retornaCelRTerm(term);

    rotTerm = retornaRot(celR);

    rotTerm = NULL;
}


void ImprimeListaTerm(ListaTerm* listaT){
    Celula_T* p;
    for(p=listaT->prim;p != NULL;p = p->prox){
        ImprimeTerminal(p->term);
    }
}


Celula_T* buscaCelTerminal(char* nomeTerm,ListaTerm* lista, FILE* log){
    Celula_T* p;
    int existeTerm = 0;
    int listaVaziaT = 1;
    for(p=lista->prim; p!=NULL; p=p->prox){
        listaVaziaT = 0;
        if(strcmp(retornaNomeTerm(p->term),nomeTerm)==0){
            return p;
            existeTerm =1;
        }
    }
    if(existeTerm==0 && listaVaziaT== 0){
        fprintf(log,"ERRO: Terminal %s inexistente no NetMap!\n",nomeTerm);
        return NULL;              
    }

    else if(listaVaziaT == 1){
        fprintf(log,"O NetMap não contém terminais.\n");
        return NULL;       
    }
}


void LiberaListaTerm(ListaTerm* listaT){
    Celula_T* p = listaT->prim;
    Celula_T* t;
    

    while(p!= NULL){
        t = p->prox;
        LiberaTerminal(p->term);
        free(p);
        p = t;
    }

    free(listaT);
}
