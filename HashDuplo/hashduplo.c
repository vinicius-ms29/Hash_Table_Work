#include "hashduplo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// FUNÇÃO QUE DEFINE A PROPORÇÃO DO TAMANHO DO VETOR
int getTamanhoVetor(){
    printf("\tEscolha o tamanho do vetor Hash (120%%, 150%%, 180%%):\n");
    printf("\t1 - 120%%\n");
    printf("\t2 - 150%%\n");
    printf("\t3 - 180%%\n");
    printf("\tEscolha: ");
    
    int fator;
    scanf("%d", &fator);
    
    switch (fator){
        case 1:
            fator = 120;
            break;
        case 2:
            fator = 150;
            break;
        case 3:
            fator = 180;
            break;
        default:
            printf("\n\n\tOpcao invalida! O tamanho definido sera: 120%%.\n");
            fator = 120;
            break;
    }
    return fator;
}
//==================================================

// FUNÇÃO ENCONTRAR PRÓXIMO NÚMERO PRIMO
int verificarPrimo(int primo){
    if (primo < 2){
        return 0;
    }
    for (int i = 2; i * i <= primo; i++){
        if (primo % i == 0){
            return 0;
        }
    }
    return 1;
}

int proximoNumeroPrimo(int primo_tamanho){
    if (!verificarPrimo(primo_tamanho)){
        return primo_tamanho;
    }
    return proximoNumeroPrimo(++primo_tamanho);
}
//==================================================

// FUNÇÃO CONTAR MATRICULAS DO ARQUIVO
int getTamanhoArquivo(const char* nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo){
        printf("\n\tNao foi possivel abrir o arquivo!\n");
        return -1;
    }

    char nome[100], matricula[20];
    int total_matriculas = 0;

    while (fgets(nome, sizeof(nome), arquivo) != NULL){
        if (fgets(matricula, sizeof(matricula), arquivo) != NULL){
            total_matriculas++;
        }
    }
    
    fclose(arquivo);
    return total_matriculas;
}
//==================================================

// FUNÇÃO CALCULAR TAMANHO DO VETOR HASH DUPLO
int calcularVetor(const char* nome_arquivo, int fator_tamanho){
    int base_tamanho = getTamanhoArquivo(nome_arquivo);
    int primo_tamanho = base_tamanho * fator_tamanho / 100;

    if (primo_tamanho <= 0 || primo_tamanho > 1000000){
        printf("\n\tUltrapassou o tamanho limite do vetor!\n");
        return -1;
    }
    
    return proximoNumeroPrimo(primo_tamanho);
}
//==================================================

// FUNÇÃO LER DADOS DO ARQUIVO
void lerArquivoParaHash(struct Alunos* hash, int tamanho, const char* nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo){
        printf("\n\tNao foi possivel abrir o arquivo!\n");
        return;
    }

    char lendo_nome[100], lendo_matricula[20];
    int i = 0;

    while (fgets(lendo_nome, sizeof(lendo_nome), arquivo) != NULL && i < tamanho){
        if (fgets(lendo_matricula, sizeof(lendo_matricula), arquivo) != NULL){
            long long int nova_matricula = atoll(lendo_matricula);
            strcpy(hash[i].nome, lendo_nome);
            hash[i].matricula = nova_matricula;
            i++;
        }
    }

    fclose(arquivo);
}
//==================================================

// FUNÇÕES REHASH
// Funções de cálculo de hash e rehash
int calcHash(long long int matri, int tam_vet) {
    return matri % tam_vet;
}

int calcHash2(long long int matri, int tam_vet) {
    return 1 + (matri % (tam_vet - 1));
}

int reHash(int ind, int h2, int tam_vet) {
    return (ind + h2) % tam_vet;
}
//==================================================

// FUNÇÃO INSERIR
void dadosInserir(struct Alunos* hash, const char* nome_arq){
    char nome[100];
    long long int matri;
    printf("\n\tInsira o nome: ");
    scanf("%s", nome);
    printf("\n\tInsira a matricula: ");
    scanf("%I64d", &matri);
    inserir(hash, nome_arq, nome, matri);
}

// Inserir elemento na tabela hash
void inserir(struct Alunos* hash, const char* nome_arq, char* new_nome, long long int new_matricula) {
    int tamanho_vetor = getTamanhoArquivo(nome_arq);
    int h = calcHash(new_matricula, tamanho_vetor);
    int h2 = calcHash2(new_matricula, tamanho_vetor);
    int ind = h, stop = 0;

    // Percorrer até encontrar uma posição vazia
    while (hash[ind].matricula != -1 && hash[ind].flag != -1) { 
        stop++;
        if (stop >= tamanho_vetor) {
            printf("\n\tVetor hash cheio, impossivel adicionar Matricula: %I64d Nome: %s!!!\n", new_matricula, new_nome);
            return;
        }
        ind = reHash(ind, h2, tamanho_vetor);
    }

    // Inserir os dados na posição disponível
    strcpy(hash[ind].nome, new_nome);
    hash[ind].matricula = new_matricula;
    hash[ind].flag = 1; // Marca como ocupada
}
//==================================================

// FUNÇÃO EXCLUIR
void dadosExcluir(struct Alunos* hash, int tamanho_vetor){
    long long int matri;
    printf("\n\tInsira a matricula para excluir: ");
    scanf("%I64d", &matri);
    excluir(hash, tamanho_vetor, matri);
}

// Excluir elemento da tabela hash
void excluir(struct Alunos* hash, int tamanho_vetor, long long int matricula) {
    int ind = pesquisar(hash, tamanho_vetor, matricula);
    if (ind != -1) {
        // Marca a matrícula como removida
        hash[ind].matricula = -1;  // Marca como excluída
        hash[ind].flag = -1;  // Marca a posição como removida
        printf("\n\tMatricula %I64d removida com sucesso!\n", matricula);
    } else {
        printf("\n\tMatricula nao encontrada!\n");
    }
}
//==================================================

// FUNÇÃO PESQUISAR
void dadosPesquisar(struct Alunos* hash, int tamanho_vetor){
    long long int matri;
    printf("\n\tInsira a matricula que deseja encontrar: ");
    scanf("%I64d", &matri);
    pesquisar(hash, tamanho_vetor, matri);
}

// Pesquisar elemento na tabela hash
int pesquisar(struct Alunos* hash, int tamanho_vetor, long long int pesq) {
    int h = calcHash(pesq, tamanho_vetor);
    int h2 = calcHash2(pesq, tamanho_vetor);
    int ind = h, stop = 0;

    // Procurar até encontrar o elemento ou uma posição vazia (sem colisão)
    while (hash[ind].matricula != pesq) {
        if (hash[ind].matricula == -1 && hash[ind].flag == 0) {
            printf("\n\tMatricula nao encontrada!\n");
            return -1;
        }

        stop++;
        if (stop >= tamanho_vetor) {
            printf("\n\tMatricula nao encontrada!\n");
            return -1;
        }

        ind = reHash(ind, h2, tamanho_vetor);
    }

    return ind;  // Retorna o índice se encontrou a matrícula
}
//==================================================

// FUNÇÃO EXIBIR TOTAL
void exibirTotal(const char* nome_arquivo){
    int total_vet = getTamanhoArquivo(nome_arquivo);
    printf("\tTotal de matriculas: %d\n", total_vet);
}
//==================================================

// Função que exibe todas as matriculas
void exibirVetor(struct Alunos* hash, int tamanho_vetor){
    for (int i = 0; i < tamanho_vetor; i++){
        if (hash[i].matricula != -1) {
            printf("\tNome: %s\tMatricula: %I64d\n", hash[i].nome, hash[i].matricula);
        }
    }
}
//==================================================


void salvarNoArquivo(struct Alunos* hash, int tamanho_vetor, const char* nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "a");  // Abre o arquivo no modo de acréscimo ("a")

    if (!arquivo) {
        printf("\n\tNao foi possivel abrir o arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < tamanho_vetor; i++) {
        if (hash[i].matricula != -1) {  // Verifica se a matrícula é válida (não excluída)
            fprintf(arquivo, "%s\n%I64d\n", hash[i].nome, hash[i].matricula);  // Salva o nome e matrícula no arquivo
        }
    }

    fclose(arquivo);  // Fecha o arquivo após salvar
    printf("\n\tDados salvos com sucesso no arquivo!\n");
}


// FUNÇÃO DO MENU PRINCIPAL
int escolhaMenu(){
    printf("\n\t| MENU - HASH DUPLO |\n");
    printf("\t0 - Sair do programa\n");
    printf("\t1 - Inserir uma matricula\n");
    printf("\t2 - Remover uma matricula\n");
    printf("\t3 - Pesquisar uma matricula\n");
    printf("\t4 - Total de matriculas\n");
    printf("\t5 - Imprimir todas as matriculas\n");
    printf("\tEscolha: ");

    int escolha;
    scanf("%d", &escolha);

    if (escolha < 0 || escolha > 5){
        printf("\n\n\tOpcao invalida! Tente novamente.\n");
    }
    
    return escolha;
}

void menu(struct Alunos* hash, int tamanho_vetor, const char* nome_arq){
    int escolha;
    do {
        escolha = escolhaMenu();  // Apenas uma vez no início de cada iteração
        switch (escolha) {
            case 0:
                salvarNoArquivo(hash, tamanho_vetor, nome_arq);
                printf("\n\t...Saindo do programa...\n");
                break;
            case 1:
                // FUNÇÃO INSERIR
                dadosInserir(hash, nome_arq);
                break;
            case 2:
                // FUNÇÃO EXCLUIR
                dadosExcluir(hash, tamanho_vetor);
                break;
            case 3:
                // FUNÇÃO PESQUISAR
                dadosPesquisar(hash, tamanho_vetor);
                break;
            case 4:
                // FUNÇÃO EXIBIR TOTAL
                exibirTotal(nome_arq);
                break;
            case 5:
                // FUNÇÃO EXIBIR VETOR
                exibirVetor(hash, tamanho_vetor);
                break;
            default:
                printf("\n\tOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (escolha != 0);
}



// FUNÇÃO MAIN
int main(){
    clock_t tempo0, tempo;
    double tempo_desempenho;
    const char* nome_arquivo = "dados.txt";
    int fator_tamanho = getTamanhoVetor();

    tempo0 = clock();
    int tamanho_calculado = calcularVetor(nome_arquivo, fator_tamanho);

    // Aloca dinamicamente o vetor de structs
    struct Alunos* hash = (struct Alunos*) malloc(tamanho_calculado * sizeof(struct Alunos));
    
    // Inicializa o vetor
    for (int i = 0; i < tamanho_calculado; i++) {
        hash[i].matricula = -1;  // Indicador de posição vazia
        hash[i].flag = 0;
    }

    lerArquivoParaHash(hash, tamanho_calculado, nome_arquivo);
    tempo = clock();

    tempo_desempenho = ((double)(tempo - tempo0) / CLOCKS_PER_SEC);
    printf("\n\tO programa realizou o processo em: %.2f segundos\n", tempo_desempenho);

    menu(hash, tamanho_calculado, nome_arquivo);

    free(hash);  // Libera a memória alocada
    return 0;
}
