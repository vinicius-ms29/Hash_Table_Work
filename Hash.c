#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define linha "\n================================================\n"

#define MAX_NOME 100
#define MAX_MATRICULA 20

typedef struct Aluno {
    char nome[MAX_NOME];
    char matricula[MAX_MATRICULA];
    struct Aluno* prox;
} Aluno;

typedef struct {
    Aluno** tabela;
    int tamanho;
    int total_matriculas;
} TabelaHash;

// Função de hash
int calcular_hash(char* matricula, int tamanho) {
    int hash = 0;
    while (*matricula) {
        hash = (hash * 31 + *matricula) % tamanho;
        matricula++;
    }
    return hash;
}

// Função para verificar se um número é primo
int eh_primo(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Função para encontrar o próximo número primo
int proximo_primo(int n) {
    while (!eh_primo(n)) {
        n++;
    }
    return n;
}

// Função para inicializar a tabela hash
TabelaHash* inicializar_tabela(int tamanho) {
    TabelaHash* tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    tabela->tabela = (Aluno**) malloc(tamanho * sizeof(Aluno*));
    for (int i = 0; i < tamanho; i++) {
        tabela->tabela[i] = NULL;
    }
    tabela->tamanho = tamanho;
    tabela->total_matriculas = 0;
    return tabela;
}

// Inserir matrícula
void inserir_matricula(TabelaHash* tabela, char* nome, char* matricula) {
    int hash = calcular_hash(matricula, tabela->tamanho);
    Aluno* novo = (Aluno*) malloc(sizeof(Aluno));
    strcpy(novo->nome, nome);
    strcpy(novo->matricula, matricula);
    novo->prox = tabela->tabela[hash];
    tabela->tabela[hash] = novo;
    tabela->total_matriculas++;
}

// Remover matrícula
int remover_matricula(TabelaHash* tabela, char* matricula) {
    int hash = calcular_hash(matricula, tabela->tamanho);
    Aluno* atual = tabela->tabela[hash];
    Aluno* anterior = NULL;
    
    while (atual != NULL && strcmp(atual->matricula, matricula) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) return 0;
    
    if (anterior == NULL) {
        tabela->tabela[hash] = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    
    free(atual);
    tabela->total_matriculas--;
    return 1;
}

// Pesquisar matrícula
Aluno* pesquisar_matricula(TabelaHash* tabela, char* matricula) {
    int hash = calcular_hash(matricula, tabela->tamanho);
    Aluno* atual = tabela->tabela[hash];
    
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}

// Imprimir matrículas
void imprimir(TabelaHash* tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        Aluno* atual = tabela->tabela[i];
        while (atual != NULL) {
            printf("Nome: %s, Matricula: %s\n", atual->nome, atual->matricula);
            atual = atual->prox;
        }
    }
}

// Carregar dados do arquivo
void carregar_dados(TabelaHash* tabela, const char* arquivo) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    char nome[MAX_NOME];
    char matricula[MAX_MATRICULA];
    
    while (fgets(nome, MAX_NOME, fp) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';
        if (fgets(matricula, MAX_MATRICULA, fp) != NULL) {
            matricula[strcspn(matricula, "\n")] = '\0';
            inserir_matricula(tabela, nome, matricula);
        }
    }
    fclose(fp);
}

// Salvar dados no arquivo
void salvar_dados(TabelaHash* tabela, const char* arquivo) {
    FILE* fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    for (int i = 0; i < tabela->tamanho; i++) {
        Aluno* atual = tabela->tabela[i];
        while (atual != NULL) {
            fprintf(fp, "%s\n%s\n", atual->nome, atual->matricula);
            atual = atual->prox;
        }
    }
    
    fclose(fp);
}

int ler_tamanho(const char* arquivo){
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return -1;
    }
    
    int total_arquivo;
    char nome[MAX_NOME];
    char matricula[MAX_MATRICULA];
    
    while (fgets(nome, MAX_NOME, fp) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';
        if (fgets(matricula, MAX_MATRICULA, fp) != NULL) {
            matricula[strcspn(matricula, "\n")] = '\0';
            total_arquivo++;
        }
    }

    fclose(fp);
    return total_arquivo;
}

// Função para escolher o tamanho do vetor hash
int menu_hash(const char* arquivo) {
    int opcao, base, fator, tamanho_primo;
    printf(linha);
    printf("Escolha o tamanho do vetor Hash (100%%, 120%%, 150%%):\n");
    printf("1 - 100%%\n");
    printf("2 - 120%%\n");
    printf("3 - 150%%\n");
    printf(linha);

    scanf("%d", &opcao);
    
    if (opcao == 1) fator = 100;
    else if (opcao == 2) fator = 120;
    else if (opcao == 3) fator = 150;
    else {
        printf("Opcao invalida! Tamanho padrão 100%% sera usado.\n");
        fator = 100;
    }

    base = ler_tamanho(arquivo);
    tamanho_primo = base * fator / 100;
    return proximo_primo(tamanho_primo);
}

// Funções do Menu
void inserir(TabelaHash* tabela) {
    char nome[MAX_NOME], matricula[MAX_MATRICULA];
    printf("Digite o nome: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Digite a matricula: ");
    fgets(matricula, MAX_MATRICULA, stdin);
    matricula[strcspn(matricula, "\n")] = '\0';
    inserir_matricula(tabela, nome, matricula);
}

void remover(TabelaHash* tabela) {
    char matricula[MAX_MATRICULA];
    printf("Digite a matricula a ser removida: ");
    fgets(matricula, MAX_MATRICULA, stdin);
    matricula[strcspn(matricula, "\n")] = '\0';
    if (remover_matricula(tabela, matricula)) {
        printf("Matricula removida com sucesso!\n");
    } else {
        printf("Matricula não encontrada!\n");
    }
}

void pesquisar(TabelaHash* tabela) {
    char matricula[MAX_MATRICULA];
    printf("Digite a matricula a ser pesquisada: ");
    fgets(matricula, MAX_MATRICULA, stdin);
    matricula[strcspn(matricula, "\n")] = '\0';
    Aluno* aluno = pesquisar_matricula(tabela, matricula);
    if (aluno != NULL) {
        printf("Aluno encontrado:\nNome: %s\nMatricula: %s\n", aluno->nome, aluno->matricula);
    } else {
        printf("Matricula nao encontrada!\n");
    }
}

void total(TabelaHash* tabela) {
    printf("Total de matriculas: %d\n", tabela->total_matriculas);
}

// Menu principal
void menu(TabelaHash* tabela, const char* arquivo) {
    int opcao;
    
    do {
        printf(linha);
        printf("\nMenu:\n");
        printf("1 - Inserir nova matricula\n");
        printf("2 - Remover matricula\n");
        printf("3 - Pesquisar matricula\n");
        printf("4 - Total de matriculas\n");
        printf("5 - Imprimir matriculas\n");
        printf("6 - Salvar e Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf(linha); 
                inserir(tabela);
                break;
            case 2:
                printf(linha); 
                remover(tabela);
                break;
            case 3: 
                printf(linha);
                pesquisar(tabela);
                break;
            case 4:
                printf(linha);
                total(tabela);
            break;
            case 5: 
                printf(linha);
                imprimir(tabela);
                break;
            case 6: 
            salvar_dados(tabela, arquivo); 
                break;
            default: 
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}

int main() {
    clock_t tempo, tempo0;
    double tempo_final;
    int tamanho_primo = menu_hash("lista_de_matriculas.txt");
    tempo0 = clock();
    TabelaHash* tabela = inicializar_tabela(tamanho_primo);
    carregar_dados(tabela, "lista_de_matriculas.txt");
    tempo = clock();
    tempo_final = ((double)(tempo - tempo0) / CLOCKS_PER_SEC);
    printf(linha);
    printf("\nTempo gasto para carregar os dados do arquivo: %f segundos\n", tempo_final);
    menu(tabela, "lista_de_matriculas.txt");
    return 0;
}
