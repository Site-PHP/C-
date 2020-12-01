#include <iostream>
#include <string>
#include <regex>

using namespace std;
/*
 * Fichier contenant des fonctions utiles pour la recuperation de lien
    */


void CurlLink(const string & Link){

    string fPath = "curl -L " + Link + " 2> err.txt > currentPage.txt";
    system(fPath.c_str());
}

bool isValidAdress(const string& link){
    regex linkBegin {"^http"}; // Verification que le lien comence bien par un http au moins
    vector<regex> endExtension(8); //M Tableau contenant les extensions a ne pas avoir
    endExtension[0] = ".jpg$";
    endExtension[1] = ".png$";
    endExtension[2] = ".gif$";
    endExtension[3] = ".jpeg$";
    endExtension[4] = ".h$";
    endExtension[5] = ".pptx$";
    endExtension[6] = ".zip$";
    endExtension[7] = ".pdf$";

    cout << "check http" << endl;
    if(!regex_search(link, linkBegin))
        return false;

    cout << "check extention" << endl;
    for(regex extension : endExtension){
        if(regex_search(link, extension))
            return false;
    }

    return true;

}



