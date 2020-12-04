#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "utils.cpp"

using namespace std;

/*
 * Fichier contenant la fonction qui ecrit les liens dans le fichier temporaire
*/



void ReadPage(){
    ifstream monFlux("currentPage.txt");  //Ouverture d'un fichier en lecture
    ofstream linksFlux("listLink.txt");

    if(monFlux)
    {
        int isBody = -1;
        string ligne;
        while (getline(monFlux,ligne) && isBody == -1) { // descends d'une ligne j'usqu'a trouver le body
            isBody = ligne.find("<body");
        }


        //Tout est prêt pour la lecture.

        while(getline(monFlux,ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
                    string sous_ligne = ligne;
                    string sous_ligne2 = ligne;
                    int a = -1;
                    a = ligne.find("href=\"");
                    int b;

                    while (a != -1){
                        a = a+6;
                        sous_ligne =sous_ligne.substr(a);
                        b = sous_ligne.find("\"");
                        string lien =sous_ligne.substr(0,b);
                        if(isValidAdress(lien))
                            linksFlux << lien << endl;

                        sous_ligne = sous_ligne.substr(b+1);
                        a = -1;
                        a = sous_ligne.find("href=\"");
                }

                    int c = -1;
                    c = ligne.find("href=\'");
                    int d;

                    while (c != -1){
                        c = c+6;
                        sous_ligne2 =sous_ligne2.substr(c);
                        d = sous_ligne2.find("\'");
                        string lien =sous_ligne2.substr(0,d);
                        if(isValidAdress(lien))
                            linksFlux << lien << endl;
                        sous_ligne2 = sous_ligne2.substr(d+1);
                        c = -1;
                        c = sous_ligne2.find("href=\'");
                }

        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}
