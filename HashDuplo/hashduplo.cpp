#include "hash_duplo_lib.hpp"
// Alunos: Arthur Fernandes de Paiva Costa e Vinicius Machado de Souza

// FUNÇÃO QUE DEFINE A PROPORÇÃO DO TAMANHO DO VETOR
int getTamanhoVetor(){
    cout << LINHA
    << "\tEscolha o tamanho do vetor Hash (120%%, 150%%, 180%%):"
    << "\n\t1 - 120%%"
    << "\n\t2 - 150%%"
    << "\n\t3 - 180%%"
    << "\n\tEscolha: ";
    int fator;
    cin >> fator;
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
        cout << "\n\n\tOpcao invalida! O tamanho definido sera: 120%%.\n";
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
    // i * i <= primo ou i <= sqrt(primo) ou i <= pow(primo, 0.5)
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
int getTamanhoArquivo(const string nome_arquivo){
    ifstream arquivo(nome_arquivo);
    string nome, matricula;
    int total_matriculas = 0;

    if (!arquivo.is_open()){
        cerr << LINHA "\n\tNao foi possivel abrir o arquivo!" << endl;
        return -1;
    }
    while (getline(arquivo, nome)){
        if (getline(arquivo, matricula)){
            total_matriculas++;
        }
    }

    arquivo.close();
    return total_matriculas;
}
//==================================================

// FUNÇÃO CALCULAR TAMANHO DO VETOR HASH DUPLO
int calcularVetor(const string nome_arquivo, int fator_tamanho){
    int base_tamanho, primo_tamanho;

    base_tamanho = getTamanhoArquivo(nome_arquivo);
    primo_tamanho = base_tamanho * fator_tamanho / 100;
    
    if (primo_tamanho <= 0 || primo_tamanho > 1000000){
        cerr << LINHA << "\n\tUltrapassou o tamanho limite do vetor!" << endl;
        return -1;
    }
    return proximoNumeroPrimo(primo_tamanho);
}
//==================================================

// FUNÇÃO LER DADOS DO ARQUIVO
void lerArquivoParaHash(vector<struct Alunos>& hash, const string nome_arquivo){
    ifstream arquivo(nome_arquivo);
    string lendo_nome, lendo_matricula;
    int i = 0;

    if (!arquivo.is_open()){
        cerr << LINHA << "\n\tNao foi possivel abrir o arquivo!" << endl;
        return;
    }
    while (getline(arquivo, lendo_nome)){
        if (getline(arquivo, lendo_matricula)){
            int limite = hash.size();
            if (i >= limite){
                cerr << LINHA << "\n\tExcedeu o tamanho do vetor!" << endl;
                break;
            }

            long long int nova_matricula = stoll(lendo_matricula);
            hash.at(i).nome = lendo_nome;
            hash.at(i).matricula = nova_matricula;
            i++;
        }
    }

    arquivo.close();
    return;
}
//==================================================

// FUNÇÕES REHASH
int calcHash(long long int matri, int tam_vet){
    return matri % tam_vet;
}

int calcHash2(long long int matri, int tam_vet){
    return 1 + (matri % (tam_vet - 1));
}

int reHash(int ind, int h2, int tam_vet){
    return (ind + h2) % tam_vet;
}
//==================================================

// FUNÇÃO INSERIR
void dadosInserir(vector<struct Alunos>& hash, const string nome_arq){
    string nome;
    long long int matri;
    cout << LINHA "\n\tInsira o nome: ";
    cin >> nome;
    cout << "\n\tInsira a matricula: ";
    cin >> matri;
    inserir(hash, nome_arq, nome, matri);
}

void inserir(vector<struct Alunos>& hash, const string nome_arq, 
                    string new_nome, long long int new_matri){
    int tam_vet = getTamanhoArquivo(nome_arq);
    int h = calcHash(new_matri, tam_vet);
    int h2 = calcHash2(new_matri, tam_vet);
    int ind = h, stop = 0;

    while (hash.at(ind).matricula != -1){// ou 0?
        stop++;
        hash.at(ind).flag = 1;
        ind = reHash(ind, h2, tam_vet);
        if (stop > tam_vet){
            cerr << LINHA "\n\tVetor hash cheio, impossivel adicionar Matricula: "
            << new_matri << " Nome: " << new_nome << "!!!" << endl;
            return;
        };
    }
    hash.at(ind).nome = new_nome;
    hash.at(ind).matricula = new_matri;
}
//==================================================

// FUNÇÃO INSERIR
void dadosExcluir(vector<struct Alunos>& hash, const string nome_arq){
    long long int matri;
    cout << LINHA << "\n\tInsira a matricula para excluir: ";
    cin >> matri;
    excluir(hash, nome_arq, matri);
}

void excluir(vector<struct Alunos>& hash, const string nome_arq, long long int matri){
    int ind = pesquisar(hash, nome_arq, matri);
    if (ind != -1){
        hash.at(ind).matricula = -1; // ou 0?
    }
    cerr << LINHA << "\n\tMatricula nao existe ou nao encontrada!" << endl << endl;
}
//==================================================

// FUNÇÃO INSERIR
void dadosPesquisar(vector<struct Alunos>& hash, const string nome_arq){
    long long int matri;
    cout << LINHA << "\n\tInsira a matricula que deseja encontrar: ";
    cin >> matri;
    pesquisar(hash, nome_arq, matri);
}

int pesquisar(vector<struct Alunos>& hash, const string nome_arq, long long int pesq){
    int tam_vet = getTamanhoArquivo(nome_arq);
    int h = calcHash(pesq, tam_vet);
    int h2 = calcHash2(pesq, tam_vet);
    int ind = h;

    while ((hash.at(ind).matricula != pesq) || (hash.at(ind).flag == 1)){
        if (hash.at(ind).matricula == pesq){
            return ind;
        }
        ind = reHash(ind, h2, tam_vet);
    }
    cout << LINHA << "\n\tMatricula nao encontrada!" << endl << endl;
    return -1;
}
//==================================================

// FUNÇÃO INSERIR
ostream& exibirTotal(const string nome_arquivo){
    int total_vet = getTamanhoArquivo(nome_arquivo);
    return cout << LINHA << "\tTotal de matriculas: " << total_vet << endl;
}
//==================================================

// FUNÇÃO INSERIR
void exibirVetor(vector<struct Alunos>& hash, const string nome_arquivo){
    int i, tam_vet = getTamanhoArquivo(nome_arquivo);
    for (i = 0; i != tam_vet; i++){
        cout << LINHA << "\tNome: " << hash.at(i).nome 
        << "\n\tMatricula: " << hash.at(i).matricula << endl << endl;
    }
}
//==================================================

// FUNÇÃO SALVAR DADOS NO ARQUIVO
void salvarNoArquivo(vector<struct Alunos>& hash, const string nome_arquivo){
    ofstream arquivo(nome_arquivo, ios::app);
    int i = 0, total_vetor = hash.size();
    if (!arquivo.is_open()){
        cerr << LINHA << "\n\tNao foi possivel abrir o arquivo!" << endl;
        return;
    }
    while (i > total_vetor){
        arquivo << endl << hash.at(i).nome << endl << hash.at(i).matricula;
    }
    return;
}
//==================================================

// FUNÇÃO DO MENU PRINCIPAL
int escolhaMenu(){
    cout << LINHA << "\n\t| MENU - HASH DUPLO |"
    << "\n\t0 - Sair do programa"
    << "\n\t1 - Inserir uma matricula"
    << "\n\t2 - Remover uma matricula"
    << "\n\t3 - Pesquisar uma matricula"
    << "\n\t4 - Total de matriculas"
    << "\n\t5 - Imprimir todas as matriculas"
    << "\n\tEscolha: ";
    int escolha;
    cin >> escolha;
    if ((escolha < 0) || (escolha > 5)){
        cout << "\n\n\tOpcao invalida! Tente novamente.";
    }
    return escolha;
}

void menu(vector<struct Alunos>& hash, const string nome_arq, int escolha){
    do{
        switch (escolha){
        case 0:
            salvarNoArquivo(hash, nome_arq);
            cout << "\n\t...Saindo do programa...";
            break;
        case 1:
            // FUNÇÃO INSERIR
            dadosInserir(hash, nome_arq);
            break;
        case 2:
            // FUNÇÃO EXCLUIR
            dadosExcluir(hash, nome_arq);
            break;
        case 3:
            // FUNÇÃO PESQUISAR
            dadosPesquisar(hash, nome_arq);
            break;
        case 4:
            // FUNÇÃO EXIBIR TOTAL
            exibirTotal(nome_arq);
            break;
        case 5:
            // FUNÇÃO EXIBIR VETOR
            exibirVetor(hash, nome_arq);
            break;
        default:
            cout << LINHA << "\n\tOpcao invalida! Tente novamente." << endl;
            break;
        }
    } while (escolha != 0);
}
//==================================================

// FUNÇÃO MAIN
int main(){
    clock_t tempo0, tempo; 
    double tempo_desempenho;
    const string nome_arquivo = "dados.txt";
    int fator_tamanho = getTamanhoVetor();
    
    tempo0 = clock();
    int tamanho_calculado = calcularVetor(nome_arquivo, fator_tamanho);
    vector<struct Alunos> hash(tamanho_calculado);
    lerArquivoParaHash(hash, nome_arquivo);
    tempo = clock();

    tempo_desempenho = ((double)(tempo - tempo0) / CLOCKS_PER_SEC);
    cout << LINHA << "\n\tO programa realizou o processo em: " 
    << tempo_desempenho << endl;

    menu(hash, nome_arquivo, escolhaMenu());
    return 0;
}
//==================================================