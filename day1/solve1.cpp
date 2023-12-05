#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int is_num(const char& c) {
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return -1;
    }
}

int get_first_num(const string& s) {
    for (char c : s) {
        int num = is_num(c);
        if (num != -1) {
            return num;
        }
    }
    return 0;
}

int get_last_num(string s) {
    std::reverse(s.begin(), s.end());

    for (char c: s) {
        int num = is_num(c);
        if (num != -1) {
            return num;
        }
    }
    return 0;
}

int main() {
    vector<string> input(1001);
    unsigned int i = 0;

    while (getline(cin, input[i++]));

    int sum = 0;

    for (auto i : input) {
        sum += get_first_num(i) * 10;
        sum += get_last_num(i);
    }

    cout << "sum = " << sum << endl;

    return 0;
}
