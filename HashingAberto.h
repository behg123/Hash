#ifndef HASHINGABERTO_H
#define HASHINGABERTO_H

#include "funcoesHash.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct TElementoAberto {
  string palavra;
  int frequencia;
  bool ativo;
  TElementoAberto *proximo;
};

struct TabelaHashAberta {
  TElementoAberto **tabela;
  int tamanho;
  int ocupacao;
  int colisao;
};

// Sobrecarga para mostrar estatisticas da tabela.
ostream &operator<<(ostream &os, TabelaHashAberta l) {
  float ocupacao = l.ocupacao;
  float tamanho = l.tamanho;
  os   << "Ocupacao: " << l.ocupacao << " de " << l.tamanho << endl
       << "Porcentagem: " << (ocupacao / tamanho) * 100 << "%\n"
       << "Colisões: " << l.colisao << endl;
  return os;
}

// Sobrecarga para mostrar os valores armazenados na tabela.
ostream &operator<<(ostream &os, TElementoAberto *c) {
    os << "| Palavra: " << c->palavra
      << " | Frequência: " << c->frequencia
      << " | Ativo: " << c->ativo << endl;

    return os;
}

// Função para escolher qual Hash será utilizado
int Escolha_Hash(TabelaHashAberta &l, string palavra, int escolhaHash) {

  // Hash que fará a soma entre os valores Hash
  if (escolhaHash == 0) {
    return hashSomaTermos(palavra, l.tamanho);

  // Hash que fará a multiplicação entre os valores Hash
  } else if (escolhaHash == 1) {
    return hashMultTermos(palavra, l.tamanho);

  // 
  } else if (escolhaHash == 2) {
    return hashMultMethod(palavra, l.tamanho);

  // Caso o valor não seja válido;
  } else {
    return -1;
  }
}

void Inicializar_Tabela_Aberta(TabelaHashAberta &l, int tamanho) {
    l.tamanho = tamanho;
    l.colisao = 0;
    l.ocupacao = 0;
    l.tabela = new TElementoAberto *[l.tamanho];

    for (int i = 0; i < l.tamanho; i++) {
        l.tabela[i] = new TElementoAberto;
        l.tabela[i]->ativo = false;
        l.tabela[i]->frequencia = 0;
        l.tabela[i]->proximo = nullptr;
    }
}

void Imprimir_Hash_Aberto(TabelaHashAberta l) {
    // Inicializar variaveis essenciais
    TElementoAberto *maior, *menor;
    float ocupacao = l.ocupacao;
    float tamanho = l.tamanho;
    menor = maior = l.tabela[0];
    int dispersao, dispersaoAUX;
    int hashDispersao, hashDispersaoAUX;

    hashDispersao = dispersao = dispersaoAUX = 0;

    cout << "====================================================\n";
    cout << "                Tabela Hash Aberta\n";
    cout << "====================================================\n";

    //Imprimir as posições da tabela Hash
    for (int i = 0; i < l.tamanho; i++) {
        TElementoAberto *nav = l.tabela[i];
        cout << "\nPosição [" << i << "]\n";
        // Se a posição está sendo usada.
        if (nav->ativo == true) {
            // caso a primeira posição possua um valor, mas a proxima posição não possua.
            if (nav->proximo == nullptr) {
                cout << nav;
            } else {
                // enquanto a proxima posição não for nulo será impresso.
                while (nav->proximo != nullptr) {
                    cout << nav;
                    nav = nav->proximo;
                }
            }
        // Caso a posição não esteja sendo usada.
        } else {
            cout << "Ativo: " << nav->ativo << endl;
        }
    }
    //Calcular o termo que mais se repetiu na tabela
    for (int i = 0; i < l.tamanho; i++) {
        if (l.tabela[i]->frequencia > maior->frequencia) {
            maior = l.tabela[i];
        }
    }
    for (int i = 0; i < l.tamanho; i++) {
        TElementoAberto *nav = l.tabela[i];

        if(nav->ativo == true){
            hashDispersaoAUX = i;
            while(nav->proximo != nullptr){
                nav = nav->proximo;
                dispersaoAUX++;
            }

            if(dispersaoAUX > dispersao){
                dispersao = dispersaoAUX;
                hashDispersao = hashDispersaoAUX;
            }
            dispersaoAUX = 0;
        }

    }
    


    //Imprimir estatisticas relevantes
    cout << "----------------------------------------------------\n" 
         << l
         << "Maior repetição foi [" << maior->palavra << "] que repetiu "
         << maior->frequencia << " vezes\n"
         << "O maior número de termos seguidos ocorreu na posição " << hashDispersao << " com " << dispersao << " itens seguidos"
         << "----------------------------------------------------\n";

}

void Inserir_Hash_Aberto(TabelaHashAberta &l, string palavra, int escolhaHash) {

    //Funções para deixar todas as palavras minusculas
    transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);

    //Funções para deixar a palavra sem nenhum carcter especial
    for (int i = 0; i < palavra.size(); i++) {
        if (palavra.at(i) < 'A' || palavra.at(i) > 'Z' && palavra.at(i) < 'a' || palavra.at(i) > 'z') {  
            palavra.erase(i, 1);
            i--;

        }
    }

    // Inicializar o hash com a sua funcao
    int hash = Escolha_Hash(l, palavra, escolhaHash);

    // Inicializar um novo termo, que será inserido na tabela
    TElementoAberto *novo = new TElementoAberto;
    novo->palavra = palavra;
    novo->proximo = nullptr;
    novo->ativo = true;
    novo->frequencia++;

    // Se a flag de ativo estiver falsa, iremos inserir o termo nesta posição.
    if (l.tabela[hash]->ativo == false) {
        l.tabela[hash] = novo;
        l.ocupacao++;

    // Se não iremos verificar qual a proxima posição que pode ser utilizada.
    } else {

        // Navegar a tabela encadeada para descobrir qual a proxima posição vaga.
        // Ou se esta palavra ja esxite na tabela.
        TElementoAberto* nav = l.tabela[hash];
        while (nav->proximo != nullptr && nav->palavra != palavra) {
            nav = nav->proximo;
            l.colisao++;
        }
        // Se a palavra já existe na tabela, apenas aumentaremos a frequencia em 1.
        if (nav->palavra == palavra) {
            nav->frequencia++;

        // Se a palavra não existir, então iremos inserir na próxima posição nula.
        } else if (nav->proximo == nullptr) {
            nav->proximo = novo;
        }
    }
}

void Deletar_Hash_Aberto(TabelaHashAberta &l, string palavra, int escolhaHash) {
    // Inicializar variaveis essênciais
    int hash = Escolha_Hash(l, palavra, escolhaHash);
    int contador = 0; 
    // Se a flag de ativo estiver falsa quer dizer que não existe nenhum termo nesta posição,
    // Então não há nada a ser deletado.
    if (l.tabela[hash]->ativo == false) {
        cout << "Não foi possivel remover nenhum item";

    // Caso haja termos nesta posição da tabela, então será verificado caso essa palavra exista, para então ser deletada
    } else {

        // Navegar a tabela encadeada para descobrir qual a proxima posição vaga.
        // Ou se esta palavra existe na tabela.
        TElementoAberto* nav = l.tabela[hash];
        while (nav->proximo != nullptr && nav->palavra != palavra) {
            nav = nav->proximo;
            contador++;
        }

        // Se a palavra existe na tabela, ela será deletada.
        if (nav->palavra == palavra) {

            // Caso a frequencia desta palavra seja 1, ela será deletada da tabela.
            if (nav->frequencia == 1) {
                TElementoAberto* Apagar = nav;
                nav->ativo = Apagar->proximo->ativo;
                nav->frequencia = Apagar->proximo->frequencia;
                nav->palavra = Apagar->proximo->palavra;
                nav->proximo = Apagar->proximo->proximo;
                delete Apagar;
                cout << "O item " << palavra <<" foi removido da posição " << hash << " | " << contador << " com sucesso!\n";
                // Se o nav->proximo for nulo quer dizer que a posição está vazia
                if(nav->proximo == nullptr){
                    nav->ativo = false;
                }
            // Caso a frequencia seja maior que 1, será diminuido a sua frequência
            } else {      
                cout << "O item " << palavra <<" foi diminuido da posição " << hash << " | " << contador << " com sucesso!\n";
                cout << "Antes ele aparecia [" << nav->frequencia << " vezes,\n";
                nav->frequencia--;
                cout << "Agora ele aparece [" << l.tabela[hash]->frequencia << " vezes.\n";
            }
        // Se a palavra não existir na tabela será avisado ao usuário
        } else if (nav->proximo == nullptr) {
            cout << "Não foi possivel remover o item [" << palavra << "]\n";
        }
    }
}


TElementoAberto* Buscar_Hash_Aberto(TabelaHashAberta &l, string palavra, int escolhaHash) {
    int hash = Escolha_Hash(l, palavra, escolhaHash);

    if(l.tabela[hash]->palavra == palavra){
        cout << "return l.tabela[hash]\n";
        return l.tabela[hash];
    } else {
        TElementoAberto* nav = l.tabela[hash];
        while (nav->proximo != nullptr && nav->palavra != palavra) {
            nav = nav->proximo;
        }
        if(nav->palavra == palavra){
            cout << "return nav\n";
            return nav;
        }
    }
    cout << "return nullptr\n";
    return nullptr;
}

#endif