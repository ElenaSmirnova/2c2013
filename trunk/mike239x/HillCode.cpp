#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include "HillCode.h"

using namespace std;

int main() {
    string s = "REALLY SECRET MSG. ORLY?";
    cout << s << endl;
    Matrix key = Matrix(3,3);
    key.set(0,0,6); key.set(1,0,24); key.set(2,0,1);
    key.set(0,1,13); key.set(1,1,16); key.set(2,1,10);
    key.set(0,2,20); key.set(1,2,17); key.set(2,2,15);
    cout << "key made" << endl;
    string s_coded = code(s, key);
    cout << s << endl;
    cout << s_coded << endl;
    string s_maybe = decode(s_coded, key);
    cout << s_maybe << endl;
	return 0;
}
