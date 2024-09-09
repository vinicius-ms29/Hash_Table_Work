#ifndef LIB_TABELA_HASH
#define LIB_TABELA_HASH

#include <stdbool.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <list>
using namespace std;

// ÁREA DAS STRUCTS =======================================================

typedef struct{
    int A;
    string nome;
    int total_matriculas;
    long long int matricula;
} Estudantes;

/*typedef struct{
    STaluno dados;
    struct STlista *prox;
} STlista;

typedef struct{
    STlista *inicio;
    STlista *fim;
    int total_matriculas;
} SThash;*/

// ÁREA DA NOMEAÇÃO DE FUNÇÕES =======================================================

void ler_arquivo(string nome_arq, Estudantes *E, vector<list<Estudantes>> tabela_hash);

void modificar_o_arquivo(string nome_arq, const vector<list<Estudantes>>& tabela_hash);


int funcao_hash();

void descobrir_numero_primo();

//STlista *alocar_memoria();

std::istream& escolher_metodo_hash(int metodo_hash);

std::istream& escolher_tamanho_tabela_hash(long tamanho_vetor);


void inserir_na_hash();

void deletar_da_hash();

void procurar_na_hash();

void total_de_matriculas();

void exibir_todas_matriculas();


void menu_hash();

int opcao_hash();

#endif