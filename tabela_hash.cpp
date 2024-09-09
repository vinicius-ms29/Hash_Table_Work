#include "LIB_tabela_hash.hpp"

// ÁREA DAS FUNÇÕES DE ARQUIVO =======================================================

void ler_arquivo(string nome_arq, int metodo_hash, vector<list<Estudantes>>& tabela_hash){
    ifstream arq(nome_arq);
    if (arq.is_open()){
        string temp_nome;
        srand(time(0));
        long temp_matr;
        int indc;

        if (metodo_hash == 1){
            while (arq >> temp_nome >> temp_matr){
                indc = funcao_hash(temp_matr, tabela_hash.size());
                tabela_hash[indc].push_back({temp_nome, temp_matr});
            }
            arq.close();
        } else if (metodo_hash == 2){
            while (arq >> temp_nome >> temp_matr){
                indc = funcao_hash(temp_matr, tabela_hash.size());
                tabela_hash[indc].push_back({temp_nome, temp_matr});
            }
            arq.close();
        } else {
            cerr << "| ERRO na funcao hash! |";
        }
    }
}


void modificar_o_arquivo(string nome_arq, const vector<list<Estudantes>>& tabela_hash){
    // Abre o arquivo em modo escrita para adicionar os dados novos
    ofstream arq(nome_arq, ios::app);
    if (arq.is_open()){
        for (const auto& lista : tabela_hash) {
            for (const auto& aluno : lista) {
                arq << endl << aluno.nome << endl << aluno.matricula;
            }
        }
    }
    arq.close(); // Fecha o arquivo
}

// ÁREA DAS FUNÇÕES DE AÇÕES =======================================================

void inserir_na_hash(){
    //
}

void deletar_da_hash(){
    //
}

void procurar_na_hash(){
    //
}

void total_de_matriculas(){
    //
}

void exibir_todas_matriculas(){
    //
}

// ÁREA DAS FUNÇÕES HASH =======================================================

int funcao_hash(int matricula, int tamanho_vetor){
    return matricula % tamanho_vetor;
}

int funcao_hash(int matricula, int tamanho_vetor, const double A){
    return int(tamanho_vetor * (fmod(matricula * A, 1)));
}

int descobrir_A(int matricula, int tamanho_vetor) {
    double aleatorio = (double)rand() / RAND_MAX;
    double fracao = (matricula * aleatorio) - int(matricula * aleatorio);
    double A = int(tamanho_vetor * fracao);
    return A;
}

void descobrir_numero_primo(){
    //
}

/*STlista *alocar_memoria(){
    return (STlista*)malloc(sizeof(STlista));
}*/

std::istream& escolher_metodo_hash(int metodo_hash){
    cout << "\n\n\t| DEFINIR METODO DA FUNCAO HASH |"
         << "\n\n\t| 1 = Divisao |\n\t| 2 = Multiplicacao |"
         << "\n\n\t-> Escolha: ";
    return cin >> metodo_hash;
}

std::istream& escolher_tamanho_tabela_hash(long tamanho_vetor){
    cout << "\t| DEFINIR TAMANHO DO VETOR HASH |"
         << "\n\n\t| 100% = Digite 1.0 |"
         << "\n\t| 120% = Digite 1.2 |"
         << "\n\t| 150% = Digite 1.5 |"
         << "\n\n\t-> Tamanho: ";
    return cin >> tamanho_vetor;
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
    cout << "\n\n\t-> Informe a opcao desejada: ";
    int opt;
    cin >> opt;
    if ((opt < 0) || (opt > 5)){
        cout << "\n\n\t| ERRO numero invalido para o menu! |";
    }
    return opt;
}

void menu_hash(){
    int opt;
    do {
        int opt = opcao_hash();
        switch (opt){
        case 0:
            cout << "\n\t...Saindo do programa...";
            break;
        case 1:
            inserir_na_hash();
            break;
        case 2:
            deletar_da_hash();
            break;
        case 3:
            procurar_na_hash();
            break;
        case 4:
            total_de_matriculas();
            break;
        case 5:
            exibir_todas_matriculas();
            break;
        default:
            cout << "\n\n\n\ndefault";
            break;
        }
    } while (opt != 0);
}

// ÁREA DA FUNÇÃO MAIN =======================================================

int main(int argc, char** argv){
    Estudantes *E;

    long tamanho_vetor; // Pede ao usuário para definir o tamanho da tabela
    escolher_tamanho_tabela_hash(tamanho_vetor) >> tamanho_vetor;

    int metodo_hash; // Pede ao usuário para definir o metodo hash
    escolher_metodo_hash(metodo_hash) >> metodo_hash;

    vector<list<Estudantes>> tabela_hash(tamanho_vetor);
    string nome_arq = "nomes_matriculas.txt";

    ler_arquivo(nome_arq, metodo_hash, tabela_hash);

    menu_hash();
    return 0;
}