/*
    Trabalho 2 de Estrutura de Dados 2
    Bruno Carvalho
    Diogo Destefano
    Fernanda Silva
    Thiago Guimarães
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include "rating.h"
#define TAM 100
#include "funcoesGerais.h"
#include "Huffman.h"

using namespace std;

int main()
{
    //**************INSTANCIANDO VETOR DE OBJETOS, INSERINDO INFOS DO ARQUIVO CSV ****************************
    int tam = 40000; // TAMANHO DO VETOR DE OBJETOS A SER INSTANCIADO E IMPRESSO EM TELA
    Rating** objetos = new Rating*[tam]; // instanciando um vetor da classe Ratings com tam ratings
    instanciaObjArq(objetos, tam); //Atribui valores no vetor exemplo com tam valores do arquivo Overview.csv

    // IMPRESSAO DO MENU E CRIAÇÃO DE MENU DE USUARIO
    imprimeMenu();

    codigoFuncao(objetos, tam); //Seleciona a funcao ou encerra a execucao;

    cout << "Execução finalizada com Sucesso!" << endl;
    delete objetos;
    return 0;
}
