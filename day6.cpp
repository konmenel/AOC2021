#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>


using std::cout;
using std::endl;
using std::vector;
using std::map;


typedef vector<uint8_t> input_t;
typedef map<uint8_t,uint64_t> fishmap_t;

input_t parse_inputs()
{
    input_t out;

    std::ifstream file("inputs/day6.dat");
    std::string num; 

    while (std::getline(file, num, ',')) {
        out.push_back(std::stoi(num));
    }

    return out;
}


fishmap_t count_fish(input_t& lanternfish) 
{
    fishmap_t map_fish = {  {0, 0},
                            {1, 0},
                            {2, 0},
                            {3, 0},
                            {4, 0},
                            {5, 0},
                            {6, 0},
                            {7, 0},
                            {8, 0}  };

    for (auto fish : lanternfish) {
        map_fish[fish]++;
    }

    return map_fish;
}


int part_1(input_t& lanternfish)
{
    for (int day = 1; day <= 80; day++) {
        size_t curr_size = lanternfish.size();
        for (int i = 0; i < curr_size; i++) {
            if (lanternfish[i] == 0) {
                lanternfish[i] = 6;
                lanternfish.push_back(8);
                continue;
            }
            lanternfish[i]--;
        }
    }

    return lanternfish.size();
}


uint64_t part_2(fishmap_t& fish_map)
{
    fishmap_t temp_map = fish_map;
    for (int day = 1; day <= 256; day++) {
        for (int i = 8; i >= 0; i--) {
            if (i == 0) {
                temp_map[6] += fish_map[i];
                temp_map[8] = fish_map[i];
                continue;
            }
            temp_map[i-1] = fish_map[i];
        }
        fish_map = temp_map;
    }


    uint64_t sum = 0;
    for (const auto& item : fish_map) {
        sum += item.second;
    }
    return sum;
}


int main() 
{
    auto lanterfish = parse_inputs();
    auto  fish_map = count_fish(lanterfish);

    auto num_fish = part_1(lanterfish);
    auto num_fish2 = part_2(fish_map);

    cout << "---PART 1---\n";
    cout << "Number of fish after 80 days = " << num_fish << endl;
    cout << "---PART 2---\n";
    cout << "Number of fish after 256 days = " << num_fish2 << endl;

    return 0;
}