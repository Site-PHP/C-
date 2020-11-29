#include <iostream>
#include <string>
#include <regex>
#include "utils.cpp"
#include "readFile.cpp"

using namespace std;





int main()
{
/*
    if(isValidAdress("http://ens.casali.me/")){

        cout << "le lien est valide " << endl;
    }
    else{
        cout << "et bah nan" << endl;
    }
*/
    CurlLink("http://ens.casali.me/");
    ReadPage();


}



