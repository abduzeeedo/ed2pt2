#ifndef FUNCOESGERAIS_H_INCLUDED
#define FUNCOESGERAIS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "rating.h"
#include "funcoesGerais.h"

void imprimeMenu(); //funcao que imprime o menu em tela
void salvarTxt(string salvar, string file); //salva os dados de uma string num arquivo txt, usado para exportar os resultados de execucao
void randomiza(Rating** vetor, int tam); //funcao que randomiza um vetor de objetos do tipo rating
void imprimeVetor(int* userId); //imprime um vetor de userID
void imprimeObjetos (Rating** vetor, int tam);//imprime os dados de um vetor de objetos do tipo Rating
void instanciaObjArq (Rating** vetor, int tam); //funcao que carrega um vetor de objetos do tipo Rating com informacoes do arquivo overview.csv
void codigoFuncao(Rating* vet[], int tam); //funcoes do menu principal, que executa os algoritmos de compressao


#endif // FUNCOESGERAIS_H_INCLUDED
