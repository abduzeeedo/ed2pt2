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

struct Node;
void st_Node(Node *head, int index, string data);
void insert_Node(Node *head, int index, string data);
Node *search_Node(Node *head, string data);
Node *search_Node(Node *head, int index);
bool delete_Node(Node *head, Node *to_delete);
vector <string> split(string str, char delimiter);
string LZW(string input, int option);

#endif // LZW_H_INCLUDED
