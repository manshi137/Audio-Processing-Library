#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
#include "/usr/local/Cellar/openblas/0.3.19/include/cblas.h"

using namespace std;

typedef struct {
    std::string label;
    float prob;
} pred_t;

int relu(string inputmatrix, string outputmatrix2)
{
    ifstream infile;
    infile.open(inputmatrix);
    
    ofstream outfile(outputmatrix2);
    if(!infile)
    cout<< "File cannot be opened."<<std::endl;	
    int cols;
    int rows;
    float num;
    infile >> cols;
    outfile<< cols<< endl;
    infile>> rows;
    outfile<< rows<<endl;
   // performing reLU function on elements of the input matrix and storing in the output file
    for(int j=0; j< cols; j++)
    {
        for(int i=0; i< rows; i++)
        {
            if(infile.eof())
            cout<< "End of file reached";
            infile>> num;
            num = max(0.0f, num);
            outfile<< num<< endl;
            
        }
    }
    infile.close();
    outfile.close();
    return 0;
}    

int softmax(string inputvector, string outputvector)
{
    ifstream infile;
    infile.open(inputvector);
    
    ofstream outfile(outputvector);
    if(!infile)
    cout<< "File cannot be opened."<<std::endl;	
    int len ;
    float num;
    infile>> len;
    outfile<<len<< endl;
    int ext ;
    infile >> ext;
    //cout<< ext<< endl;
    float sum=0.0;
    vector<float> v;
    //storing vector
    for(int i=0; i< len; i++)
    {
    infile>> num;
    v.push_back(num);
    sum += exp(num);
    // cout<<"num: "<<num<<endl;
    // cout<<"exp(num): "<<exp(num)<<endl;
    // cout<<"sum: "<<sum<<endl;
    }
    // cout << sum<<" $$$$$$"<< endl;
    //outputing result vector in output file
    for(int i=0;i<12;i++)
    {
    // cout <<exp(v[i])<<endl;
    // cout<<"sum: "<<sum<<endl;
    outfile<< exp(v[i])/sum<< endl;
    }
    infile.close();
    outfile.close();
    return 0;
}    

int FC1(string inputmatrix, string weightmatrix, string biasmatrix, string outputmatrix)
{
    //a is rows b is columns
    // ifstream in (inp);
    // float A[1][250];
    float* AA=(float*) malloc(250*1*sizeof(float));

    ifstream in1;
    in1.open(inputmatrix);
    if(in1.fail()){
        throw invalid_argument("Maybe 1File Does Not Exist.");
    }
    string st;
    cout<<"A"<<endl;
    for(int i=0;i<1;i++){
        for(int j=0;j<250;j++){
            getline(in1,st,' ');
            float f=stof(st);
            
            AA[i*250 + j]=f;
        }
    }
    in1.close(); 
    
    // float B[250][144];
    float* BB=(float*) malloc(144*250*sizeof(float));

    ifstream in2;
    in2.open(weightmatrix);
    if(in2.fail()){
        throw invalid_argument("Maybe 2File Does Not Exist.");
    }
    


    for(int i=0;i<250;i++){
        for(int j=0;j<144;j++){
            getline(in2,st,',');
            float f=stof(st);
            
            BB[i*144 + j]=f;
        }
    }
    in2.close(); 

    // float C[1][144];
    float* CC=(float*) malloc(144*1*sizeof(float));

    ifstream in3;
    in3.open(biasmatrix);
    if(in3.fail()){
        throw invalid_argument("Maybe 3File Does Not Exist.");
    }
    
    for(int i=0;i<1;i++){
        for(int j=0;j<144;j++){
            getline(in3,st,',');
            float f=stof(st);
            
            CC[i*144 + j]=f;
        }
    }
    in3.close(); 
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 1, 144, 250, 1.0, AA, 250, BB, 144, 1.0, CC, 144);
    // storing the final output in the given output file
    ofstream outfile(outputmatrix);
    outfile << 144<<endl;
    outfile << 1 << endl;
    for(int j=0; j< 144; j++)
    {
    	for(int i=0; i< 1; i++)
    	{
    	outfile<< CC[i*144 + j]<< endl;
    	}
    }


    // float product[1][144];
    // for(int a=0; a< 1; a++)
    // {
   	// for(int b=0; b< 144; b++)
   	// {
   	// product[a][b]=0;
   	// }
    // }
    // //for storing the product of the two matrices
    // for(int a=0; a< 1; a++)
    // {
   	// for(int b=0; b< 144; b++)
   	// {
   	// for(int c=0; c< 250; c++)
   	// product[a][b]+= A[a][c]*B[c][b];
   	// }
    // }
    
    // ofstream outfile(outputmatrix);
    // // storing the final output in the given output file
    // outfile << 144<<endl;
    // outfile << 1 << endl;
    // for(int j=0; j<144; j++)
    // {
    // 	for(int i=0; i< 1; i++)
    // 	{
    // 	outfile<< product[i][j]+ C[i][j]<< endl;
    // 	}
    // }
    // outfile.close();
  cout<<"FC1"<<endl;  
return 0;   
}

int FC23(string inputmatrix, string weightmatrix, string biasmatrix, string outputmatrix)
{
    //a is rows b is columns
    // ifstream in (inp);
    // float A[1][144];
    float* AA=(float*) malloc(144*1*sizeof(float));

    ifstream in1;
    in1.open(inputmatrix);
    if(in1.fail()){
        throw invalid_argument("Maybe 4File Does Not Exist.");
    }
    string st;
    int r1,c1;
    in1>>r1;
    in1>>c1;
        for(int j=0;j<144;j++){
    for(int i=0;i<1;i++){
            
            in1>> AA[i*144 + j];
        }
    }
    in1.close(); 

    // float B[144][144];
    float* BB=(float*) malloc(144*144*sizeof(float));

    ifstream in2;
    in2.open(weightmatrix);
    if(in2.fail()){
        throw invalid_argument("Maybe 5File Does Not Exist.");
    }
    


    for(int i=0;i<144;i++){
        for(int j=0;j<144;j++){
            getline(in2,st,',');
            float f=stof(st);
            
            BB[i*144 + j]=f;
        }
    }
    in2.close(); 

    // float C[1][144];
    float* CC=(float*) malloc(144*1*sizeof(float));

    ifstream in3;
    in3.open(biasmatrix);
    if(in3.fail()){
        throw invalid_argument("Maybe 6File Does Not Exist.");
    }
    
    for(int i=0;i<1;i++){
        for(int j=0;j<144;j++){
            getline(in3,st,',');
            float f=stof(st);
            
            CC[i*144 + j]=f;
        }
    }
    in3.close(); 
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 1, 144, 144, 1.0, AA, 144, BB, 144, 1.0, CC, 144);
// storing the final output in the given output file
    ofstream outfile(outputmatrix);
    outfile << 144<<endl;
    outfile << 1 << endl;
    
    for(int j=0; j< 144; j++)
    {
    	for(int i=0; i< 1; i++)
    	{
    	outfile<< CC[i*144 + j]<< endl;
    	}
    }

    // float product[1][144];
    // for(int a=0; a< 1; a++)
    // {
   	// for(int b=0; b< 144; b++)
   	// {
   	// product[a][b]=0;
   	// }
    // }
    // //for storing the product of the two matrices
    // for(int a=0; a< 1; a++)
    // {
   	// for(int b=0; b< 144; b++)
   	// {
   	// for(int c=0; c< 144; c++)
   	// product[a][b]+= A[a][c]*B[c][b];
   	// }
    // }
    
    // ofstream outfile(outputmatrix);
    // // storing the final output in the given output file
    // outfile << 144<<endl;
    // outfile << 1 << endl;
    // for(int j=0; j<144; j++)
    // {
    // 	for(int i=0; i< 1; i++)
    // 	{
    // 	outfile<< product[i][j]+ C[i][j]<< endl;
    // 	}
    // }
    // outfile.close();
    cout<<"FC23"<<endl; 
return 0;   
}

int FC4(string inputmatrix, string weightmatrix, string biasmatrix, string outputmatrix)
{
    //a is rows b is columns
    // ifstream in (inp);
    // float A[1][144];
    float* AA=(float*) malloc(144*1*sizeof(float));

    ifstream in1;
    in1.open(inputmatrix);
    if(in1.fail()){
        throw invalid_argument("Maybe 7File Does Not Exist.");
    }
    string st;
    int r1,c1;
    in1>>r1;
    in1>>c1;

        for(int j=0;j<144;j++){
    for(int i=0;i<1;i++){
            
            in1>>AA[i*144 + j];
        }
    }
    in1.close(); 

    // float B[144][12];
    float* BB=(float*) malloc(12*144*sizeof(float));

    ifstream in2;
    in2.open(weightmatrix);
    if(in2.fail()){
        throw invalid_argument("Maybe 9 File Does Not Exist.");
    }
    


    for(int i=0;i<144;i++){
        for(int j=0;j<12;j++){
            getline(in2,st,',');
            float f=stof(st);
            
            BB[i*12 + j]=f;
        }
    }
    in2.close(); 
    
    // float C[1][12];
    float* CC=(float*) malloc(12*1*sizeof(float));

    ifstream in3;
    in3.open(biasmatrix);
    if(in3.fail()){
        throw invalid_argument("Maybe 10 File Does Not Exist.");
    }
    
    for(int i=0;i<1;i++){
        for(int j=0;j<12;j++){
            getline(in3,st,',');
            float f=stof(st);
            
            CC[i*12 + j]=f;
        }
    }
    in3.close(); 
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 1, 12, 144, 1.0, AA, 144, BB, 12, 1.0, CC, 12);
// storing the final output in the given output file
    ofstream outfile(outputmatrix);
    outfile<< 12<< endl;
    outfile<< 1<< endl;
    for(int j=0; j< 12; j++)
    {
    	for(int i=0; i< 1; i++)
    	{
    	outfile<< CC[i*12 + j]<< endl;
    	}
    }
    // float product[1][12];
    // for(int a=0; a< 1; a++)
    // {
   	// for(int b=0; b< 12; b++)
   	// {
   	// product[a][b]=0;
   	// }
    // }
    // //for storing the product of the two matrices
    // for(int a=0; a< 1; a++)
    // {
   	// for(int b=0; b< 12; b++)
   	// {
   	// for(int c=0; c< 144; c++)
   	// product[a][b]+= A[a][c]*B[c][b];
   	// }
    // }
    
    // ofstream outfile(outputmatrix);
    // // storing the final output in the given output file
    // outfile << 12<<endl;
    // outfile << 1 << endl;
    // for(int j=0; j<12; j++)
    // {
    // 	for(int i=0; i< 1; i++)
    // 	{
    // 	outfile<< product[i][j]+ C[i][j]<< endl;
    // 	}
    // }
    // outfile.close();
    cout<<"FC4"<<endl; 
return 0;   
}
pred_t* libaudioAPI(const char* audio, pred_t* predd){
cout<<"FC"<<endl;
    FC1("inputmatrix.txt","weightmatrix1.txt","biasmatrix1.txt","outputmatrix.txt");
    relu("outputmatrix.txt", "outputmatrix2.txt");
    FC23("outputmatrix2.txt","weightmatrix2.txt","biasmatrix2.txt","outputmatrix3.txt" );
    relu("outputmatrix3.txt", "outputmatrix4.txt");
    FC23("outputmatrix4.txt","weightmatrix3.txt","biasmatrix3.txt","outputmatrix5.txt" );
    relu("outputmatrix5.txt", "outputmatrix6.txt");
    FC4("outputmatrix6.txt", "weightmatrix4.txt","biasmatrix4.txt","outputmatrix7.txt");
    softmax("outputmatrix7.txt", "outputmatrix8.txt");

    ifstream infile;
    infile.open("outputmatrix8.txt");
    
    ofstream outfile("outputvector.txt");
    if(!infile)
    cout<< "File cannot be opened."<<std::endl;	
    int length ;
    float num;
    infile>> length;
    vector<float> v;
    //storing vector
    for(int i=0; i< length; i++)
    {
    infile>> num;
    v.push_back(num);
    }
    float max1= v[0]; int i1=0;
    float max2= v[0]; int i2=0;
    float max3= v[0]; int i3=0;
    for(int i=1; i< length; i++)
    {
    if(v[i]> max1)
    {
    	max3 = max2;
    	max2 = max1;
    	max1 = v[i];
    	i3 = i2;
    	i2 = i1;
    	i1 = i;
    	
    }
    else if(v[i] < max1 && max2 < v[i])
    {
    	max3 = max2;
    	max2 = v[i];
    	i3= i2;
    	i2 = i;
    }
    else if (v[i]< max2 && max3 < v[i])
    {
    	max3 = v[i];
    	i3 = i;
    }
    }
    std::string arr[12]= {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    outfile<< max1<<endl;
    outfile<< arr[i1]<<endl;
    outfile<< max2<<endl;
    outfile<< arr[i2]<<endl;
    outfile<< max3<<endl;
    outfile<< arr[i3]<<endl;
    
    
    infile.close();
    outfile.close();
    predd[0].label = arr[i1];
    predd[0].prob = max1;
    predd[1].label = arr[i2];
    predd[1].prob = max2;
    predd[2].label = arr[i3];
    predd[2].prob = max3;
    return predd;
}
