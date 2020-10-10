#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    
    string inputfile, outputfile;
    int inputFD, outputFD;
    ssize_t bytesRd, bytesWr;
    int bufferSize = 32768;
    char buffer[bufferSize];
    char filenameIN[256], filenameOUT[256];
    cout << "Enter the name of input file\n";
    cin >> inputfile;
    cout << "Enter the name of output file\n";
    cin >> outputfile;
    strcpy(filenameIN, inputfile.c_str());
    strcpy(filenameOUT, outputfile.c_str());
    
    inputFD = open(filenameIN, O_RDONLY);
    if(inputFD == -1){
        perror("Error while opening input file\n");
        return 2;
    }
    
    outputFD = open(filenameOUT, O_WRONLY | O_CREAT, 0644);
    if(outputFD == -1){
        perror("Error while creating output file\n");
        return 3;
    }
    
    while((bytesRd = read(inputFD, &buffer, bufferSize)) > 0){
        bytesWr = write(outputFD, &buffer, (ssize_t)bytesRd);
        if(bytesRd != bytesWr){
            cout << "Error in writing\n";
            return 4;
        }else{
            cout << "Files copied correctly\n";
        }
    }
    
    close(inputFD);
    close(outputFD);
}
