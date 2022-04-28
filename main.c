#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "listaTerminais.h"
#include "listaRoteadores.h"


void le_e_executaComando(FILE* entrada, ListaRot* listaROT, ListaTerm* listaTERM,FILE* log, int* idRot,int* idTerm,FILE* saida){
    char instrucao[100];
    char nomeRot[100],nomeRot1[100],nomeRot2[100];
    char nomeOperadora[100];
    char nomeLoc[100];
    char nomeTerm[100];
    char locTerm[100];
    int idROT,idTERM;
    

    char pacoteDados;

    char nomeTerm1[100];
    char nomeTerm2[100];
    

    fscanf(entrada,"%s",instrucao);
    if(strcmp(instrucao,"CADASTRAROTEADOR")==0){
        fscanf(entrada,"%s",nomeRot);
        fscanf(entrada,"%s",nomeOperadora);  
        
       
        // executar cadastra roteador
        idROT = *idRot;
        CadastraRoteador(listaROT,idROT,nomeRot,nomeOperadora);
        
        *idRot = *idRot+1;
    
    }
    if(strcmp(instrucao,"REMOVEROTEADOR")==0){
        fscanf(entrada,"%s",nomeRot); 

        Celula_R* celR = buscaCelRot(nomeRot,listaROT,log);

        if (celR !=NULL){
            RemoveRoteador(celR,listaROT);    // executar remove roteador      
        }

        
    }

    if(strcmp(instrucao,"CADASTRATERMINAL")==0){
        fscanf(entrada,"%s",nomeTerm);
        fscanf(entrada,"%s",locTerm);
        
        idTERM = *idTerm;
        CadastraTerminal(idTERM,nomeTerm,locTerm,listaTERM);
        *idTerm = *idTerm +1;

    }
    if(strcmp(instrucao,"REMOVETERMINAL")==0){
        fscanf(entrada,"%s",nomeTerm);

        // executar remove terminal
        RemoveTerminal(buscaCelTerminal(nomeTerm,listaTERM,log),listaTERM,log);
    }

    if(strcmp(instrucao,"CONECTAROTEADORES")==0){
        fscanf(entrada,"%s",nomeRot1);
        fscanf(entrada,"%s",nomeRot2);

        Celula_R* cel1;
        Celula_R* cel2;

        cel1 = buscaCelRot(nomeRot1,listaROT,log);
        cel2 = buscaCelRot(nomeRot2,listaROT,log);

        //executar conecta roteadoresElaces

        if(verificaRoteador(cel1,listaROT) && verificaRoteador(cel2,listaROT)){
            ConectaRoteadoresEnlaces(cel1, cel2);

        }else if(verificaRoteador(cel1,listaROT)==0){
            fprintf(log,"Roteador %s inexistente no NetMap\n",retornaNomeRot(retornaRot(cel1)));
        }else if(verificaRoteador(cel2,listaROT)==0){
            fprintf(log,"Roteador %s inexistente no NetMap\n",retornaNomeRot(retornaRot(cel2)));
        }

    
    }

    if(strcmp(instrucao,"CONECTATERMINAL")==0){
        fscanf(entrada,"%s",nomeTerm1);
        fscanf(entrada,"%s",nomeRot);
        
        // executar conecta terminal
        // PRITAR ROT CONECTADO AO TERMINAL!!!
        ConectaTerminal(buscaCelTerminal(nomeTerm1,listaTERM,log), buscaCelRot(nomeRot,listaROT,log));
    }

    if(strcmp(instrucao,"IMPRIMENETMAP")==0){

        // executar imprime netmap
    }

    if(strcmp(instrucao,"DESCONECTAROTEADORES")==0){
        fscanf(entrada,"%s",nomeRot1);
        fscanf(entrada,"%s",nomeRot2);

        // Celula_R* cel1;
        // Celula_R* cel2;


        // cel1 = buscaCelRot(nomeRot1,listaROT,log);
        // cel2 = buscaCelRot(nomeRot2,listaROT,log);

        // // executar desconecta roteadores
        // if(verificaRoteador(cel1,listaROT) && verificaRoteador(cel2,listaROT)){
        //     DesconectaRoteadoresEnlaces(cel1, cel2,log);

        // }else if(verificaRoteador(cel1,listaROT)==0){
        //     fprintf(log,"Roteador %s inexistente no NetMap\n",retornaNomeRot(retornaRot(cel1)));
        // }else if(verificaRoteador(cel2,listaROT)==0){
        //     fprintf(log,"Roteador %s inexistente no NetMap\n",retornaNomeRot(retornaRot(cel2)));
        // }
       
    }

    if(strcmp(instrucao,"DESCONECTATERMINAL")==0){
        fscanf(entrada,"%s",nomeTerm);

        // executar desconecta terminal

        // DesconectaTerminal(buscaCelTerminal(nomeTerm,listaTERM,log));

    }
    
    if(strcmp(instrucao,"FREQUENCIAOPERADORA")==0){
        fscanf(entrada,"%s",nomeOperadora);

        // executar frequencia operadora

        // FrequenciaOperadora(listaROT,nomeOperadora,saida);
    }

    if(strcmp(instrucao,"FREQUENCIATERMINAL")==0){
        fscanf(entrada,"%s",nomeLoc);

        // executar frequencia terminal
        // FrequenciaTerminal(listaTERM,nomeLoc,saida);
    }
  





    if(strcmp(instrucao,"ENVIARPACOTESDADOS")==0){
        fscanf(entrada,"%s",nomeTerm1);
        fscanf(entrada,"%s",nomeTerm2);

        // executar enviar pacotes dados

        //EnviaPacotesDados(buscaCelTerminal(nomeTerm1,listaTERM,log),buscaCelTerminal(nomeTerm2,listaTERM,log),saida);
    }



    if(strcmp(instrucao,"FIM")==0){
        // printf("PROGRAMA TERMINANDO !!!\n");

        //termina o programa
        // exit(0);
    }

}

int main(){   
    FILE* entrada;
    FILE* log;
    FILE* saida;
    int idRot = 0; 
    int idTerm = 0;

    //abrindo arquivo
 
    log = fopen("log.txt","w");
    saida = fopen("saida.txt","w");
    entrada = fopen("entrada.txt","r");

    if(entrada==NULL){
        fprintf(log,"ERRO: entrada.txt não encontrado");
    }

    ListaRot* listaRot = CriaListaRot();
    ListaTerm* listaTerm = CriaListaTerm();


    

    while(!feof(entrada)){

        le_e_executaComando(entrada,listaRot,listaTerm,log,&idRot,&idTerm,saida);      

    }
    printf("TRATANDO CONECTA TERMINAL\n");
    //ImprimeListaRot(listaRot);
    //ImprimeListaTerm(listaTerm);

    

    //fechando arquivo
    fclose(entrada);

    return 0;
}

