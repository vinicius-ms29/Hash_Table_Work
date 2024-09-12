#ifndef HASH_H
#define HASH_H

#define MAX_NOME 100
#define MAX_MATRICULA 20
#define LINHA "================================================\n"

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

// Funções
int calcular_hash(char* matricula, int tamanho);
int eh_primo(int num);
int proximo_primo(int n);
TabelaHash* inicializar_tabela(int tamanho);
void inserir_matricula(TabelaHash* tabela, char* nome, char* matricula);
int remover_matricula(TabelaHash* tabela, char* matricula);
Aluno* pesquisar_matricula(TabelaHash* tabela, char* matricula);
void imprimir_matriculas(TabelaHash* tabela);
void carregar_dados(TabelaHash* tabela, const char* arquivo);
void salvar_dados(TabelaHash* tabela, const char* arquivo);
int menuhash();
void inserir(TabelaHash* tabela);
void remover(TabelaHash* tabela);
void pesquisar(TabelaHash* tabela);
void total(TabelaHash* tabela);
void imprimir(TabelaHash* tabela);
void menu(TabelaHash* tabela, const char* arquivo);

#endif // HASH_H
