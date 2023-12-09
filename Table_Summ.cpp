#include <iostream>
#include <string>

using namespace std;

int main(){
    int p = 10;
    for (int i=0; i<p; i++){
        for (int j=0; j<p; j++){
            cout<<i+j<<"\t";
        }
        cout<<endl;
    }

    return 0;
}