#include <iostream>
#include <fstream>


#include "HashingFechado.h"
#include "HashingAberto.h"



using namespace std;

int DefinirTamanho(){
    ifstream arquivoTexto;
    int tamanho = 0;

    arquivoTexto.open("texto.txt");
    string palavra;
    while(arquivoTexto >> palavra){
        tamanho++;
    }

    arquivoTexto.close();
    return tamanho;
}

void LerTexto(int escolhaEncapsulamento, int escolhaHash, TabelaHashAberta &A, TabelaHashFechada &F){
    string palavra;
    ifstream arquivoTexto;

    int tamanho = DefinirTamanho();

    switch(escolhaEncapsulamento){
    case 0:
        Inicializar_Tabela_Aberta(A, 150);

        arquivoTexto.open("texto.txt");

        while(arquivoTexto >> palavra){
            Inserir_Hash_Aberto(A, palavra, escolhaHash);
        }
        arquivoTexto.close();

        Imprimir_Hash_Aberto(A);
        break;

    case 1:
        Inicializar_Tabela_Fechada(F, 150);

        arquivoTexto.open("texto.txt");

        while(arquivoTexto >> palavra){
            Inserir_Hash_Fechado(F, palavra, escolhaHash);
        }
        arquivoTexto.close();

        Imprimir_Hash_Fechado(F);
        break;

    }
}

void FuncoesExtrasAberto(int escolhaFuncao, int escolhaHash, TabelaHashAberta &A){
    string palavra;
    TElementoAberto * aux;
    switch(escolhaFuncao){
        case 0:
            cout << "====================================================\n"
                 << "Qual palavra deseja deletar?\n"
                 << "Resposta: ";
            cin >> palavra;
            Deletar_Hash_Aberto(A, palavra, escolhaHash);
            LimparTela();
            Imprimir_Hash_Aberto(A);
            break;
        case 1:
            cout << "====================================================\n"
                 << "Qual palavra deseja buscar?\n"
                 << "Resposta: ";
                cin >> palavra;
                aux = Buscar_Hash_Aberto(A, palavra, escolhaHash);
                if(aux != nullptr){
                    cout << "O termo pesquisado é: \n" << aux << endl;
                } else {
                    cout << "Não foi possivel localizar a palavra [" << palavra << "]\n";
                }
            break;
            break;
    }
}

void FuncoesExtrasFechado(int escolhaFuncao, int escolhaHash, TabelaHashFechada &F){
    TElementoFechado aux;
    string palavra;
    switch(escolhaFuncao){
        case 0: 
            cout << "====================================================\n"
                 << "Qual palavra deseja deletar?\n"
                 << "Resposta: ";            
            cin >> palavra;
            Deletar_Hash_Fechado(F, palavra, escolhaHash);
            LimparTela();
            Imprimir_Hash_Fechado(F);
            break;
        case 1:
            cout << "====================================================\n"
                 << "Qual palavra deseja buscar?\n"
                 << "Resposta: ";
            cin >> palavra;
            aux = Buscar_Hash_Fechado(F, palavra, escolhaHash);
            if(aux.ativo == true){
                cout << "O termo pesquisado é: \n" << aux << endl;
            } else {
                cout << "Não foi possivel localizar a palavra [" << palavra << "]\n";
            }
            break;
        case 2:
            break;
    }
}