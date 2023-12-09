#include <iostream>
#include <string>
#include "math.h"

using namespace std;

//^ Переводит inp_znach из base-чной в 10-чную систему счисления
double iz_P_v_10(string inp_znach, int base){
    string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i=0; i<inp_znach.size(); i++){
        if ((inp_znach[i] != '.') and (alphabet.find(inp_znach[i]) >= base)){
            cout << "ERROR INPUT VALUE" << endl;
            return 0;
        }
    }

    double new_znach = 0;

    string znach, drob;

    znach = inp_znach.substr(0, inp_znach.find('.'));
    drob = inp_znach.substr(inp_znach.find('.') + 1, inp_znach.size() - znach.size());

    
    for (int i=0, count=0; i<znach.size(); i++, count++){
        new_znach = new_znach + alphabet.find(znach[i]) * pow(base, znach.size()-i-1);
    }

    for (int i=0, count=-1; i<drob.size(); i++, count--){
        new_znach = new_znach + alphabet.find(drob[i]) * pow(base, count);
    }

    return new_znach;
}


//^ Переводит inp_znach из 10-чной в new_base-чную 
//^ с точностью после запятой в accurancy знаков
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

    if (new_drob == ""){
        new_drob = "0";
    }

    return new_znach + "." + new_drob;
}


int main(){
    cout<<iz_P_v_10("13467.6", 8)<<endl;
    cout<<iz_10_v_P(iz_P_v_10("13467.6", 8), 16)<<endl;

    return 0;
}