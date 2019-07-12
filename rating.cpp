/*
    Trabalho 2 de Estrutura de Dados 2
    Bruno Carvalho
    Diogo Destefano
    Fernanda Silva
    Thiago Guimarães
*/
#include "rating.h"



// Construtor sobrecarregado para poder utilizar dois tipos de inicializa��o
Rating::Rating()
{
}
//Construtor Padrao
Rating::Rating(int uid, int mid, float ra, string ov)
{
	userID = uid;
	movieID = mid;
	rating = ra;
	overview = ov;
}
//Funcao que adiciona um rating
void Rating::addRating(int uid, int mid, float ra, string ov)
{
	userID = uid;
	movieID = mid;
	rating = ra;
	overview = ov;
}
//Retorna o UserID de um objeto
int Rating::getUserID()
{
	return userID;
}
//Atribui um UserID a um objeto
void Rating::setUserID(int uid) {
	userID = uid;
}
//Retorna o ID de filme de um objeto
int Rating::getMovieID()
{
	return movieID;
}
//Atribui um ID de filme a um objeto
void Rating::setMovieID(int mid) {
	movieID = mid;
}
//Retorna o Rating do filme de um objeto
float Rating::getRating()
{
	return rating;
}
//Atribui um Rating do filme a um objeto
void Rating::setRating(float ra) {
	rating = ra;
}
//Retorna a Sinopse de um objeto
string Rating::getOverview()
{
	return overview;
}
//Atribui uma Sinopse a um objeto
void Rating::setOverview(string ov) {
	overview = ov;
}
//Imprime Rating em tela
void Rating::printRating() {
	cout << "UserID:" << userID << " MovieID:" << movieID << " Rating:" << rating << " Sinopse:" << overview << endl << "\n";
}
//Destrutor
Rating::~Rating() {}
