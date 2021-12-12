#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;

typedef vector<string> input_t;
typedef vector<input_t> inputs_t;
typedef vector<string> output_t;
typedef vector<output_t> outputs_t;
typedef vector<string> digits_t;

#define INPUT_FILE "inputs/day8.dat"


void parse_inputs(inputs_t& input, outputs_t& output)
{
    std::ifstream file(INPUT_FILE);
    string line, inputs_string, outputs_string, signal;
    vector<string> signals;

    while (std::getline(file, line)) {
        std::stringstream line_ss(line);

        std::getline(line_ss, inputs_string, '|');
        std::getline(line_ss, outputs_string, '|');

        std::stringstream inputs_ss(inputs_string), outputs_ss(outputs_string);

        signals.clear();
        while (std::getline(inputs_ss, signal, ' ')) {
            signals.push_back(signal);
        }
        input.push_back(signals);

        signals.clear();
        std::getline(outputs_ss, signal, ' ');
        while (std::getline(outputs_ss, signal, ' ')) {
            signals.push_back(signal);
        }
        output.push_back(signals);
    }

    return;
}


bool isUnique(const string& signal)
{
    size_t size = signal.size();
    return (size == 2 || size == 3 || size == 4 || size == 7);
}


int part_1(outputs_t& output)
{
    int count = 0;
    for (const auto& line : output) {
        for (const auto& signal : line) {
            if (isUnique(signal)) { count++; }
        }
    }

    return count;
}


bool isSubstring(string& substr, string& str) 
{
    for  (auto chr : substr) {
        size_t found = str.find(chr);        
        if (found == string::npos) {
            return false;
        }
    }    
    return true;
}


bool found_all(vector<bool>& digits_found)
{
    bool res = true;
    for (auto digit : digits_found) {
        if (!digit) {
            return false;
        }
    }
    return true;
}


void find_digits(input_t& input, digits_t& digits, bool disp=false) 
{
    vector<bool> dgts_found(10, false);
    int iter = 0;

    while (!found_all(dgts_found)) {
        if (iter++ == 5)
            exit(-1);

        for (int i = 0; i < input.size(); i++) {
            string& signal = input[i];
            std::sort(signal.begin(), signal.end());

            // find 6, 9, 0
            if (dgts_found[4] && dgts_found[7] &&
                (!dgts_found[6] || !dgts_found[9] || !dgts_found[0])
                ) {
                if (signal.size() == 6) {
                    if (!isSubstring(digits[7], signal)) {
                        digits[6] = signal;
                        dgts_found[6] = true;
                    } else if (isSubstring(digits[4], signal)) {
                        digits[9] = signal;
                        dgts_found[9] = true;
                    } else {
                        digits[0] = signal;
                        dgts_found[0] = true;
                    }

                } 
            }

            // find 5
            if (dgts_found[6] && !dgts_found[5]) {
                if (signal.size() == 5) {
                    if (isSubstring(signal, digits[6])) {
                        digits[5] = signal;
                        dgts_found[5] = true;
                    }
                }
            }

            // find 3 and 2
            if (dgts_found[9] && dgts_found[5]) {
                if (signal.size() == 5) {
                    if (signal == digits[5])
                        continue; 
                    
                    if (isSubstring(signal, digits[9]) && !dgts_found[3]) {
                        digits[3] = signal;
                        dgts_found[3] = true;
                    } else if (!dgts_found[2]) {
                        digits[2] = signal;
                        dgts_found[2] = true;
                    }
                }
            }

            // find the unique digits (1,4,7,8)
            if (!dgts_found[1] || !dgts_found[4] || !dgts_found[7] || !dgts_found[8]) {
                if (signal.size() == 2) {
                    digits[1] = signal;
                    dgts_found[1] = true;
                } else if (signal.size() == 3) {
                    digits[7] = signal;
                    dgts_found[7] = true;
                } else if (signal.size() == 4) {
                    digits[4] = signal;
                    dgts_found[4] = true;
                } else if (signal.size() == 7) {
                    digits[8] = signal;
                    dgts_found[8] = true;
                }
            }
        }
    }
}


int part_2(inputs_t input, outputs_t& output)
{
    int digit_pos;
    vector<int> output_nums;
    int num;
    digits_t digits(10);

    for (int i = 0; i < output.size(); i++) {
        auto& line_in = input[i];
        auto& line_out = output[i];

        find_digits(line_in, digits);

        digit_pos = 1000;
        num = 0;
        for (string signal : line_out) {
            std::sort(signal.begin(), signal.end());
            digits_t::iterator it = std::find(digits.begin(), digits.end(), signal);
            int index = it - digits.begin();

            num += index * digit_pos;
            digit_pos /= 10;
        }
        output_nums.push_back(num);
    }

    int sum = 0;
    for (const auto& out : output_nums) {
        sum += out;
    }
    return sum;
}

int main() 
{
    inputs_t input;
    outputs_t output;
    parse_inputs(input, output);

    auto unique_nums = part_1(output);
    auto out_sum = part_2(input, output);

    cout << "---PART 1---\n";
    cout << "Number of unique numbers = " << unique_nums << endl;
    cout << "---PART 2---\n";
    cout << "Sum of outputs = " << out_sum << endl;

    return 0;
}