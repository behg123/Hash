#ifndef FUNCOESHASH_H
#define FUNCOESHASH_H

#include <iostream>
#include <cmath>
using namespace std;

int hashSomaTermos(string Key, int m) {
  int soma = 0;
  for (int i = 0; i < Key.size(); i++) {
    soma = soma + Key.at(i);
  }
  return soma % m;
}

int hashMultTermos(string Key, int m) {
  int mult = 1;
  for (int i = 0; i < Key.size(); i++) {
    mult *= Key.at(i);
  }
  if(mult < 0){
    mult = -mult;
  }
  return mult % m;
}

int hashMultMethod(string Key, int m) {
  int soma = 0;
  float A = 0.84721;
  float z = 1;
  for (int i = 0; i < Key.size(); i++) {
    soma = soma + Key.at(i);
  }
  float mod = fmod(soma * A, z);
  return mod * m;
}

void LimparTela(){
  system("pause");
  system("cls");
}


#endif