#include<iostream>
#include<string>
using namespace std;

int main () {
	cout << "Enter even number: ";
	int n = 0;
	cin >> n;
	if (n - n / 2 * 2 == 1) {
		cout << "This number is odd.";
	} else {
		string s = "";
		for (int i = 0; i < n; i++) {
			if (i < n / 2) {
				s += "(";
			} else {
				s += ")";
			}
		}
		cout << s + "\n";
		for (int j = 1; j > 0; ++j) {
			string a = "N";
			for (int i = n - 1, depth = 0; i >= 0; --i) {
				if (s[i] == '(') {
					--depth;
				} else {
					++depth;
				}
				if (s[i] == '(' && depth > 0) {
					--depth;
					int open = (n - i - 1 - depth) / 2;
					int close = n - i - 1 - open;
					s = s.substr(0,i) + ')' + string (open, '(') + string (close, ')');
					a = s;
					break;
				}
			}
			if (a[0] == 'N') {
				break;
			}
			cout << s + "\n";
		}
	}
	cin >> n;
	return 0;
}