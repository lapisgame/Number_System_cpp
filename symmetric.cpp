#include <iostream>
#include <string>
#include "math.h"

using namespace std;

string summ(string inp_znach1, string inp_znach2, int base){
    int pointer1, pointer2, pointer_drob1, pointer_drob2, carry;
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

    new_drob = "";

    // Поразрядное суммирование 
    carry = 0;
    while (pointer_drob2 >= 0){
        int summ = alphabet.find(drob1[pointer_drob1]) + alphabet.find(drob2[pointer_drob2]) + carry;
        char addition_bit = alphabet[summ % base];
        new_drob += addition_bit;
        carry = summ / base;

        pointer_drob1--;
        pointer_drob2--;
    }
    
    // Бежим с конца в перед пока не закончится меньшее число, 
    // в процессе складываем значения и пишем их по модулю
    new_znach = "";
    carry = 0;
    while (pointer2 >= 0){
        int summ = alphabet.find(znach1[pointer1]) + alphabet.find(znach2[pointer2]) + carry;
        char addition_bit = alphabet[summ % base];
        new_znach += addition_bit;
        carry = summ / base;

        pointer1--;
        pointer2--;
    }

    // Добегаем остальные позиции в числе
    while (pointer1 >= 0){
        int summ = alphabet.find(znach1[pointer1]) + carry;
        char addition_bit = alphabet[summ % base];
        new_znach += addition_bit;
        carry = summ / base;

        pointer1--;
    }

    // Записываем в конец остаток суммы
    if (carry != 0){
        new_znach = new_znach + to_string(carry);
    }

    // Переворачиваем результат
    string new_znach_rev = "";
    string new_drob_rev = "";

    for (int i=new_znach.size()-1; i>=0; i--){
        char ad = new_znach[i];
        new_znach_rev += ad;
    }

    for (int i=new_drob.size()-1; i>=0; i--){
        char ad = new_drob[i];
        new_drob_rev += ad;
    }

    return new_znach_rev + "." + new_drob_rev;
}


string double_to_symmetric(double decimal_num){
    int decimal_znach, remainder, precision, digit;
    double decimal_drob;
    string result_znach, result_drob, res;

    int znak=0;

    if (decimal_num < 0){
        znak = 1;
        decimal_num = -decimal_num;
    }

    decimal_znach = (int) decimal_num;
    decimal_drob = decimal_num - decimal_znach; 


    result_znach = "";
    while (decimal_znach > 0){
        remainder = decimal_znach % 3;
        result_znach = to_string(remainder) + result_znach;
        decimal_znach = decimal_znach / 3;
    }

    result_drob = "";
    if (decimal_drob != 0){
        precision = to_string(decimal_drob).size() * 4;

        while ((decimal_drob != 0) and (result_drob.size() < precision)){
            decimal_drob = decimal_drob * 3;
            digit = (int) decimal_drob;
            decimal_drob = decimal_drob - digit;

            result_drob = result_drob + to_string(digit);
        }
    }

    string to_plus = "00" + result_znach + "." + result_drob;
    string to_plus1 = string(result_znach.size() + 2, '1') + '.' + string(result_drob.size(), '1');
    string to_min = summ(to_plus, to_plus1, 3);

    res = "";

    for (int i=0; i<to_min.size(); i++){
        if (to_min[i] == '0'){
            res += '-';
        }
        if (to_min[i] == '1'){
            res += '0';
        }
        if (to_min[i] == '2'){
            res += '+';
        }
        if (to_min[i] == '.'){
            res += '.';
        }
    }

    if (znak){
        string res_copy = "";
        for (int i=0; i<res.size(); i++){
            if (res[i] == '+'){
                res_copy += '-';
            }
            if (res[i] == '-'){
                res_copy += '+';
            }
            if (res[i] == '0'){
                res_copy += '0';
            }
            if (res[i] == '.'){
                res_copy += '.';
            }
        }


        res = res_copy;
    }

    return res;
}

double symmetric_to_double(string symmetric_num){
    double res = 0;
    string znach, drob;

    znach = symmetric_num.substr(0, symmetric_num.find('.'));
    drob = symmetric_num.substr(symmetric_num.find('.') + 1, symmetric_num.size()-znach.size());

    for (int i=0; i<znach.size(); i++){
        if (znach[i] == '+'){
            res = res + pow(3, znach.size()-i-1);
        }
        if (znach[i] == '-'){
            res = res - pow(3, znach.size()-i-1);
        }
    }

    for (int i=0; i<drob.size(); i++){
        if (drob[i] == '+'){
            res = res + pow(3, -i-1);
        }
        if (drob[i] == '-'){
            res = res - pow(3, -i-1);
        }
    }

    return res;
}

int main(){
    cout << double_to_symmetric(7) << endl;
    cout << symmetric_to_double(double_to_symmetric(7)) << endl;
    cout << double_to_symmetric(-5.25) << endl;
    cout << symmetric_to_double(double_to_symmetric(-5.25)) << endl;

    return 0;
}