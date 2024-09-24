#include "hashduplo.h"

// Arthur Fernandes de Paiva Costa e Vinícius Machado de Souza

// Função de hash, multiplica por 31 para evitar colisões
int calcular_hash(char* matricula, int tamanho) {
    int hash = 0;
    while (*matricula) {
        hash = (hash * 31 + *matricula) % tamanho;
        matricula++;
    }
    return hash;
}

// Segunda função de hash utilizada para o cálculo de re-hashing
int calcular_hash2(char* matricula, int tamanho) {
    int hash = 0;
    while (*matricula) {
        hash = (hash * 31 + *matricula) % (tamanho - 1);
        matricula++;
    }
    return 1 + hash; // Garantir que o valor seja sempre maior que zero
}

// Função para verificar se um número é primo
int eh_primo(int num) {
    if (num < 2) return 0; // Números menores que 2 não são primos
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    } // Se o número for divisível por outro além de 1 e ele mesmo
    return 1; // O número é primo
}

// Função para encontrar o próximo número primo
int proximo_primo(int n) {
    while (!eh_primo(n)) {
        n++;
    } // Continua incrementando até encontrar o próximo número primo
    return n;
}

// Função para inicializar a tabela hash
TabelaHash* inicializar_tabela(int tamanho) {
    // Aloca espaço para a tabela hash e inicializa suas entradas
    TabelaHash* tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    tabela->tabela = (Aluno*) malloc(tamanho * sizeof(Aluno));
    for (int i = 0; i < tamanho; i++) {
        tabela->tabela[i].ocupado = 0; // Inicializando todos os espaços como vagos
    }
    tabela->tamanho = tamanho;
    tabela->total_matriculas = 0; // Sem matrículas no início
    return tabela;
}

// Função para inserir uma matrícula usando hashing duplo
void inserir_matricula(TabelaHash* tabela, char* nome, char* matricula) {
    // Calcula o hash para a matrícula
    int hash = calcular_hash(matricula, tabela->tamanho);
    int hash2 = calcular_hash2(matricula, tabela->tamanho);

    int i = 0;
    int pos = hash;
    // Realiza o um loop até encontrar um espaço livre
    while (tabela->tabela[pos].ocupado == 1) {
        i++;
        pos = (hash + i * hash2) % tabela->tamanho;  // Re-hashing
        if (i >= tabela->tamanho) {
            printf("Tabela hash cheia! Não foi possivel inserir.\n");
            return; 
        }
    }

    // Copia os dados do aluno para a posição encontrada
    strcpy(tabela->tabela[pos].nome, nome);
    strcpy(tabela->tabela[pos].matricula, matricula);
    tabela->tabela[pos].ocupado = 1; // Marca a posição como ocupada
    tabela->total_matriculas++; // Incrementa o total de matrículas
}

// Função para remover uma matrícula usando hashing duplo
int remover_matricula(TabelaHash* tabela, char* matricula) {
    // Calcula o hash para a matrícula a ser removida
    int hash = calcular_hash(matricula, tabela->tamanho);
    int hash2 = calcular_hash2(matricula, tabela->tamanho);

    int i = 0;
    int pos = hash;
    while (tabela->tabela[pos].ocupado != 0) { // Busca pela matrícula
        if (tabela->tabela[pos].ocupado == 1 && strcmp(tabela->tabela[pos].matricula, matricula) == 0) {
            tabela->tabela[pos].ocupado = -1;  // Marca como removido
            tabela->total_matriculas--; // Decrementa o total de matrículas
            return 1;
        }
        i++;
        pos = (hash + i * hash2) % tabela->tamanho;
        if (i >= tabela->tamanho) break;
    }
    return 0;  // Matrícula não encontrada
}

// Função para pesquisar uma matrícula usando hashing duplo
Aluno* pesquisar_matricula(TabelaHash* tabela, char* matricula) {
    // Calcula o hash para a matrícula procurada
    int hash = calcular_hash(matricula, tabela->tamanho);
    int hash2 = calcular_hash2(matricula, tabela->tamanho);

    int i = 0;
    int pos = hash;
    while (tabela->tabela[pos].ocupado != 0) { // Busca pela matrícula
        if (tabela->tabela[pos].ocupado == 1 && strcmp(tabela->tabela[pos].matricula, matricula) == 0) {
            return &tabela->tabela[pos]; // Retorna o aluno encontrado
        }
        i++;
        pos = (hash + i * hash2) % tabela->tamanho;
        if (i >= tabela->tamanho) break;
    }
    return NULL;  // Matrícula não encontrada
}

// Imprimir todas as matrículas
void imprimir(TabelaHash* tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->tabela[i].ocupado == 1) {
            printf("Nome: %s, Matricula: %s\n", tabela->tabela[i].nome, tabela->tabela[i].matricula);
        } // Imprime apenas as posições que estão ocupadas
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

    // Lê os dados do arquivo e insere na tabela hash
    while (fgets(nome, MAX_NOME, fp) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';
        if (fgets(matricula, MAX_MATRICULA, fp) != NULL) {
            matricula[strcspn(matricula, "\n")] = '\0';
            inserir_matricula(tabela, nome, matricula); // Insere os dados do aluno
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

    // Salva apenas as matrículas que estão ocupadas
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->tabela[i].ocupado == 1) {
            fprintf(fp, "%s\n%s\n", tabela->tabela[i].nome, tabela->tabela[i].matricula);
        }
    }

    fclose(fp);
}

// Função para ler o tamanho do arquivo
int ler_tamanho(const char* arquivo) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return -1;
    }
    
    int total_arquivo = 0;
    char nome[MAX_NOME];
    char matricula[MAX_MATRICULA];

    // Conta o número de matrículas no arquivo
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
int menuhash() {
    int opcao, fator, tamanho_base, tamanho_arquivo;
    printf(linha);
    printf("Escolha o tamanho do vetor Hash (100%%, 120%%, 150%% ou 180%%):\n");
    printf("1 - 100%%\n");
    printf("2 - 120%%\n");
    printf("3 - 150%%\n");
    printf("4 - 180%%\n");
    printf(linha);

    scanf("%d", &opcao);

    // Define o fator multiplicador com base na escolha
    switch (opcao) {
            case 1:
                fator=100;
                break;
            case 2:
                fator=120;
                break;
            case 3:
                fator=150;
                break;
            case 4:
                fator=180;
                break;
            default:
                fator=100;
                printf("Usando valor padrao:100%%\n");
                break;
        }

    // Lê o tamanho do arquivo e multiplica pelo fator para definir o tamanho da tabela
    tamanho_arquivo = ler_tamanho("ListaMatricula.txt");
    tamanho_base = tamanho_arquivo * fator / 100;
    return proximo_primo(tamanho_base); // Encontra o próximo número primo para o tamanho da tabela
}

// Função para medir o tempo de execução
void medir_tempo(void (*funcao)(TabelaHash*), TabelaHash* tabela, const char* nome_funcao) {
    clock_t inicio = clock();
    funcao(tabela);
    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto pela funcao %s: %.6f segundos\n", nome_funcao, tempo_gasto);
}

// Medir tempo de execução de funções que retornam um valor
double medir_tempo_com_retorno(int (*funcao)(TabelaHash*, char*), TabelaHash* tabela, char* arg, const char* nome_funcao) {
    clock_t inicio = clock();
    int resultado = funcao(tabela, arg);
    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto pela funcao %s: %.6f segundos\n", nome_funcao, tempo_gasto);
    return resultado;
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

    clock_t inicio = clock();
    inserir_matricula(tabela, nome, matricula);
    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto pela funcao inserir: %.6f segundos\n", tempo_gasto);
}

void remover(TabelaHash* tabela) {
    char matricula[MAX_MATRICULA];
    printf("Digite a matricula a ser removida: ");
    fgets(matricula, MAX_MATRICULA, stdin);
    matricula[strcspn(matricula, "\n")] = '\0';

    clock_t inicio = clock();
    int removido = remover_matricula(tabela, matricula);
    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto pela funcao remover: %.6f segundos\n", tempo_gasto);

    if (removido) {
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

    clock_t inicio = clock();
    Aluno* aluno = pesquisar_matricula(tabela, matricula);
    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto pela funcao pesquisar: %.6f segundos\n", tempo_gasto);

    if (aluno != NULL) {
        printf("Nome: %s, Matricula: %s\n", aluno->nome, aluno->matricula);
    } else {
        printf("Matricula não encontrada!\n");
    }
}

// Mostrar total de matrículas
void mostrar_total_matriculas(TabelaHash* tabela) {
    clock_t inicio = clock();
    printf("Total de matriculas: %d\n", tabela->total_matriculas);
    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto pela funcao mostrar_total_matriculas: %.6f segundos\n", tempo_gasto);
}

// Função principal
void menu(TabelaHash* tabela) {
    int opcao;
    do {
        printf(linha);
        printf("1 - Inserir Matricula\n");
        printf("2 - Remover Matricula\n");
        printf("3 - Pesquisar Matricula\n");
        printf("4 - Imprimir Matriculas\n");
        printf("5 - Mostrar Total de Matriculas\n");
        printf("0 - Sair\n");
        printf(linha);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                inserir(tabela);
                salvar_dados(tabela, "ListaMatricula.txt");
                break;
            case 2:
                remover(tabela);
                salvar_dados(tabela, "ListaMatricula.txt");
                break;
            case 3:
                pesquisar(tabela);
                break;
            case 4:
                medir_tempo(imprimir, tabela, "imprimir");
                break;
            case 5:
                mostrar_total_matriculas(tabela);
                break;
            case 0:
                printf("Saindo\n");
                return;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 6);
}

int main() {
    clock_t tempo0, tempo;
    double tempo_final;

    int tamanho = menuhash();

    tempo0 = clock();

    TabelaHash* tabela = inicializar_tabela(tamanho);
    carregar_dados(tabela, "ListaMatricula.txt");

    tempo = clock();
    tempo_final = ((double)(tempo - tempo0) / CLOCKS_PER_SEC);

    printf("\nTempo gasto para carregar os dados do arquivo: %f segundos\n", tempo_final);

    menu(tabela);

    free(tabela->tabela);
    free(tabela);

    return 0;
}
