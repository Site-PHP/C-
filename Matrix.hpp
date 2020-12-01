#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <string>
#include "readFile.cpp"


/*
 * Fichier contenant la classe Matrix qui va créer la matricer finale
 */

using namespace std;
using matrixAssoc = map<string,map<string, int>>;



class Matrix{
    private:
        matrixAssoc matLinks;
        unsigned size;

        string baseLink;
        const string K_externalName = "Exterieur"; //Ca ca sert a rien c'est juste pour changer les noms du debut dans la matrice si on veut
        const string K_lienName = "Liens";


    public:
        Matrix(const unsigned & size = 0, const string & link = "http://ens.casali.me");
        ~Matrix();
        void fillMatrix(); // Fonction qui remplie le tableau
        void initMatrix(); // Fonction qui mets les liens dans les bonnes cases
        void initMatrix2(matrixAssoc::iterator currentLink); // Fonction appelée par initMatrix()
        bool isInMatrix(const string & link);
        matrixAssoc getMatrix();
        bool isFromMainSite(const string& link); //retourne vrai si le lien est de la base du site, sinon faux



};



Matrix::Matrix(const unsigned & size, const string &link): size(size), baseLink(link)
{
    initMatrix();
    fillMatrix();
}

Matrix::~Matrix()
{

}



void Matrix::fillMatrix()
{
    for(matrixAssoc::iterator analyzedLink (matLinks.begin()++);  analyzedLink != matLinks.end(); ++analyzedLink){
        //On recupere le fichier contenant les liens de la page
        CurlLink(analyzedLink->first);
        ReadPage();
        ifstream linkFile("listLink.txt"); // Ouverture du fichier de lien
        if(linkFile){
            string linkInPage;
            while (getline(linkFile, linkInPage)) {
                if(isInMatrix(linkInPage)){
                    matLinks[analyzedLink->first][linkInPage]++;
                }
                else if(!isFromMainSite(linkInPage)){
                    matLinks[analyzedLink->first][K_externalName]++;
                }
            }
        }

    }


}

void Matrix::initMatrix()
{
    matLinks[K_lienName][K_externalName];
    matLinks[baseLink][K_externalName];
    matrixAssoc::iterator firstPage(matLinks.begin());
    firstPage++;
    initMatrix2(firstPage);


}

void Matrix::initMatrix2(matrixAssoc::iterator currentLink)
{
    CurlLink(currentLink->first);
    ReadPage();
    ifstream linkFile("listLink.txt"); // Ouverture du fichier de lien

    while (linkFile) {
        string lien;
        while(getline(linkFile, lien)){
            if(!isInMatrix(lien) && isFromMainSite(lien) && matLinks.size() < size){
                matLinks[K_lienName][lien];
                matLinks[lien][K_externalName] = 0;
            }
        }

    }

    if(matLinks.size() < size )
    {
        currentLink++;
        initMatrix2(currentLink);
    }
    else
    {
        return;
    }

}



bool Matrix::isInMatrix(const string &link)
{
    for(map<string,int>::iterator it = matLinks[K_lienName].begin(); it != matLinks[K_lienName].end(); ++it){
        if(it->first == link)
            return true;
    }
    return false;
}

matrixAssoc Matrix::getMatrix()
{
    return matLinks;
}

bool Matrix::isFromMainSite(const string& link){

    return regex_search(link, regex(baseLink));
}






#endif // MATRIX_HPP
