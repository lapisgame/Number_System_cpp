#include <iostream>
#include <string>

using namespace std;

string RremoveZero(string str) 
{ 
    if (str.size()>1){
        int i = str.size()-1; 
        while (str[i] == '0') 
            i--; 

        str.erase(i+1, str.size()); 
    }

    return str; 
}

string LremoveZero(string str) 
{ 
    if (str.size()>1){
        int i = 0; 
        while (str[i] == '0') 
            i++; 

        str.erase(0, i); 
    }

    return str; 
} 

string umnogenie(string inp_znach1, string inp_znach2, int base){
    int pointer1, pointer2, pointer_drob1, pointer_drob2, carry, borrow, shift_dot, result_digit;
    string znach1, znach2, drob1, drob2, new_znach, new_drob, a, b;
    
    string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i=0; i<inp_znach1.size(); i++){
        if ((inp_znach1[i] != '.') and (alphabet.find(inp_znach1[i]) >= base)){
            cout << "ERROR INPUT VALUE IN FIRST DIGIT" << endl;
            return "";
        }
    }

    for (int i=0; i<inp_znach2.size(); i++){
        if ((inp_znach2[i] != '.') and (alphabet.find(inp_znach2[i]) >= base)){
            cout << "ERROR INPUT VALUE IN SECOND DIGIT" << endl;
            return "";
        }
    }

    if (inp_znach1.find('.') < inp_znach2.find('.')){
        string temp = inp_znach1;
        inp_znach1 = inp_znach2;
        inp_znach2 = temp;
    }

    znach1 = inp_znach1.substr(0, inp_znach1.find('.'));
    znach2 = inp_znach2.substr(0, inp_znach2.find('.'));
    
    drob1 = inp_znach1.substr(inp_znach1.find('.') + 1, inp_znach1.size() - znach1.size());
    drob2 = inp_znach2.substr(inp_znach2.find('.') + 1, inp_znach2.size() - znach2.size());

    // Незначащие нули в конце числа для одинакового кол-ва разрядов
    if (drob1.size() > drob2.size()){
        drob2 = drob2 + string(drob1.size() - drob2.size(), '0');
    }
    else{
        if (drob1.size() < drob2.size()){
            drob1 = drob1 + string(drob2.size() - drob1.size(), '0');
        }
    } 

    shift_dot = drob1.size() + drob2.size();

    a = znach1 + drob1;
    b = znach2 + drob2;

    new_znach = "";

    carry = 0;

    for (int i=0; i<(a.size() + b.size()); i++){
        result_digit = carry;
        for (int j=0; j<a.size(); j++){
            if ((i - j >= 0) and (i - j < b.size())){
                result_digit = result_digit + (alphabet.find(a[a.size() - 1 - j]) * alphabet.find(b[b.size() - 1 - (i - j)]));
            }
        }

        carry = result_digit / base;
        result_digit = result_digit % base;

        new_znach = alphabet[result_digit] + new_znach;
    }

    new_znach = LremoveZero(new_znach);

    new_znach = new_znach.substr(0,new_znach.size() - shift_dot) + "." + new_znach.substr(new_znach.size() - shift_dot, new_znach.size());

    new_znach = RremoveZero(new_znach);

    return new_znach;
}

int main(){
    cout << umnogenie("112.356", "13.35", 8) << endl;

    return 0;
}