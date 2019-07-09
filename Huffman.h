/*
    Trabalho 2 de Estrutura de Dados 2
    Bruno Carvalho
    Diogo Destefano
    Fernanda Silva
    Thiago Guimarães
*/

#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include "NoH.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <bitset>

using namespace std;

class Huffman
{
public:
	Huffman();
	string codifica(string); //Codifica uma string
	double getTempoGasto(); //Retorna o tempo gasto na codificacao
	void salvaBinario(string, string); //Salva a string de codigos bit por bit
	~Huffman();
private:
	double tempoGasto; //Tempo gasto para codificacao da string
	NoH *priLista; //Primeiro No da lista
	NoH *ultLista; //Ultimo No da lista
	NoH* getMenor(); //Menor No da lista
	void removeLista(NoH*); //Remove um no da lista
	void insere(char, int); //Insere o char C
	void criaArvore(); //Constroi arvore de Huffman
	string geraCodigoString(string); //Gera o codigo da string usando a arvore
	void geraCodigo(string, NoH*); //Pega todos os codigos presentes na arvore
	string codigos[26]; //Lista de caracteres minusculos
	void deletaNo(NoH*); //Deleta um no da Arvore
};
#endif // HUFFMAN_H_INCLUDED
