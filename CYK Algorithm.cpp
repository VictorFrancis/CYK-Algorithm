//Assignment 2
//Name: Victor Francis Halder
//ID: 1610026

#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

const int maximum = 100;

string grammar[maximum][maximum];  //to store entered grammar
string dynamic[maximum];
int production,numberOfProduction;       //numberOfProduction-> number of productions

inline string cancatenation(string x, string y){   //concatenates unique non-terminals

    int i;
    string r=x;
    for(i=0; i<y.length(); i++){
        if(r.find(y[i]) > r.length()){
            r=r+y[i];
        }

    }
    return r;
}

inline void breakGrammar(string x){    //seperates right hand side of entered grammar

    int i;
    production=0;
    while(x.length()){

        i=x.find("|");
        if(i>x.length()){
            dynamic[production++] = x;
            x="";
        }
        else{
            dynamic[production++] = x.substr(0,i);
            x=x.substr(i+1,x.length());
        }
    }
}

inline int leftChomsky(string x){   //checks if LHS of entered grammar is in CNF

    if(x.length()==1 && x[0]>='A' && x[0]<='Z'){
        return 1;
    }

    return 0;
}

inline int RightChomsky(string y){   //checks if RHS of grammar is in CNF

    if(y.length() == 1 && y[0]>='a' && y[0] <='z'){
        return 1;
    }

    else if(y.length()==2 && y[0]>='A' && y[0]<='Z' && y[1]>='A' && y[1]<='Z' ){
        return 1;
    }

    return 0;
}

inline string searchProduction(string production){ //returns a concatenated string of variables which can produce string production

    int j,k;
    string r="";

    for(j=0; j<numberOfProduction; j++){
        k=1;

        while(grammar[j][k] != ""){
            if(grammar[j][k] == production){
                r=cancatenation(r,grammar[j][0]);
            }
            k++;
        }
    }
    return r;
}

inline string combination(string x, string y){  //creates every combination of variables from x and y

    int i,j;
    string prim=x,ret="";

    for(i=0; i<x.length(); i++){
        for(j=0; j<y.length(); j++){
            prim="";
            prim=prim+x[i]+y[j];
            ret=ret+searchProduction(prim);     //searches if the generated productions can be created or not
        }
    }

    return ret;
}

int main(){

    int i,ptr,j,l,k;
    string x,str,re,pro,start,stry;
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");
    string line;


    if(inFile.is_open()){
        while(inFile>>line){
        cin>>start;
        cin>>numberOfProduction;
        cin>>stry;
        }
    }
    else{
        cout<<"Unable to open file";
        return 0;
    }

    inFile.close();



    //cout<<"Enter the start Variable ";
    //cout<<endl;

    //cin >> start;

    //cout<<"Number of productions ";
    //cout<<endl;

    //cin >> numberOfProduction;

    for(i=0; i<numberOfProduction; i++){

        cin >> x;

        ptr=x.find("->");
        grammar[i][0] = x.substr(0,ptr);

        if(leftChomsky(grammar[i][0]) == 0){
            cout<<"Grammar not in Chomsky Form";
            cout<<endl;

            break;
        }

        x = x.substr(ptr+2, x.length());
        breakGrammar(x);

        for(j=0; j<production; j++){
            grammar[i][j+1]=dynamic[j];

            if(RightChomsky(dynamic[j])==0){

                cout<<"Grammar not in Chomsky Form";
                cout<<endl;

                break;
            }
        }
    }

    string matrix[maximum][maximum];

    //cout<<"Enter string to be checked : ";
    //cout<<endl;

    //cin>>stry;


    for(i=0; i<str.length(); i++){       //Assigns values to principal diagonal of matrix

        re="";
        stry = "";
        stry=stry+stry[i];

        for(j=0; j<numberOfProduction; j++){
            k=1;

            while(grammar[j][k] != ""){
                if(grammar[j][k] == str){
                    re=cancatenation(re,grammar[j][0]);
                }

                k++;
            }
        }
        matrix[i][i]=re;
    }

    for(k=1; k<str.length(); k++){       //Assigns values to upper half of the matrix
        for(j=k; j<str.length(); j++){
            re="";

            for(l=j-k; l<j; l++){
                pro = combination(matrix[j-k][l],matrix[l+1][j]);
                re = cancatenation(re,pro);
            }
            matrix[j-k][j] = re;
        }
    }

    for(i=0; i<str.length(); i++){   //Prints the matrix
        k=0;
        l=str.length()-i-1;

        for(j=l; j<str.length(); j++){
            cout<<setw(5)<<matrix[k++][j]<<" ";
        }

        cout<<endl;
    }

    int f=0;

    for(i=0; i<start.length(); i++){
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length()){   //Checks if last element of first row contains a Start variable
            if(outFile.is_open()){
                outFile<<"String can be generated";
            }
            else{
                cout << "Unable to open file";
            }
        }

        else{
            if(outFile.is_open()){
                outFile<<"String cannot be generated";
            }
            else{
                cout << "Unable to open file";
            }
        }

    }
    outFile.close();
    return 0;
}



//Reference: Let's Code
