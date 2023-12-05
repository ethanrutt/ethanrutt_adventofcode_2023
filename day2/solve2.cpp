#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

const int MAX_NUM_RED_CUBES = 12;
const int MAX_NUM_GREEN_CUBES = 13;
const int MAX_NUM_BLUE_CUBES = 14;


// https://gist.github.com/tcmug/9712f9192571c5fe65c362e6e86266f8
template <typename T>
std::vector <T> split_string(T string, T delim) {
    std::vector <T> result;
    size_t from = 0, to = 0;
    while (T::npos != (to = string.find(delim, from))) {
        result.push_back(string.substr(from, to - from));
        from = to + delim.length();
    }
    result.push_back(string.substr(from, to));
    return result;
}

// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
const char* ws = " \t\n\r\f\v";

// trim from end of string (right)
std::string& rtrim(std::string& s, const char* t = ws)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
std::string& ltrim(std::string& s, const char* t = ws)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (right then left)
std::string& trim(std::string& s, const char* t = ws)
{
    return ltrim(rtrim(s, t), t);
}

int get_gamenum(std::string s) {
    std::string trimmed = s.substr(s.find(' '), s.find(':'));
    return atoi(trimmed.c_str());
}

std::pair<std::string, int> get_num_color(std::string s) {
    std::istringstream ss(s);
    std::string color;
    int num;

    ss >> num >> color;

    std::pair<std::string, int> res = {color, num};

    return res;
}


int main() {
    std::vector<std::string> games(101);
    unsigned int i = 0;

    while (getline(std::cin, games[i++]));
    int sum;
    std::unordered_map<std::string, int> cube_count;

    // prevent seg fault from getline and
    // prevent seg fault from later parsing on last empty element
    games.erase(games.end() - 1);

    for (std::string s : games) {
        int gamenum = get_gamenum(s);
        bool game_possible = true;
        std::string curr_game_trimmed = s.substr(s.find(':') + 2, s.size());

        std::vector<std::string> subsets = split_string<std::string>(curr_game_trimmed, ";");

        cube_count["red"] = 0;
        cube_count["green"] = 0;
        cube_count["blue"] = 0;

        for (std::string subset : subsets) {
            std::vector<std::string> cube_nums = split_string<std::string>(trim(subset), ",");

            for (std::string cube_num : cube_nums) {
                std::pair<std::string, int> p = get_num_color(trim(cube_num));

                if (p.first == "red") {
                    cube_count["red"] = std::max(cube_count["red"], p.second);
                }
                else if (p.first == "green") {
                    cube_count["green"] = std::max(cube_count["green"], p.second);
                }
                else if (p.first == "blue") {
                    cube_count["blue"] = std::max(cube_count["blue"], p.second);
                }
            }
        }

        sum += cube_count["red"] * cube_count["green"] * cube_count["blue"];
    }

    std::cout << "sum: " << sum << std::endl;

    return 0;
}
