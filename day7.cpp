#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using std::cout;
using std::endl;
using std::vector;
using std::string;


typedef vector<int> input_t;

input_t parse_inputs()
{
    input_t out;

    std::ifstream file("inputs/day7.dat");
    string num;
    
    while (std::getline(file, num, ',')) {
        out.push_back(std::stoi(num));
    }

    return out;
}


int part_1(input_t& crabs)
{
    int cost;
    int best_cost = INT_MAX;
    int pos = 0;
    while (true) {
        cost = 0;
        for (auto& crab : crabs) {
            cost += std::abs(crab - pos);
        }
        
        if (cost > best_cost) {
            break;
        }

        best_cost = cost;
        pos++;
    }
    
    return best_cost;
}


int part_2(input_t& crabs)
{
    int cost;
    int diff;
    int best_cost = INT_MAX;
    int pos = 0;
    while (true) {
        cost = 0;
        for (auto& crab : crabs) {
            diff = std::abs(crab - pos);
            cost += diff * (diff + 1) / 2;
        }
        
        if (cost > best_cost) {
            break;
        }

        best_cost = cost;
        pos++;
    }
    
    return best_cost;
}


int main() 
{
    auto crabs = parse_inputs();
    auto cost = part_1(crabs);
    auto cost2 = part_2(crabs);

    cout << "---PART 1---\n";
    cout << "Min cost = " << cost << endl;
    cout << "---PART 2---\n";
    cout << "Min cost = " << cost2 << endl;
    
    return 0;
}