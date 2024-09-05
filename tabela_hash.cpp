#include "LIB_tabela_hash.hpp"

// ÁREA DAS FUNÇÕES DE ARQUIVO =======================================================

void add_to_file(){
    //
}

void delete_from_file(){
    //
}

// ÁREA DAS FUNÇÕES DE AÇÕES =======================================================

void insert_hash(){
    //
}

void delete_hash(){
    //
}

void search_hash(){
    //
}

void total_registrations(){
    //
}

void print_registrations(){
    //
}

// ÁREA DAS FUNÇÕES HASH =======================================================

int func_hash(CL *key){
    return key % ht_size;
}

double choose_hash_size(){
    //
}

void create_prime_number(){
    //
}

CL *allocate_cell(){
    //
}

// ÁREA DAS FUNÇÕES DE MENU =======================================================

int opcao_hash(){
    cout << "\n\t|=======| TABELA HASH - ENDEREÇAMENTO FECHADO |=======|";
    cout << "\n\n\t|0| Sair |";
    cout << "\n\t|1| Inserir Nova Matricula |";
    cout << "\n\t|2| Cancelar/Remover Matricula |";
    cout << "\n\t|3| Pesquisar Matricula |";
    cout << "\n\t|4| Total de Matriculas |";
    cout << "\n\t|5| Imprimir Matriculas |";
    cout << "\n\n\tINFORME A OPCAO DESEJADA: ";
    int opt;
    cin >> opt;
    if ((opt < 0) || (opt > 5)){
        cout << "\n\n\tERRO: numero invalido para o menu";
    }
    return opt;
}

void menu_hash(){
    int opt;
    do {
        int opt = option_hash();
        switch (opt){
        case 0:
            cout << "\n\t...Saindo do programa...";
            break;
        case 1:
            insert_hash();
            break;
        case 2:
            delete_hash();
            break;
        case 3:
            search_hash();
            break;
        case 4:
            total_registrations();
            break;
        case 5:
            print_registrations();
            break;
        default:
            
            break;
        }
    } while (opt != 0);
}

// ÁREA DA FUNÇÃO MAIN =======================================================

int main(int argc, char** argv){
    choose_hash_size();
    menu_hash();
    return 0;
}
