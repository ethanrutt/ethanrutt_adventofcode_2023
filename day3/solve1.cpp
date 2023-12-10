#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <set>

using namespace std;

const string NUMS = "0123456789";
const string SYMBOLS = "#$%&*+-/=@";
const set<char> SYMBOLS_SET = {'#', '$', '%', '&', '*', '+', '-', '/', '=', '@'};

pair<int, int> find_num(int start_pos, string s) {
    int start;
    int end;
    try {
        start = s.find_first_of(NUMS, start_pos);
        end = s.find_first_not_of(NUMS, start);
    } catch (const out_of_range& e) {
        return {-1, -1};
    }

    if (end == -1) {
        end = s.size();
    }

    return {start, end};
}

bool check_num(string above, string curr, string below, pair<int, int> range) {
    const int start_idx = range.first <= 0 ? range.first : range.first - 1;
    const int end_idx = range.second >= curr.size() ? range.second - 1 : range.second;
    if (!above.empty()) {
        for (int i = start_idx; i <= end_idx; i++) {
            if (SYMBOLS_SET.find(above[i]) != SYMBOLS_SET.end()) {
                return true;
            }
        }
    }

    if (!below.empty()) {
        for (int i = start_idx; i <= end_idx; i++) {
            if (SYMBOLS_SET.find(below[i]) != SYMBOLS_SET.end()) {
                return true;
            }
        }
    }

    if (
        SYMBOLS_SET.find(curr[start_idx]) != SYMBOLS_SET.end() ||
        SYMBOLS_SET.find(curr[end_idx]) != SYMBOLS_SET.end()
    ) {
        return true;
    }

    return false;
}

void check_line(string above, string curr, string below, int& sum) {
    int idx = 0;
    pair<int, int> range = find_num(idx, curr);

    while (range.first != -1) {
        idx = range.second;
        string num = curr.substr(range.first, range.second - range.first);
        if (check_num(above, curr, below, range)) {
            sum += atoi(num.c_str());
        }
        range = find_num(idx, curr);
    }

}

int main() {
    vector<string> input(141);
    unsigned int i = 0;
    int sum = 0;

    while (getline(cin, input[i++]));

    for (i = 0; i < input.size(); i++) {
        if (i == 0) {
            check_line(string(), input[i], input[i+1], sum);
        }
        else if (i == input.size() - 1) {
            check_line(input[i-1], input[i], string(), sum);
        }
        else {
            check_line(input[i-1], input[i], input[i+1], sum);
        }
    }

    cout << "sum: " << sum << endl;

    return 0;
}

