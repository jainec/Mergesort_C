#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct reg{
    char codigo[15], cnpj[20], cnpj2[20];
    int prioridade, posicao;
    float porcentagem, peso;
}container;

void initialize(container E[], int n){
    int i;
    for(i = 0; i < n; i++){
        E[i].codigo[0] = '\0';
        E[i].cnpj[0] = '\0';
        E[i].cnpj2[0] = '\0';
        E[i].prioridade = -1;
        E[i].posicao = -1;
        E[i].peso = -1;
        E[i].porcentagem = -1;
    }
}

void carregaArquivo(container containers[], int contCadastrados, FILE* input){
    int i = 0;
    while( i < contCadastrados ){
        fscanf(input,"%s %s %f\n", containers[i].codigo, containers[i].cnpj, &containers[i].peso);
        containers[i].prioridade = 0;
        containers[i].posicao = i;
        i++;
    }
}

int comparar(container A, container B, int tipo){
    if(tipo == 1){
        if(A.posicao <= B.posicao) return 0;
        else return 1;
    }
    else if(tipo == 2){
        if(A.prioridade <= B.prioridade) return 0;
        else return 1;
    }
    else{
        if(A.porcentagem >= B.porcentagem) return 0;
        return 1;
    }
}

void copy(container *A, container *B){
    strcpy(A->codigo, B->codigo);
    strcpy(A->cnpj, B->cnpj);
    strcpy(A->cnpj2, B->cnpj2);
    A->posicao = B->posicao;
    A->peso = B->peso;
    A->porcentagem = B->porcentagem;
    A->prioridade = B->prioridade;
}

void intercalar(container E[], int ini, int meio, int fim, int qnt, int tipo) {
    int i = ini, j = meio + 1, k = ini;
    container S[qnt];
    while(i <= meio && j <= fim) {
        if(comparar(E[i], E[j], tipo) == 0){
            copy(&S[k], &E[i]);
            k++; i++;
        }
        else {
            copy(&S[k], &E[j]);
            k++; j++;
        }
    }
     if(i > meio){
        while(j <= fim){   //Caso ainda haja elementos na segunda metade
            copy(&S[k], &E[j]);
            k++; j++;
        }
    }
    if(j > fim){
        while(i <= meio){ //Caso ainda haja elementos na primeira metade
            copy(&S[k], &E[i]);
            k++; i++;
        }
    }
     for(i = ini; i <= fim; i++){   //Move os elementos de volta para o vetor original
        copy(&E[i], &S[i]);
     }
}

void mergesort(container E[], int ini, int fim, int qnt, int tipo) {
    if(ini < fim) {
        int meio = ini + (fim - ini) / 2;
        mergesort(E, ini, meio, qnt, tipo);
        mergesort(E, meio + 1, fim, qnt, tipo);
        intercalar(E, ini, meio, fim, qnt, tipo);
    }
}

void troca(container *A, container *B){
    char cod[15], cnpj[20], cnpj2[20];
    int pos, peso, porcent, pri;
    strcpy(cod, A->codigo);
    strcpy(cnpj, A->cnpj);
    strcpy(cnpj2, A->cnpj2);
    pos = A->posicao;
    peso = A->peso;
    porcent = A->porcentagem;
    pri = A->prioridade;
    strcpy(A->codigo, B->codigo);
    strcpy(A->cnpj, B->cnpj);
    strcpy(A->cnpj2, B->cnpj2);
    A->posicao = B->posicao;
    A->peso = B->peso;
    A->porcentagem = B->porcentagem;
    A->prioridade = B->prioridade;
    strcpy(B->codigo, cod);
    strcpy(B->cnpj, cnpj);
    strcpy(B->cnpj2, cnpj2);
    B->posicao = pos;
    B->peso = peso;
    B->porcentagem = porcent;
    B->prioridade = pri;
}

int hoare(container array[], int inicio, int fim){
    char pivo[15];
    strcpy(pivo, array[inicio].codigo);
    int i = inicio - 1;
    int j = fim + 1;
    while(1){
        do i++; while(strcmp(array[i].codigo, pivo) < 0);
        do j--; while(strcmp(array[j].codigo, pivo) > 0);
        if(i >= j){
            return j;
        }
        troca(&array[i], &array[j]);
    }
}

void quicksortHoare(container array[], int inicio, int fim){
    if(inicio < fim){
        int pivo = hoare(array, inicio, fim);
        quicksortHoare(array, inicio, pivo);
        quicksortHoare(array, pivo + 1, fim);
    }
}

int buscaBinaria(container c1[], int contCadastrados, container c2[], int k){
    int ini = 0, fim = contCadastrados-1, meio;
    while (ini <= fim){
        meio = (ini + fim)/2;
        if (strcmp(c2[k].codigo, c1[meio].codigo) == 0){   //quando encontrar o elemento procurado -> verifica cnpj e peso
            if(strcmp(c1[meio].cnpj, c2[k].cnpj) != 0){    //verificacao de cnpj aqui
                strcpy(c2[k].cnpj2, c1[meio].cnpj);
                c2[k].prioridade = 1;
                c2[k].posicao = c1[meio].posicao;
            }else{                                          //verificacao de peso aqui
                int diferenca = abs(c2[k].peso - c1[meio].peso);
                double percent = round( (diferenca*100)/c1[meio].peso);
                if (percent >= 11 || percent <= -11){
                    c2[k].peso = diferenca;
                    c2[k].porcentagem = (percent);
                    c2[k].prioridade = 2;
                    c2[k].posicao = c1[meio].posicao;
                }
            }
            return 0;
        }
        if (strcmp(c2[k].codigo, c1[meio].codigo) < 0) fim = meio - 1;
        else ini = meio + 1;
    }
    return -1;
}

void busca(container c1[], int contCadastrados, int contSelecionados, container c2[]){
    int j;
    for(j = 0; j < contSelecionados; j++)
        buscaBinaria(c1, contCadastrados, c2, j);
}

void print(container containers2[], int contSelecionados, FILE* arq){
    int i;
    for(i = 0; i < contSelecionados; i++){
        if(containers2[i].prioridade == 1)
            fprintf(arq, "%s: %s<->%s\n", containers2[i].codigo, containers2[i].cnpj2, containers2[i].cnpj);
        if(containers2[i].prioridade == 2) break;
    }
    int aux = i;
    mergesort(containers2, aux, contSelecionados-1, contSelecionados, 3);
    for(i = aux; i < contSelecionados; i++)
        fprintf(arq, "%s: %.0fkg (%0.f%%)\n", containers2[i].codigo, containers2[i].peso, containers2[i].porcentagem);
}

int main(int argc, char* argv[]){
    printf("#ARGS = %i\n", argc);
    printf("PROGRAMA = %s\n", argv[0]);
    printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);
    int contCadastrados, contSelecionados;

    FILE* input = fopen(argv[1], "r");

    fscanf(input, "%d\n", &contCadastrados);
    container containers[contCadastrados];
    initialize(containers, contCadastrados);
    carregaArquivo(containers, contCadastrados, input);

    fscanf(input, "%d\n", &contSelecionados);
    container containers2[contSelecionados];
    initialize(containers2, contSelecionados);
    carregaArquivo(containers2, contSelecionados, input);
    fclose(input);

    quicksortHoare(containers, 0, contCadastrados-1);     //ordena alfabeticamente
    busca(containers, contCadastrados, contSelecionados, containers2);  //faz busca binaria
    mergesort(containers2, 0, contSelecionados-1, contSelecionados, 1);  //ordena por posicao
    mergesort(containers2, 0, contSelecionados-1, contSelecionados, 2);  //ordena por prioridade

    FILE* output = fopen(argv[2], "w");
    print(containers2, contSelecionados, output);
    fclose(output);
    return 0;
}
