#ifndef HASHINGFECHADO_H
#define HASHINGFECHADO_H

#include "funcoesHash.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct TElementoFechado {
  string palavra;
  int frequencia;
  bool ativo;
};

struct TabelaHashFechada {
  TElementoFechado *tabela;
  int tamanho;
  int ocupacao;
  int colisao;
};

// Sobrecarga para mostrar estatisticas da tabela.
ostream &operator<<(ostream &os, TabelaHashFechada l) {
  float ocupacao = l.ocupacao;
  float tamanho = l.tamanho;
  os   << "Ocupacao: " << l.ocupacao << " de " << l.tamanho << endl
       << "Porcentagem: " << (ocupacao / tamanho) * 100 << "%\n"
       << "Colisões: " << l.colisao << endl;
  return os;
}

// Sobrecarga para mostrar os valores armazenados na tabela.
ostream &operator<<(ostream &os, TElementoFechado l) {
  os << " | Palavra: " << l.palavra << " | Frequência: " << l.frequencia
     << " | Ativo: " << l.ativo << endl;
  return os;
}

// Função para escolher qual Hash será utilizado
int Escolha_Hash(TabelaHashFechada &l, string palavra, int escolhaHash) {

  // Hash que fará a soma entre os valores Hash
  if (escolhaHash == 0) {
    return hashSomaTermos(palavra, l.tamanho);

  // Hash que fará a multiplicação entre os valores Hash
  } else if (escolhaHash == 1) {
    return hashMultTermos(palavra, l.tamanho);

  // Hash que usará o metodo de multiplicação
  } else if (escolhaHash == 2) {
    return hashMultMethod(palavra, l.tamanho);

  // Caso o valor não seja válido;
  } else {
    return -1;
  }
}

void Inicializar_Tabela_Fechada(TabelaHashFechada &l, int tamanho) {
  l.tamanho = tamanho;
  l.ocupacao = 0;
  l.tabela = new TElementoFechado[l.tamanho];
  l.colisao = 0;

  for (int i = 0; i < l.tamanho; i++) {
    l.tabela[i].ativo = false;
    l.tabela[i].frequencia = 0;
  }
}

void Imprimir_Hash_Fechado(TabelaHashFechada &l) {
  TElementoFechado maior, menor;
  menor = maior = l.tabela[0];
  int dispersao, dispersaoAUX;

  int hashDispersaoMenor, hashDispersaoMenorAUX, hashDispersaoMaior, hashDispersaoMaiorAUX;

  hashDispersaoMenor = hashDispersaoMenorAUX = hashDispersaoMaior = hashDispersaoMaiorAUX = dispersao = dispersaoAUX = 0;
  cout << "====================================================\n";
  cout << "                Tabela Hash fechado\n";
  cout << "====================================================\n";

  //Imprimir as posições da tabela Hash
  for (int i = 0; i < l.tamanho; i++) {
    if (l.tabela[i].ativo == false) {
      cout << "Posição [" << i << "] Ativo: " << l.tabela[i].ativo << endl;

    } else {
      cout << "Posição [" << i << "]" << l.tabela[i];

    }
  }
  //Calcular o termo que mais se repetiu na tabela
  for (int i = 0; i < l.tamanho; i++) {
    if (l.tabela[i].frequencia > maior.frequencia) {
      maior = l.tabela[i];
    }
  }

  for (int i = 0; i < l.tamanho; i++){
      if(l.tabela[i].ativo = true){
        hashDispersaoMenorAUX = i + 1;
        int j = hashDispersaoMenorAUX;
          while(l.tabela[j].ativo != false && j < l.tamanho){
            dispersaoAUX++;
            j++;
          }
        hashDispersaoMaiorAUX = j - 1;
        if(dispersaoAUX > dispersao){
          dispersao = dispersaoAUX - 1;
          hashDispersaoMaior = hashDispersaoMaiorAUX;
          hashDispersaoMenor = hashDispersaoMenorAUX;
        }
        dispersaoAUX = 0;
      }
    }


  //Impirmir estatisticas relevantes
  cout << "----------------------------------------------------\n"
       << l
       << "A maior repetição foi [" << maior.palavra << "], que repetiu "
       << maior.frequencia << " vezes\n"
       << "O maior número de termos seguidos ocorreu entres as posição " << hashDispersaoMenor << " e " << hashDispersaoMaior << " com " << dispersao << " itens seguidos"
       << "----------------------------------------------------\n";

}

void Inserir_Hash_Fechado(TabelaHashFechada &l, string palavra, int escolhaHash) {
  int contador = 0;
  //Funções para deixar todas as palavras minusculas
  transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
  //Funções para deixar a palavra sem nenhum carcter especial
  for (int i = 0; i < palavra.size(); i++) {
      if (palavra.at(i) < 'A' || palavra.at(i) > 'Z' && palavra.at(i) < 'a' || palavra.at(i) > 'z') {  
          palavra.erase(i, 1);
          i--;
      } 
  }

  int hash = Escolha_Hash(l, palavra, escolhaHash);

  //Descobrir em que posição da tabela que o hash desejado está
  while (l.tabela[hash].ativo != false && contador < l.tamanho && l.tabela[hash].palavra != palavra) {
    l.colisao++;
    contador++;
    hash++;
    hash = hash % l.tamanho;
  }
  // Se a flag de ativo estiver falsa, iremos inserir o termo nesta posição.
  if (l.tabela[hash].ativo == false) {
    l.tabela[hash].ativo = true;
    l.tabela[hash].frequencia++;
    l.tabela[hash].palavra = palavra;
    l.ocupacao++;
  // Se a palavra ja existe na tabela, apenas aumentaremos a frequencia em 1.
  } else if (l.tabela[hash].palavra == palavra) {
    l.tabela[hash].frequencia++;
  }
}

void Deletar_Hash_Fechado(TabelaHashFechada &l, string palavra, int escolhaHash) {
  int hash = Escolha_Hash(l, palavra, escolhaHash);
  int contador = 0;
  //Descobrir em que posição da tabela que o hash desejado está
  while (contador < l.tamanho && l.tabela[hash].palavra != palavra) {
    contador++;
    hash++;
    hash = hash % l.tamanho;
  }
  // Se a palavra existe na tabela, iremos deletar ela.
  if (l.tabela[hash].palavra == palavra) {
    // Caso a frequencia desta palavra seja 1, iremos deletar ela da tabela.
    if (l.tabela[hash].frequencia == 1) {
      cout << "Termo [" << l.tabela[hash].palavra << "] deletado da posição [" << hash << "] com sucesso!\n";
      l.tabela[hash].ativo = false;
      l.tabela[hash].frequencia--;
      l.ocupacao--;
    // Caso a frequencia desta palavra seja maior 1, iremos diminuir a frequencia dela em 1.
    } else {
      cout << "Termo [" << l.tabela[hash].palavra << "] diminuido da posição [" << hash << "] com sucesso!\n";
      cout << "Antes ele aparecia [" << l.tabela[hash].frequencia << "] vezes,\n";
      l.tabela[hash].frequencia--;
      cout << "Agora ele aparece [" << l.tabela[hash].frequencia << "] vezes.\n";

    }
  // Caso essa palavra não seja encontrada na tabela, sera apenas alertado ao usuário.
  } else {
    cout << "Hash Invalido!\n";

  }
}

TElementoFechado Buscar_Hash_Fechado(TabelaHashFechada &l, string palavra, int escolhaHash) {
  int hash = Escolha_Hash(l, palavra, escolhaHash);
  int contador = 0;
  // Descobrir em que posição da tabela que o hash desejado esta.
  while (l.tabela[hash].ativo != false && contador < l.tamanho) {
    // Caso essa palavra exista na tabela iremos retornar ela.
    if (l.tabela[hash].palavra == palavra) {
      return l.tabela[hash];
    }
    hash++;
    hash = hash % l.tamanho;
  }
  // Caso ela não seja encontrada nós iremos retornar a ultima função encontrada, que neste estará nula.
  return l.tabela[hash];
}

#endif