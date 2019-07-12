/*
    Trabalho 2 de Estrutura de Dados 2
    Bruno Carvalho
    Diogo Destefano
    Fernanda Silva
    Thiago Guimarães
*/

#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include "rating.h"
#include "funcoesGerais.h"

struct No; //estrutura de um no
void st_No(No *pri, int id, string val); //instancia a lista
void insere_No(No *pri, int id, string val); //insere um No no encadeamento
No *procura_No(No *pri, string val); //procura um no por uma string
No *procura_No(No *pri, int id); // procura no por user ID
bool deleta_No(No *pri, No *to_delete); //deleta no do encadeamento
vector <string> split(string str, char delimiter); //divide uma string
string LZW(string input); //algoritmo LZW de compressao

#endif // LZW_H_INCLUDED
