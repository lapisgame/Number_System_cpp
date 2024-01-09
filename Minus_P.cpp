#include <iostream>
#include <string>

using namespace std;

string RremoveZero(string str) 
{ 
    int i = str.size()-1; 
    while (str[i] == '0') 
        i--; 

    str.erase(i+1, str.size()); 
  
    return str; 
} 

string LremoveZero(string str) 
{ 
    int i = 0; 
    while (str[i] == '0') 
        i++; 

    str.erase(0, i); 
  
    return str; 
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

    if (inp_znach1.find('.') < inp_znach2.find('.')){
        string temp = inp_znach1;
        inp_znach1 = inp_znach2;
        inp_znach2 = temp;
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



int main(){
    cout << minuss("42", "36", 8) << endl;

    return 0;
}