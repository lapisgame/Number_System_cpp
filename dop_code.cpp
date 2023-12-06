#include <iostream>
#include <string>
#include "math.h"

using namespace std;

string int_to_dop_code(int x){
    string y, y_inv, z;
    int point, bit;
    
    if (x >= 0){
        cout << "Число должно быть отрицательным" << endl;
        return "";
    }

    x = abs(x);
    y = "";

    while (x > 0){
        y = to_string(x % 2) + y;
        x = x / 2;
    }

    if (y.size() < 8){
        y = string(8 - y.size (), '0') + y;
    }
    else{
        if (y.size() < 16){
            y = string(16 - y.size (), '0') + y;
        }
        else{
            if (y.size() < 32) {
                y = string(32 - y.size (), '0') + y;
            }
            else{
                if (y.size() < 64) {
                    y = string(64 - y.size (), '0') + y;
                }
            }
        }
    }

    y_inv = "";
    for (int i=0; i<y.size(); i++){
        if (y[i] == '0'){
            y_inv = y_inv + '1';
        }
        else{
            y_inv = y_inv + '0';
        }
    }

    z = y_inv;
    point = z.size() - 1;
    bit = 1;

    while ((point>=0) and (bit>0)){
        if (z[point] == '0'){
            z[point] = '1';
            bit--;
        }
        else{
            z[point] = '0';
        }
    }

    return z;
}



int dop_code_to_int(string z){
    string y, y_inv;
    int x, point, bit, digit;

    point = z.size() - 1;
    bit = 1;

    while ((point>=0) and (bit>0)){
        if (z[point] == '1'){
            z[point] = '0';
            bit--;
        }
        else{
            z[point] = '1';
        }
    }

    y = "";
    y_inv = z;
    for (int i=0; i<y_inv.size(); i++){
        if (y_inv[i] == '0'){
            y = y + '1';
        }
        else{
            y = y + '0';
        }
    }

    x = 0;
    for (int i=y.size() - 1, count=0; i>=0; i--, count++){
        digit = y[i] - '0';
        x = x + (pow(2, count) * digit);
    }
    x = -x;

    return x;
}



int main(){

    cout << int_to_dop_code(-17) << endl;
    cout << dop_code_to_int(int_to_dop_code(-17)) << endl;

    return 0;
}