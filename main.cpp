#include <iostream>
#include <string>
#include <regex>
#include "Matrix.hpp"

using namespace std;


using MatAssoc = map<string,map<string, int>> ;

void afficheMatrice(MatAssoc matrix, const string & fileName)
{

    ofstream SortieMatrice(fileName);

    SortieMatrice << "Liens" << ",";
    for(map<string,int>::iterator nomLien = matrix["Liens"].begin(); nomLien != matrix["Liens"].end(); ++nomLien){
        SortieMatrice << nomLien->first << ",";
    }
    SortieMatrice << "\n";
    MatAssoc::iterator firstKey (matrix.begin());
    firstKey++;

    for(firstKey ; firstKey != matrix.end(); ++firstKey){
        SortieMatrice << firstKey->first + "," ;
        for(map<string, int>::iterator secondKey = firstKey->second.begin(); secondKey != firstKey->second.end(); ++secondKey ){

                SortieMatrice << secondKey->second << ",";


        }
        SortieMatrice << "\n";
    }

}






int main(int argc, char* argv[])
{

    string baseUrl = argv[1];
    int size = stoi(argv[2]);
    string fileName = argv[3];

    
    if(isValidAdress(baseUrl) && size <= 100 && regex_search(fileName,regex(".csv$"))){
        Matrix myMat(size, baseUrl);
        afficheMatrice(myMat.getMatrix(),fileName);
    }
    else{
        cout << "Invalid arguments" << endl;
    }


}





