/*
    Trabalho 2 de Estrutura de Dados 2
    Bruno Carvalho
    Diogo Destefano
    Fernanda Silva
    Thiago Guimarães
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "LZW.h"

//Estrutura de um nó do encadeamento
struct No{
	int id;
	string val;
	No *prox;
};

/*
FUNCAO DE  A LISTA DE NOS
Entrada: Ponteiro para o primeiro nó do encadeamento, id e valor de tal nó
Saida: Lista instanciada
*/
void st_No(No *pri, int id, string val){
	pri->id = id;
	pri->val = val;
	pri->prox = NULL;
}

/*
FUNCAO DE INSERIR UM NO NA LISTA
Entrada: Ponteiro para o primeiro nó do encadeamento, id e valor do nó a ser inserido
Saida: No adicionado na lista
*/
void insere_No(No *pri, int id, string val){
	No *new_No = new No;
	new_No->id = id;
	new_No->val = val;
	new_No->prox = NULL;

	No *curr = pri;
	while (curr != NULL)
	{
		if (curr->prox == NULL)
		{
			curr->prox = new_No;
			return;
		}
		curr = curr->prox;
	}
}

/*
FUNCAO DE BUSCAR UM NO PELO SEU VALOR
Entrada: Ponteiro para o primeiro nó da lista, valor de tal nó
Saida: Retorna o ponteiro pro nó se for encontrado, e NULL caso a lista não possua o nó com o valor passado
*/
No *procura_No(No *pri, string val)
{
	No *curr = pri;
	while (curr != NULL)
	{
		if (val.compare(curr->val) == 0)
			return curr;
		else
			curr = curr->prox;
	}
	return NULL;
}


/*
FUNCAO DE BUSCAR UM NO PELO SEU ID
Entrada: Ponteiro para o primeiro nó da lista, id de tal nó
Saida: Retorna o ponteiro pro nó se for encontrado, e NULL caso a lista não possua o nó com o id passado
*/
No *procura_No(No *pri, int id)
{
	No *curr = pri;
	while (curr != NULL)
	{
		if (id == curr->id)
			return curr;
		else
			curr = curr->prox;
	}
	return NULL;
}

/*
FUNCAO DE REMOVER NO DA LISTA
Entrada: Ponteiro para o primeiro nó do encadeamento, e ponteiro pro nó a ser removido
Saida: Caso exista na lista, remove
*/
bool deleta_No(No *pri, No *to_delete){
	if (to_delete == NULL)
		return false;
	else if (to_delete == pri)
	{
		pri = to_delete->prox;
		delete to_delete;
		return true;
	}
	else{
		No *curr = pri;
		while (curr)
		{
			if (curr->prox == to_delete)
			{
				curr->prox = to_delete->prox;
				delete to_delete;
				return true;
			}
			curr = curr->prox;
		}
		return false;
	}
}

/*
FUNCAO DE REALIZAR UM SPLIT NA STRING
Entrada: String a ser dividida e um char que delimita onde ela será dividida
Saida: um vetor com a divisao realizada
*/
vector <string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Transforma uma string numa stream
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

/*
FUNCAO DE REALIZAR A COMPACTACAO DA STRING VIA LZW
Entrada: String a ser comprimida
Saida: os codigos da compressao LZW em uma string
*/
string LZW(string input)
{

    No *dicionario = new No;
    string result;
    int length, last_seen, id = 128;

    st_No(dicionario, 32, " ");
    for (int i = 33; i < 128; i++)
    {
        string val;
        val = i;
        insere_No(dicionario, i, val);
    }

    length = (int)input.length();

    for (int i = 0; i < length; i++)
    {
        No *searched;
        string search;
        search = input[i];

        re_search:
        searched = procura_No(dicionario, search);
        if (searched)
        {
            i++;
            search += input[i];
            last_seen = searched->id;
            if (i != length)
                goto re_search;
            else
                goto print;
        }
        else
        {
            insere_No(dicionario, id, search);
            id++;
			print:
            result += to_string(last_seen) + " ";
            i--;
        }
    }
		return result;
}
