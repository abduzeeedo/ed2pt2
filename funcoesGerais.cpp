#ifndef FUNCOESGERAIS_CPP_INCLUDED
#define FUNCOESGERAIS_CPP_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "rating.h"
#define TAM 100
#include "funcoesGerais.h"
#include "Huffman.h"
#include "LZW.h"
#include <ctime>
#include <algorithm>

string saidaHuff = "";
string saidaLZWW = "";

//Funcao de Impressao de Menu
//Entrada: Arquivo .txt do menu a ser impresso em tela
//Saida: Impressao em tela do Menu de opcoes
void imprimeMenu(){

    ifstream leitor;
    leitor.open("menu.txt");//Le o menu to txt
	string buffer;

    if (leitor.is_open()){
        while(!leitor.eof()){
            getline(leitor, buffer);
            cout << buffer << endl;
        }
        leitor.close();
    }
    else {
        cout << "Erro ao abrir Arquivo Menu!" << endl;
    }

}

//Funcao Que salva uma string em um arquivo .txt
//Entrada: String a ser salva e arquivo .txt onde os dados serao salvos.
//Saida: Escrita da string passada por parametro em um arquivo .txt (tambem passado por parametro)
void salvarTxt(string salvar, string file) {
	ofstream arquivo;
	arquivo.open(file);
	arquivo << salvar << endl;
}

//Funcao randomiza o conteudo de um vetor de sinopses
//ENTRADA: Ponteiro para vetor do tipo rating e tamanho do vetor
//SAIDA: O vetor de rating com valores entre as posicoes randomizados (desordenado)
void randomiza(Rating** vetor, int tam) {
	for (int i = 0; i < tam; i++)
	{
		srand(2 * i + tam); //Troca a seed do rand a cada iteraçao
		swap(vetor[rand() % tam], vetor[rand() % tam]);
	}
}

//imprime vetor de objetos (todos os dados)
void imprimeObjetos (Rating** vetor, int tam){
    for (int i=0; i < tam; i++){
        vetor[i]->printRating();//imprime os valores dos tam objetos
    }
}

//Funcao de leitura do arq e inclusao para um vetor de objetos do tipo Rating (com Overview)
//entrada: o vetor objetos do tipo rating, e o tamanho desse vetor
//saida: o vetor de objetos do tipo rating totalmente preenchido com valores do arquivo overview.csv (sinopses)
void instanciaObjArq (Rating** vetor, int tam){

    srand(time(NULL));
    ifstream arquivo;
    arquivo.open("overview.csv");

    string buffer;
    int userID;
    int movieID;
    float rating;
    string overview;

    int pos = 0; //posicao do vetor de objetos

    if(arquivo.is_open()){

        ///pula primeira linha
        getline(arquivo, buffer);
        cout << "Inicializando vetor de objetos a partir do arquivo overview.csv. Tamanho do vetor:" << tam << endl;
        cout << "Por favor, aguarde..." << endl;
        ///Pega linhas e vai adicionando em posicoes do vetor de objetos
        while(pos < tam){

                getline(arquivo, buffer, ';');
                userID = stoi(buffer);

                getline(arquivo, buffer, ';');
                movieID = stoi(buffer);

                getline(arquivo, buffer, ';');
                rating = stof(buffer);

                getline(arquivo, buffer, '\n');
                overview = buffer;

                //vetor[pos]->addRating(userID, movieID, rating, overview);

                Rating* aux = new Rating(userID, movieID, rating, overview); //cria um objeto auxiliar, colocando os valores lidos do arquivo
                vetor[pos] = aux; //atribui tais valores pra uma posicao do vetor de objetos
                pos++;
        }
        arquivo.close();
        randomiza(vetor, tam); //Chama funcao que randomiza a posicao dos objetos do vetor

    }
    else
        cout << "Erro ao abrir o arquivo !" << endl;
}

//Remove os espacos a mais de uma string, feito in-place e O(n) onde n eh o tamanho da string (sinopse)
//ENTRADA: uma string (sinopse)
//SAIDA: a mesma string, sem espacos desnecessarios (apenas um espaco entre cada palavra)
void removeEspaco(string &str)
{
	//i = posicao vazia na "nova" string
	//j = posicao da proxima letra a ser inserida na string original
	//tam = tamanho da string (condicao de parada)
	//espaco = flag para nao retirar espacos necessarios (precisa ter pelo menos um espaco entre cada palavra)
	size_t tam = str.length();
	short i = 0;
	short j = -1;
	bool espaco = false;

	//Percorre por todos os espacos no comeco do texto, se houver algum
	if (str[++j] == ' ')
		while (++j < tam && str[j] == ' ');

	//Comeca a leitura da string
	while (j < tam)
	{
		if (str[j] != ' ')
		{
			str[i++] = str[j++]; //Coloca a letra da posicao j na posicao i e aumenta os indices
			espaco = false; //Quando o caractere encontrado e uma letra, coloca a flag como false
		}
		else if (str[j++] == ' ')
		{
			if (!espaco)
			{
				str[i++] = ' '; //Adiciona apenas um espaco (necessario) entre uma palavra e outra
				espaco = true; //Quando o caractere encontrado nao e uma letra, coloca a flag como true
			}
		}
	}
	//Remove todos os epacos no final do texto, se houver algum
	if (i <= 1)
		str.erase(str.begin() + i, str.end());
	else
	{
		if (str[i - 1] == ' ')
			str.erase(str.begin() + i - 1, str.end());
		else
			str.erase(str.begin() + i, str.end());
	}
}

//Verifica se a letra e valida (se e de A a Z ou um numero)
//ENTRADA: uma variavel do tipo const char
//SAIDA: verdadeiro/falso dependendo se a variavel eh uma letra/numero ou nao
bool charInvalido(const char &c)
{
	if ((c <= 'Z' && c >= 'A') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		return false;
	else
		return true;
}

//Funcao para ler os N numeros aleatorios do arquivo entrada.txt
//ENTRADA: Arquivo .txt com dados de N numero aleatorios a serem inseridos
//SAIDA: Vetor do tipo Vector onde cada posicao contem um nemero contido em uma linha do arquivo passado por parametro
vector<int> importaEntrada(const char* nomeArquivo)
{
	int i = 0; //Variavel para controlar a posicao do vetor
	string linha; //Variavel para armazenar a linha no getline
	ifstream arquivo(nomeArquivo); //Abre o arquivo
	int N; //Tamanho do vetor
	if (arquivo.is_open()) //Verifica se o arquivo esta aberto
	{
		getline(arquivo, linha); //Le a primeira linha do arquivo
		N = atoi(linha.c_str()); //Converte string para int
		vector<int> vEntrada(N); //Cria o vetor com N posicoes lidas da primeira linha
		while (!arquivo.eof()) //Continua lendo o arquivo
		{
			getline(arquivo, linha);
			vEntrada[i] = atoi(linha.c_str()); //Armazena na posicao i do vetor o numero lido da linha
			i++;
		}
		arquivo.close(); //Fecha o arquivo
		return vEntrada; //Retorna o vetor
	}
	else //Caso o arquivo nao esteja aberto, mostra um erro.
		cout << "Erro ao abrir arquivo " << nomeArquivo << endl;
}

//Remove todas as pontuacoes, espacos, caracteres especiais e coloca todas as letras em minusculo
//ENTRADA: Uma string (sinopse)
//SAIDA: Uma string contendo as mesmas palavras da entrada porem em letras minusculas e sem sinais de pontuacao.
string limpaString(string original)
{
	string s = original;
	/*Nao usamos o erase/remove porque em sinopses que nao existe espacos entre a pontuacao, as palavras ficariam todas juntas dificultando dividir o sinopse em varias palavras
	Exemplo: usando erase/remove no sinopse Exemplo.de.sinopse, iria ficar Exemplodesinopse e isso ia contar como uma palavra so
	Usando o replace_if com espacos, ficaria Exemplo de sinopse, o que eh o certo*/
	transform(s.begin(), s.end(), s.begin(), ::tolower);//Coloca as letras em minusculo
	replace_if(s.begin(), s.end(), charInvalido, ' ');//Troca todos os sinais de pontuacao e caracteres especiais por espacos
	removeEspaco(s);//Remove os espacos desneessarios
	return s;
}

//Metodo que seleciona via codigo de comando a funcao a ser executada e finaliza execucao
//ENTRADA: Vetor de objetos do tipo ratings e o tamanho deste vetor
//SAIDA: Chamada de funcoes de acordo com o codigo inserido pelo usuario
void codigoFuncao(Rating* vet[], int tam) {
	string code;
	/*Essa funcao sera usada para importar os sinopses, cada posicao do vetor contem um numero
	que indica o numero de sinopses aleatorios que devem ser importados e instanciados
	para serem comprimidos*/
	vector<int> vEntrada = importaEntrada("entrada.txt");

	while (true) {
		cout << endl << "Insira o Codigo de Funcao: (0 para imprimir menu, -1 para Encerrar Execucao,)" << endl;
		cin >> code;
		if (code == "-1") {
			return; //Finaliza a Execucao
		}

		if (code == "0") {
			imprimeMenu();//Imprime o Menu (via arquivo txt)
		}

		if (code == "1") {
			cout << "Fazendo a compressao de sinopses usando metodo Huffman..." << endl;
			string comprime;
			string saida_Huf = "";

			for (int i =0; i < 5; i++){
                string nomeArq = "";
                saidaHuff.clear();
                for (int v = 0; v < vEntrada.size(); v++){
                    Huffman* huf = new Huffman();

                    /*Exibindo e salvando dados de entrada*/
                    cout << endl;
                    saidaHuff += "\n================================================================================\n";
                    cout << "Iteracao " << v+1 << " de " << vEntrada.size() << "." << endl;
                    saidaHuff += "Metodo Huffman - Iteracao " + to_string(v+1) + " de " + to_string(vEntrada.size()) + ".\n";
                    cout << "Fazendo a compressao de " << vEntrada[v] << " sinopses." << endl;
                    saidaHuff += "Fazendo a compressao de " + to_string(vEntrada[v]) + " sinopses.\n";

                    /*Randomizando o vetor de entrada a cada iteracao*/
                    cout << "[1] Randomizando o vetor de sinopses." << endl;
                    randomiza(vet, tam);

                    cout << "[2] Criando string com " << vEntrada[v] << " sinopses." << endl;
                    /*Cria uma string com todos os sinopses que foram passados*/
                    for (int h = 0; h < vEntrada[v]; h++)
                    {
                        comprime += vet[h]->getOverview();
                        comprime += "\n"; //Pula uma linha a cada sinopse
                    }

                    cout << "[3] Salvando string em arquivo de texto." << endl;
                    /*Salva a string sem estar comprimida num TXT para comprar os tamanhos depois*/
                    string arquivoSemCompressao = "Huffman_SemCompressao_Iteracao_" + to_string(v+1) + " Seed=" + to_string(i) + ".txt";
                    salvarTxt(comprime, arquivoSemCompressao);

                    cout << "[4] Codificando a string." << endl;
                    /*Comprime a string*/
                    saida_Huf = huf->codifica(comprime);

                    cout << "[5] Salvando string codificada em um novo arquivo de texto." << endl;
                    /*Salva a string comprimida bit por bit em um novo TXT*/
                    string arquivoCompresso = "Huffman_Compresso_Iteracao_" + to_string(v+1) + " Seed=" + to_string(i) + ".txt";
                    huf->salvaBinario(arquivoCompresso, saida_Huf);

                    /*Exibindo e salvando dados de saida*/
                    cout << "Compressao de sinopses usando metodo Huffman completa." << endl;
                    saidaHuff += "Compressao de sinopses usando metodo Huffman completa.\n";

                    cout << "Tamanho ocupado antes da compressao: " << comprime.size() << " bytes." << endl;
                    saidaHuff += "Tamanho ocupado antes da compressao: " + to_string(comprime.size()) + " bytes.\n";

                    cout << "Tamanho ocupado apos a compressao: " << saida_Huf.size() / 8 << " bytes." << endl; //Divide por 8 pois como eh uma string, cada 1 e 0 tem 8 bits e nao 1.
                    saidaHuff += "Tamanho ocupado apos a compressao: " + to_string(saida_Huf.size()/8) + " bytes.\n"; //Divide por 8 pois como eh uma string, cada 1 e 0 tem 8 bits e nao 1.

                    float taxa;
                    float result1 = saida_Huf.size()/8;
                    float result2 = comprime.size();

                    taxa = result1/result2;

                    cout << "Taxa de compressao: " << taxa << ", Ou seja, cerca de " << taxa*100 << "%" << endl;
                    saidaHuff += "Taxa de compressao: " + to_string(taxa) + ", Ou seja, cerca de " + to_string(taxa*100) + "%\n";

                    cout << "Tempo gasto pela compressao: " << huf->getTempoGasto() << endl;
                    saidaHuff += "Tempo gasto pela compressao: " + to_string(huf->getTempoGasto());
                    cout << endl;
                    saidaHuff += "\n================================================================================\n";
                    nomeArq = "resultados(Huffman)-para-seed " + to_string(i) + ".txt";
                    salvarTxt(saidaHuff, nomeArq);
                    comprime.clear();
                    saida_Huf.clear();
                    delete huf;
                }
			}
		}

		if (code == "2") {
			cout << "Fazendo a compressao de sinopses usando metodo LZW..." << endl;
			string comprime;
			string saida_lzw = "";

			for (int i =0; i < 5; i++){
                string nomeArq = "";
                saidaLZWW.clear();
                for (int v = 0; v < vEntrada.size(); v++){
                    /*Exibindo e salvando dados de entrada*/
                    cout << endl;
                    saidaLZWW += "\n================================================================================\n";
                    cout << "Iteracao " << v+1 << " de " << vEntrada.size() << "." << endl;
                    saidaLZWW += "Metodo LZW - Iteracao " + to_string(v+1) + " de " + to_string(vEntrada.size()) + ".\n";
                    cout << "Fazendo a compressao de " << vEntrada[v] << " sinopses." << endl;
                    saidaLZWW += "Fazendo a compressao de " + to_string(vEntrada[v]) + " sinopses.\n";

                    /*Randomizando o vetor de entrada a cada iteracao*/
                    cout << "[1] Randomizando o vetor de sinopses." << endl;
                    randomiza(vet, tam);

                    cout << "[2] Criando string com " << vEntrada[v] << " sinopses." << endl;
                    /*Cria uma string com todos os sinopses que foram passados*/
                    for (int h = 0; h < vEntrada[v]; h++)
                    {
                        comprime += vet[h]->getOverview();
                        comprime += "\n"; //Pula uma linha a cada sinopse
                    }

                    cout << "[3] Salvando string em arquivo de texto." << endl;
                    /*Salva a string sem estar comprimida num TXT para comprar os tamanhos depois*/
                    string arquivoSemCompressao = "LZW_SemCompressao_Iteracao_" + to_string(v+1) + " Seed=" + to_string(i) + ".txt";
                    salvarTxt(comprime, arquivoSemCompressao);

                    cout << "[4] Codificando a string." << endl;
                    /*Comprime a string*/

                    clock_t inicioClock;
                    clock_t fimClock;
                    inicioClock = clock();

                    saida_lzw = LZW(comprime, 1);

                    fimClock = clock();
                    float tempoTotal = fimClock-inicioClock;
                    tempoTotal = tempoTotal / CLOCKS_PER_SEC;

                    cout << "[5] Salvando string codificada em um novo arquivo de texto." << endl;
                    string arquivoCompresso = "LZW_Compresso_Iteracao_" + to_string(v+1) + " Seed=" + to_string(i) + ".txt";
                    salvarTxt(saida_lzw, arquivoCompresso);

                    /*Exibindo e salvando dados de saida*/
                    cout << "Compressao de sinopses usando metodo LZW completa." << endl;
                    saidaLZWW += "Compressao de sinopses usando metodo LZW completa.\n";

                    cout << "Tamanho ocupado antes da compressao: " << comprime.size() << " bytes." << endl;
                    saidaLZWW += "Tamanho ocupado antes da compressao: " + to_string(comprime.size()) + " bytes.\n";

                    cout << "Tamanho ocupado apos a compressao: " << saida_lzw.size()/2 << " bytes." << endl; //divide-se por 2 pois os numeros sao representados por 8 bits (char qualquer), enquanto poderiam ser representados por 4
                    saidaLZWW += "Tamanho ocupado apos a compressao: " + to_string(saida_lzw.size()/2) + " bytes.\n"; //divide-se por 2 pois os numeros sao representados por 8 bits (char qualquer), enquanto poderiam ser representados por 4

                    float taxa;
                    float result1 = saida_lzw.size()/2;
                    float result2 = comprime.size();

                    taxa = result1/result2;

                    cout << "Taxa de compressao: " << taxa << ", Ou seja, cerca de " << taxa*100 << "%" << endl;
                    saidaLZWW += "Taxa de compressao: " + to_string(taxa) + ", Ou seja, cerca de " + to_string(taxa*100) + "%\n";

                    cout << "Tempo gasto pela compressao: " << tempoTotal << endl;
                    saidaLZWW += "Tempo gasto pela compressao: " + to_string(tempoTotal);
                    cout << endl;
                    saidaLZWW += "\n================================================================================\n";
                    nomeArq = "resultados-LZW-para-seed " + to_string(i) + ".txt";
                    salvarTxt(saidaLZWW, nomeArq);
                    comprime.clear();
                    saida_lzw.clear();
                }
			}
		}
	}
}

#endif // FUNCOESGERAIS_CPP_INCLUDED
