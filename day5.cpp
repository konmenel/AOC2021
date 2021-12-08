#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>


using std::vector;

typedef vector<vector<int>> grid_t;

struct Line
{
    vector<int> x;
    vector<int> y;

    bool isHorizontal() { return y[0] == y[1]; }
    bool isVertical() { return x[0] == x[1]; }
};

typedef vector<Line> lines_t;

lines_t parse_inputs() 
{
    lines_t out; 
    std::ifstream file("inputs/day5.dat");
    std::string file_line, token;
    size_t pos = 0;

    while (std::getline(file, file_line)) {
        Line line;
        pos = file_line.find(",");
        token = file_line.substr(0, pos);
        file_line.erase(0, pos+1);
        line.x.emplace_back(std::stoi(token));

        pos = file_line.find(" -> ");
        token = file_line.substr(0, pos);
        file_line.erase(0, pos+4);
        line.y.emplace_back(std::stoi(token));

        pos = file_line.find(",");
        token = file_line.substr(0, pos);
        file_line.erase(0, pos+1);
        line.x.emplace_back(std::stoi(token));

        line.y.emplace_back(std::stoi(file_line));

        out.push_back(line);
    }
    return out;
}


int part_1(grid_t& grid, const lines_t& lines)
{
    int result = 0;
    
    for (Line line : lines) {
        if (line.isHorizontal()) {
            int min_x = std::min(line.x[0], line.x[1]);
            int max_x = std::max(line.x[0], line.x[1]);
            for (int x = min_x; x <= max_x; x++) {
                grid[line.y[0]][x] += 1;
            }
        } else if (line.isVertical()) {
            int min_y = std::min(line.y[0], line.y[1]);
            int max_y = std::max(line.y[0], line.y[1]);
            for (int y = min_y; y <= max_y; y++) {
                grid[y][line.x[0]] += 1;
            }
        }
    }
    
    for (auto row : grid) {
        for (auto node : row) {
            if (node > 1) {
                result += 1;
            }
        }
    }
    return result;
}


int part_2(grid_t& grid, const lines_t& lines)
{
    int result = 0;
    
    for (Line line : lines) {
        if ((!line.isHorizontal()) && (!line.isVertical())) {
            int min_index = std::min_element(line.y.begin(), line.y.end()) - line.y.begin();
            int x = line.x[min_index];
            int y = line.y[min_index];
            int max_y = std::max(line.y[0], line.y[1]);
            int min_x = std::min(line.x[0], line.x[1]);

            int direction = (x == min_x) ? 1 : -1;
            
            while (y <= max_y) {
                grid[y][x] += 1;
                y += 1;
                x += direction;
            }
        }
    }
    
    for (auto row : grid) {
        for (auto node : row) {
            if (node > 1) {
                result += 1;
            }
        }
    }
    return result;
}


int main() 
{
    grid_t grid(1000, vector<int>(1000, 0));
    lines_t lines = parse_inputs();

    auto score1 = part_1(grid, lines);
    auto score2 = part_2(grid, lines);

    std::cout << "---Part 1---\n";
    std::cout << "Score: " << score1 << std::endl;
    std::cout << "---Part 2---\n";
    std::cout << "Score: " << score2 << std::endl;

    return 0;
}
