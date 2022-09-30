#include <iostream>
#include <stdio.h>

#include "LeituraArquivos.h"

#include "HashingFechado.h"
#include "HashingAberto.h"



using namespace std;

int main() {
  int escolhaEnderecamento, escolhaHash, escolhaExtra;
  TabelaHashAberta A;
  TabelaHashFechada F;

    while(escolhaEnderecamento != 0 && escolhaEnderecamento != 1){
      cout << "====================================================\n"
           << "Qual a opção de endereçamento deseja utiliza?\n"
           << "[0] Hash Aberto\n"
           << "[1] Hash Fechado\n"
           << "Resposta: ";
      cin >> escolhaEnderecamento;
    }
    while(escolhaHash != 0 && escolhaHash != 1 && escolhaHash != 2){
      cout << "====================================================\n"
           << "Qual Hash deverá ser utilizado:\n"
           << "[0] Hash de mod com soma dos termos\n"
           << "[1] Hash de mod com multiplicação dos termos\n"
           << "[2] Hash do metodo de multiplicação\n"
           << "Resposta: ";
      cin >> escolhaHash;
    }
    LerTexto(escolhaEnderecamento, escolhaHash, A, F);

    while(escolhaExtra != 2){
      cout << "====================================================\n"
           << "Deseja realizar mais alguma função?\n"
           << "[0] Deletar um termo\n"
           << "[1] Procurar um termo\n"
           << "[2] Finalizar o programa\n"
           << "Resposta: ";
      cin >> escolhaExtra;


      if(escolhaEnderecamento == 0){
        FuncoesExtrasAberto(escolhaExtra, escolhaHash, A);
      } else {
        FuncoesExtrasFechado(escolhaExtra, escolhaHash, F);
      }

    }
    escolhaEnderecamento = escolhaHash = -1;


  
}