#include <iostream>
#include <string>
#include "math.h"

using namespace std;

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

bool sravnenie(string inp_znach1, string inp_znach2, int base){
    double z1, z2;
    z1 = iz_P_v_10(inp_znach1, base);
    z2 = iz_P_v_10(inp_znach2, base);

    return z1 > z2;
}

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

string minuss(string inp_znach1, string inp_znach2, int base){
    int pointer1, pointer2, pointer_drob1, pointer_drob2, carry, borrow;
    string znach1, znach2, drob1, drob2, new_znach, new_drob;
    
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

    znach1 = inp_znach1.substr(0, inp_znach1.find('.'));
    znach2 = inp_znach2.substr(0, inp_znach2.find('.'));
    
    drob1 = inp_znach1.substr(inp_znach1.find('.') + 1, inp_znach1.size() - znach1.size());
    drob2 = inp_znach2.substr(inp_znach2.find('.') + 1, inp_znach2.size() - znach2.size());


    // Указатели на конец числа
    pointer1 = znach1.size() - 1;
    pointer2 = znach2.size() - 1;


    // Незначащие нули в начале числа для одинакового кол-ва разрядов
    if (znach1.size() > znach2.size()){
        znach2 = string(znach1.size() - znach2.size(), '0') + znach2;
    }
    else{
        if (znach1.size() < znach2.size()){
            znach1 = string(znach2.size() - znach1.size(), '0') + znach1;
        }
    } 

    // Незначащие нули в конце числа для одинакового кол-ва разрядов
    if (drob1.size() > drob2.size()){
        drob2 = drob2 + string(drob1.size() - drob2.size(), '0');
    }
    else{
        if (drob1.size() < drob2.size()){
            drob1 = drob1 + string(drob2.size() - drob1.size(), '0');
        }
    } 

    pointer_drob1 = drob1.size() - 1;
    pointer_drob2 = drob2.size() - 1;

    borrow = 0;
    new_drob = "";

    for (int i=drob1.size() - 1; i>=0; i--){
        int digit1 = alphabet.find(drob1[i]);
        int digit2 = alphabet.find(drob2[i]);

        // Учитываем заём
        digit1 = digit1 - borrow;

        // Если digit1 < digit2, занимаем у следующего разряда
        if (digit1 < digit2){
            digit1 += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        // Вычисляем текущий разряд результата
        int result_digit = digit1 - digit2;
        new_drob = alphabet[result_digit] + new_drob;
    }

    // Удаляем замыкающие нули
    new_drob = RremoveZero(new_drob);

    if (new_drob == ""){
        new_drob = "0";
    }


    // Вычитание целой части
    new_znach = "";

    for (int i=znach1.size() - 1; i>=0; i--){
        int digit1 = alphabet.find(znach1[i]);
        int digit2 = alphabet.find(znach2[i]);

        // Учитываем заём
        digit1 = digit1 - borrow;

        // Если digit1 < digit2, занимаем у следующего разряда
        if (digit1 < digit2){
            digit1 += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        // Вычисляем текущий разряд результата
        int result_digit = digit1 - digit2;
        new_znach = alphabet[result_digit] + new_znach;
    }

    // Удаляем ведущие нули
    new_znach = LremoveZero(new_znach);

    if (new_znach == ""){
        new_znach = "0";
    }

    return new_znach + "." + new_drob;
}

void split(string all, string &znach, string &drob){
    znach = all.substr(0, all.find('.'));
    drob = all.substr(all.find('.') + 1, all.size() - znach.size());
}

string delenie(string inp_znach1, string inp_znach2, int base){
    int pointer1, pointer2, pointer_drob1, pointer_drob2, carry, borrow;
    string znach1, znach2, drob1, drob2, new_znach, new_drob;
    
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

    new_znach = "";
    new_drob = "";

    int count = 0;

    int count_znach = 0;
    while (sravnenie(inp_znach1, inp_znach2, base)){
        inp_znach1 = minuss(inp_znach1, inp_znach2, base);
        count_znach++;
    }

    // Количество знаков после запятой
    int max_acc = 9;

    while (count < max_acc){
        int count_drob = 0;
        
        inp_znach1 = umnogenie(inp_znach1, "10.0", base);

        while (sravnenie(inp_znach1, inp_znach2, base)){
            inp_znach1 = minuss(inp_znach1, inp_znach2, base);
            count_drob++;
        }

        new_drob += alphabet[count_drob];
        count++;
    }

    while (count_znach>0){
        new_znach = alphabet[count_znach % base] + new_znach;
        count_znach = count_znach / base;
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
    cout << delenie("2.3", "10", 5) << endl;

    return 0;
}