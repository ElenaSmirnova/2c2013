#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include "matrix.h"

using namespace std;


int modulus_(int val, int mod) {
    int v = val;
    while (v<0) {
        v+=mod;
    }
    v %= mod;
    return v;
}

Matrix mod29( Matrix m ) {
    Matrix result = m;
    int c = result.getCellsNum();
    for (int i = 0; i < c; i++) {
        result.set(0,i,(double)modulus_((int)result.get(i),29));
    }
    return result;
}

int inverse(int i, int mod) {
    for (int inv = 0; inv < mod; inv++) {
        if (i * inv % mod == 1) {
            return inv;
        }
    }
    return 0;
}

char charByCode(double c) {
    if (c == 26) {
        return ' ';
    } else if (c == 27) {
        return '.';
    } else if (c == 28) {
        return '?';
    } else {
        char ch = (char)c;
        return ch + 'A';
    }
}

double codeByChar(char c) {
    if (c == ' ') {
        return 26;
    } else if (c == '.') {
        return 27;
    } else if (c == '?') {
        return 28;
    }
    if ((c >= 'A') * (c <= 'Z')) {
        return (c - 'A');
    }
    if ((c >= 'a') * (c <= 'a')) {
        return (c - 'a');
    }
    return 26;
}

char* code_ (char* arr, Matrix key) {
    int msgSize = key.getWidth();
    Matrix msg = Matrix(msgSize, 1);
    for (int i = 0; i < msgSize; i++) {
        msg.set(0, i, codeByChar(arr[i]));
    }
    Matrix cipher = key.multiply(msg);
    cipher = mod29(cipher);
    char* result = new char[msgSize];
    return result;
}

string code (string msg, Matrix key)  {
    int m = key.getWidth();
    while (msg.length()%m!=0) {
        string msg1 = msg + " ";
    }
    int l = msg.length();
    int cnt = 0;
    string result = "";
    for (int i = 0; i < l/m; i++) {
        char * to_code = new char[m];
        for (int j = 0; j < m; j++) {
            to_code[j+cnt] = msg[j+cnt];
        }
        cnt+=m;
        char * got = code_(to_code, key);
        for (int j = 0; j < m; j++) {
            result += got[j];
        }
    }
    return result;
}
string decode (string msg, Matrix key)  {
    Matrix back_key = key.adjugate();
    int detInv = inverse(key.determinant(),29);
    for (int x = 0; x < back_key.getWidth(); x++) {
        for (int y = 0; y < back_key.getHeight(); y++) {
            back_key.set(x,y, detInv*back_key.get(x,y));
        }
    }
    back_key = mod29(back_key);
    return code (msg, back_key);
}
