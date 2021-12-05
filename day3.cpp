#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <bitset>

#define N_BITS 12


std::vector<int> parse_inputs()
{
    std::vector<int> data = {};
    std::ifstream data_file("inputs/day3.dat");

    std::string line;
    char* ptr = nullptr;
    while (std::getline(data_file, line))
    {
        data.emplace_back(std::strtol(line.c_str(), &ptr, 2));
    }
    return data;
}

std::bitset<N_BITS> to_binary(int num) { return std::bitset<N_BITS>(num); }

void print_vec(std::string name, std::vector<int> vec)
{
    std::cout << name << ":" << std::endl;

    for (int number : vec)
        std::cout << to_binary(number) << "\n";
    std::cout << std::endl;
}

uint64_t part_1(std::vector<int>& data)
{
    int DATA_SIZE_HALF = data.size() / 2;
    uint32_t gamma_rate = 0;
    int count_1;

    for (int i = 0; i < N_BITS; i++){
        count_1 = 0;
        int mask = 1 << i;

        for (auto number : data) {
            if ((number & mask) == mask) { count_1++; };
        }

        gamma_rate += count_1 > DATA_SIZE_HALF ? mask : 0;
    }

    return gamma_rate * (~gamma_rate & 4095);
}


uint64_t part_2(std::vector<int>& data)
{
    int count_0, count_1;
    std::vector<int> oxy = data;
    std::vector<int> co2 = data;

    std::vector<int> keep_0 = {};
    std::vector<int> keep_1 = {};

    for (int i = N_BITS - 1; i >= 0; i--){
        int mask = 1 << i;
        
        // oxygen loop
        if (oxy.size() != 1)
        {
            count_0 = 0;
            count_1 = 0;
            keep_0.clear();
            keep_1.clear();

            for (auto number : oxy) {
                if ((number & mask) == mask) {
                    keep_1.push_back(number);
                    count_1++;
                } else { 
                    keep_0.push_back(number);
                    count_0++;
                };
            }
            oxy = count_1 >= count_0 ? keep_1 : keep_0;
        }

        // co2 loop
        if (co2.size() != 1)
        {
            count_0 = 0;
            count_1 = 0;
            keep_0.clear();
            keep_1.clear();

            for (auto number : co2) {
                if ((number & mask) == mask) {
                    keep_1.push_back(number);
                    count_1++;
                } else { 
                    keep_0.push_back(number);
                    count_0++;
                };
            }
            co2 = count_1 >= count_0 ? keep_0 : keep_1;
        }
    }
    return oxy[0] * co2[0];
}

int main()
{
    auto data = parse_inputs();
    auto power = part_1(data);
    auto life_support = part_2(data);

    std::cout << "---PART 1---\n";
    std::cout << "Power Consumption = " << power << std::endl;
    std::cout << std::endl;
    std::cout << "---PART 2---\n";
    std::cout << "Life Support = " << life_support << std::endl;
    return 0;
}
