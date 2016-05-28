//
// Created by ph on 27.05.16.
//

#include "DataReader.h"
#include <Exceptions.h>

int DataReader::dataread(string pathName){
    ifstream file;

    file.open(pathName, ios::in);
    if (!file) {
        throw FileNotExists();
    } else {
        string nLine;
        string nodeValueLine;
        string interpolNodeValueLine;

        regex integer("[0-9]+");

        if(getline(file,nLine) && regex_match(nLine,integer)){
            this->n=stoi(nLine);
        }
        else{
            throw InvalidFileFormat();
        }


        char nodesValueRegexString [50];
        sprintf(nodesValueRegexString,"([-+]?(\\d*[.])?\\d+ ){%d}[-+]?(\\d*[.])?\\d+ ?",this->n);

        regex nodeValueRegex(nodesValueRegexString);
        smatch match;

        if(getline(file,nodeValueLine) && regex_match(nodeValueLine, match,nodeValueRegex)){
            istringstream ss (nodeValueLine);
            int i=0;
            while(!ss.eof()) {
                string liczba;
                getline(ss, liczba, ' ');
                this->xINT[i]=Interval<long double>::IntRead(liczba);
                stringstream convertToLD(liczba);
                convertToLD >> this->xLD[i];
                i++;
            }
        }
        else{
            throw InvalidFileFormat();
        }

        regex interpolNodeValueRegex(nodesValueRegexString);

        if(getline(file,interpolNodeValueLine) && regex_match(interpolNodeValueLine, match,interpolNodeValueRegex)) {
            istringstream ss (interpolNodeValueLine);
            int i=0;
            while(!ss.eof()) {
                string liczba;
                getline(ss, liczba, ' ');
                this->fINT[i]=Interval<long double>::IntRead(liczba);
                stringstream convertToLD(liczba);
                convertToLD >> this->fLD[i];
                i++;
            }

        }
        else{
            throw InvalidFileFormat();
        }

        string xxLine;
        regex xxLineRegex("[-+]?(\\d*[.])?\\d+");

        if(getline(file,xxLine) && regex_match(xxLine, match,xxLineRegex)) {
            this->xxINT=Interval<long double>::IntRead(xxLine);
            stringstream convertToLD(xxLine);
            convertToLD >> this->xxLD;
        }
        else{
            throw InvalidFileFormat();
        }

    }
}

void DataReader::displayOpeningError() {
    printf("File cannot be opened!\n");
}
