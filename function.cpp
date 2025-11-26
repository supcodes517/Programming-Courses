#include <iostream>
#include <string>
using namespace std;
//definition of functions
int larger(int first, int second){
    if(first > second){
        return first;
    }else{
        return second;
    }
}

void greet(string name){
    if(name != ""){
        cout << "Hello, " << name << "!" << endl;
    }else{
        cout << "Hello, Guest!" << endl;
    }
}

double larger(double first, double second){
    if(first > second){
        return first;
    }else{
        return second;
    }
}

void pattern(int size){
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << "* ";
        }
        cout<<endl;
    }
    
}

//declaration of functions
int larger(int first, int second);
double larger(double first, double second);
void greet(string name);
void pattern(int size);

int main(){
    pattern(3);
    pattern(4);
    pattern(5);
    
    return 0;
}

