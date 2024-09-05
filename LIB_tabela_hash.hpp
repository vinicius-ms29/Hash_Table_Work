#ifndef LIB_TABELA_HASH
#define LIB_TABELA_HASH

#include <stdbool.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// ÁREA DAS STRUCTS =======================================================

typedef struct student_data{
    string name;
    long int registration;
}SD;

typedef struct cell_list{
    int key;
    cell_list *next;
}CL;

typedef struct hash_table{
    hash_table *first;
    hash_table *last;
    int total_students;
}HT;

// ÁREA DA NOMEAÇÃO DE FUNÇÕES =======================================================

void add_to_file();

void delete_from_file();


int func_hash();

CL *allocate_cell();

double choose_hash_size();

void create_prime_number();


void insert_hash();

void delete_hash();

void search_hash();

void total_registrations();

void print_registrations();


void menu_hash();

int option_hash();

#endif
