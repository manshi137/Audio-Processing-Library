#include <stdio.h>
#include "foo.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    // foo();
    pred_t parr[3];
    std::string arr[12]= {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    
    pred_t *pred2 = (pred_t *) malloc(3*sizeof(pred_t));
    pred2 = libaudioAPI(argv[1],parr);
    ofstream outfile(argv[2],ios::app);
    outfile<<argv[1];
    outfile<< " ";
    outfile<< pred2[0].label<< " "<<pred2[1].label<< " " << pred2[2].label<<" "<< pred2[0].prob<<" "<<pred2[1].prob<< " " <<pred2[2].prob<<" ";
    outfile<< endl;
    outfile.close();
    puts("This is a shared library test...");
    return 0;
}