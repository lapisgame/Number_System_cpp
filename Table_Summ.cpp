#include <iostream>
#include <string>

using namespace std;

string iz_10_v_P(double inp_znach, int new_base, int accurancy=9){
    string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    string new_znach="", new_drob="";
    int old_znach = (int) inp_znach;
    double old_drob = inp_znach - old_znach;

    while (old_znach > 0){
        new_znach = alphabet[old_znach % new_base] + new_znach;
        old_znach = old_znach / new_base;
    }


    int lencount = 0;
    while ((lencount < accurancy) and (old_drob != 0)){
        new_drob += alphabet[(int)(old_drob * new_base)];
        old_drob = (old_drob * new_base) - (int)(old_drob * new_base);
        lencount += 1;
    }

    if (new_znach == ""){
        new_znach = "0";
    }

    if (new_drob == ""){
        new_drob = "0";
    }

    return new_znach + "." + new_drob;
}

int main(){
    int p;
    cout << "P = ";
    cin >> p;

    cout << "\t\t";
    for (int i=0; i<p; i++){
        cout<<i<<"\t";
    }
    cout<<endl;
    
    cout <<"\t";
    for (int i=0; i<p; i++){
        cout<<"---------";
    }
    cout<<endl;

    for (int i=0; i<p; i++){
        cout<<i<<"\t"<<"|"<<"\t";
        for (int j=0; j<p; j++){
            cout<<iz_10_v_P(i+j, p)<<"\t";
        }
        cout<<endl;
    }

    return 0;
}