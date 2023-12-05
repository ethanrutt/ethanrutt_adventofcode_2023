#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// map of number and amount of characters in word
const unordered_map<string, int> nums_sizes = {
    {"zero", 4},
    {"one", 3},
    {"two", 3},
    {"three", 5},
    {"four", 4},
    {"five", 4},
    {"six", 3},
    {"seven", 5},
    {"eight", 5},
    {"nine", 4}
};

const unordered_map<string, string> nums_nums = {
    {"zero", "0"},
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};

void parse_nums(string& s) {
    int first_num = INT32_MAX;
    string first_string = string();
    for (auto kv : nums_nums) {
        int idx = s.find(kv.first);
        if (idx < first_num && idx > -1) {
            first_num = idx;
            first_string = kv.first;
        }
    }

    if (!first_string.empty()) {
        s = s.substr(0, first_num) + nums_nums.at(first_string) + s.substr(first_num, s.size());
    }

    int last_num = 0;
    string last_string = string();
    for (auto kv : nums_nums) {
        int idx = s.rfind(kv.first);
        if (idx > last_num && idx > -1) {
            last_num = idx;
            last_string = kv.first;
        }
    }

    if (!last_string.empty()) {
        s = s.substr(0, last_num) + nums_nums.at(last_string) + s.substr(last_num, s.size());
    }
}

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
        parse_nums(i);
        sum += get_first_num(i) * 10;
        sum += get_last_num(i);
    }

    cout << "sum = " << sum << endl;

    return 0;
}

