#include <iostream>
#include <vector>

using namespace std;


int main() {
    vector<string> input(1001);
    unsigned int i = 0;

    while (getline(cin, input[i++]));

    /**
     *
     * find number with find_first_of("0123456789")
     * do find_first_not_of("0123456789") so that I can isolate the number with start and end indexes
     * get first, last index of number, as well as line number
     *
     * check all elements around the number to determine if it's part of schematic
     * need to handle corner checks
     * if part of schematic -> add to sum
     *
     */





    return 0;

}
