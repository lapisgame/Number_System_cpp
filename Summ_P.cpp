#include <iostream>
#include <string>

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



int main(){
    cout << summ("1.3", "13.35", 6) << endl;

    return 0;
}