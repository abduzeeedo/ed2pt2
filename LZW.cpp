#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "LZW.h"

struct Node{
	int index;
	string data;
	Node *next;
};

void st_Node(Node *head, int index, string data){
	head->index = index;
	head->data = data;
	head->next = NULL;
}

void insert_Node(Node *head, int index, string data){
	Node *new_Node = new Node;
	new_Node->index = index;
	new_Node->data = data;
	new_Node->next = NULL;

	Node *curr = head;
	while (curr != NULL)
	{
		if (curr->next == NULL)
		{
			curr->next = new_Node;
			return;
		}
		curr = curr->next;
	}
}

Node *search_Node(Node *head, string data)
{
	Node *curr = head;
	while (curr != NULL)
	{
		if (data.compare(curr->data) == 0)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}

Node *search_Node(Node *head, int index)
{
	Node *curr = head;
	while (curr != NULL)
	{
		if (index == curr->index)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}

bool delete_Node(Node *head, Node *to_delete){
	if (to_delete == NULL)
		return false;
	else if (to_delete == head)
	{
		head = to_delete->next;
		delete to_delete;
		return true;
	}
	else{
		Node *curr = head;
		while (curr)
		{
			if (curr->next == to_delete)
			{
				curr->next = to_delete->next;
				delete to_delete;
				return true;
			}
			curr = curr->next;
		}
		return false;
	}
}

vector <string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

string LZW(string input, int option)
{
	if (option == 1)
	{
		Node *dictionary = new Node;
		string result;
		int length, last_seen, index = 128;

		st_Node(dictionary, 32, " ");
		for (int i = 33; i < 128; i++)
		{
			string data;
			data = i;
			insert_Node(dictionary, i, data);
		}

		length = (int)input.length();

		for (int i = 0; i < length; i++)
		{
			Node *searched;
			string search;
			search = input[i];

		re_search:
			searched = search_Node(dictionary, search);
			if (searched)
			{
				i++;
				search += input[i];
				last_seen = searched->index;
				if (i != length)
					goto re_search;
				else
					goto print;
			}
			else
			{
				insert_Node(dictionary, index, search);
				index++;
			print:
				result += to_string(last_seen) + " ";
				i--;
			}
		}

		return result;
	}
	if (option == 2)
	{
		Node *dictionary = new Node;
		string result;
		int index = 128;

		st_Node(dictionary, 32, " ");
		for (int i = 33; i < 128; i++)
		{
			string data;
			data = i;
			insert_Node(dictionary, i, data);
		}

		vector <string> s_input = split(input, ' ');
		for (int i = 0; i < s_input.size(); i++)
		{
			Node *searched;
			int search;
			search = stoi(s_input[i]);

			searched = search_Node(dictionary, search);

			string cur, prev, data;
			if (searched)
				cur = search_Node(dictionary, stoi(s_input[i]))->data;
			if (i != 0)
				prev = search_Node(dictionary, stoi(s_input[i - 1]))->data;
			else
				prev = cur;

			int show = 0;
			if (searched)
			{
				result += searched->data;

				if (i != 0)
				{
					data = prev + cur[0];
					if (show != 1)
					{
						insert_Node(dictionary, index, data);
						index++;
					}
				}
				show = 0;
			}
			else
			{
				data = prev + prev[0];
				insert_Node(dictionary, index, data);
				index++;
				show = 1;
				result += data;
			}
		}

		return result;
	}
}
