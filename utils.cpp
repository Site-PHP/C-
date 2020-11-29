#include <iostream>
#include <string>
#include <regex>

using namespace std;


void CurlLink(const string & Link){

    string fPath = "curl -L " + Link + " 2> err.txt > /home/samy/ProjetCpp/currentPage.txt";
    system(fPath.c_str());
}

bool isValidAdress(const string& link){
    regex linkBegin {"^http"}; // Verification que le lien comence bien par un http au moins
    vector<regex> endExtension(4); //M Tableau contenant les extensions a ne pas avoir
    endExtension[0] = {".jpg$"};
    endExtension[1] = {".png$"};
    endExtension[2] = {".gif$"};
    endExtension[3] = {".jpeg$"};

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

bool isFromMainSite(const string& link, const string& mainPath){

    return regex_search(link, regex(mainPath));
}

