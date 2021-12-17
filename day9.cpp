#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

typedef vector<int> row_t;
typedef vector<row_t> input_t;

#define INPUT_FILE "inputs/day9.dat"


struct Point
{
    int x;
    int y;
    
    Point() : x(0), y(0) {};
    Point(int x, int y) : x(x), y(y) {};
    
    void change_coords(int x_new, int y_new)
    {
        x = x_new; 
        y = y_new;
    }
};


bool operator==(const Point& right, const Point& left)
{
    return (right.x == left.x && right.y == left.y);
}


input_t parse_inputs()
{
    std::ifstream file(INPUT_FILE);
    string line;

    input_t input;

    while (std::getline(file, line)) {
        row_t row;
        for (auto& num : line) {
            row.push_back((int)num - 48);
        }
        input.push_back(row);
    }

    return input;
}


bool isLowest(const input_t& inputs, int x, int y)
{
    // right boundry
    if (x == 0) {
        // right top corner
        if (y == 0) {
            return (
                inputs[x][y] < inputs[x+1][y] &&
                inputs[x][y] < inputs[x][y+1]
            );
        }

        // right bottom corner
        if (y == inputs[x].size()-1) {
            return (
                inputs[x][y] < inputs[x+1][y] &&
                inputs[x][y] < inputs[x][y-1]
            );
        }

        return (
            inputs[x][y] < inputs[x+1][y] &&
            inputs[x][y] < inputs[x][y+1] &&
            inputs[x][y] < inputs[x][y-1]
        );
    }
    
    // left boundry
    if (x == inputs.size()-1) {
        // left top corner
        if (y == 0) {
            return (
                inputs[x][y] < inputs[x-1][y] &&
                inputs[x][y] < inputs[x][y+1]
            );
        }

        // left bottom corner
        if (y == inputs[x].size()) {
            return (
                inputs[x][y] < inputs[x-1][y] &&
                inputs[x][y] < inputs[x][y-1]
            );
        }

        return (
            inputs[x][y] < inputs[x-1][y] &&
            inputs[x][y] < inputs[x][y+1] &&
            inputs[x][y] < inputs[x][y-1]
        );
    }
    
    // top boundry
    if (y == 0) {
        return (
            inputs[x][y] < inputs[x-1][y] &&
            inputs[x][y] < inputs[x+1][y] &&
            inputs[x][y] < inputs[x][y+1]
        );
    }
    
    // bottom boundry
    if (y == inputs[x].size()-1) {
        return (
            inputs[x][y] < inputs[x-1][y] &&
            inputs[x][y] < inputs[x+1][y] &&
            inputs[x][y] < inputs[x][y-1]
        );
    }
    
    // normal case
    return (
        inputs[x][y] < inputs[x-1][y] &&
        inputs[x][y] < inputs[x+1][y] &&
        inputs[x][y] < inputs[x][y-1] &&
        inputs[x][y] < inputs[x][y+1]
    );
}


bool isVisited(const Point& p, const vector<Point>& visited_points)
{
    for (const Point& point : visited_points) {
        if (p == point) {
            return true;
        }
    }
    return false;
}


bool isInBounds(const Point& p, const input_t& input)
{
    return !(
        p.x < 0 || 
        p.x > input.size() - 1 ||
        p.y < 0 ||
        p.y > input[0].size() - 1
        );
}


bool isTop3(const int& b, const vector<int>& top3_basins)
{
    for (int i = 0; i < 3; i++) {
        if (b > top3_basins[i]) {
            return true;
        }
    }
    return false;
}


int basin_size(Point center, vector<Point>& visited_points, const input_t& input)
{
    visited_points.push_back(center);

    Point neighbor(center.x - 1, center.y);
    if (isInBounds(neighbor, input)
        && !isVisited(neighbor, visited_points)
        && input[neighbor.x][neighbor.y] != 9) {
        basin_size(neighbor, visited_points, input);
    }

    neighbor.change_coords(center.x + 1, center.y);
    if (isInBounds(neighbor, input)
        && !isVisited(neighbor, visited_points)
        && input[neighbor.x][neighbor.y] != 9) {
        basin_size(neighbor, visited_points, input);
    }

    neighbor.change_coords(center.x, center.y - 1);
    if (isInBounds(neighbor, input)
        && !isVisited(neighbor, visited_points)
        && input[neighbor.x][neighbor.y] != 9) {
        basin_size(neighbor, visited_points, input);
    }

    neighbor.change_coords(center.x, center.y + 1);
    if (isInBounds(neighbor, input)
        && !isVisited(neighbor, visited_points)
        && input[neighbor.x][neighbor.y] != 9) {
        basin_size(neighbor, visited_points, input);
    }

    return visited_points.size();
}


int part_1(const input_t& input)
{
    int risk = 0;

    for (int x = 0; x < input.size(); x++) {
        for (int y = 0; y < input[x].size(); y++) {
            if (isLowest(input, x, y)) {
                risk += input[x][y] + 1;
            }
        }
    }
    return risk;
}


int part_2(const input_t& input)
{
    vector<int> top3_basins(3, 0);
    Point center;

    for (int x = 0; x < input.size(); x++) {
        for (int y = 0; y < input[x].size(); y++) {
            if (isLowest(input, x, y)) {
                center.change_coords(x, y); 
                vector<Point> visited_points = {};
                
                int curr_basin = basin_size(center, visited_points, input);
                
                if (isTop3(curr_basin, top3_basins)) {
                    int index = std::min_element(top3_basins.begin(), top3_basins.end()) - top3_basins.begin();
                    top3_basins[index] = curr_basin;
                }
            }
        }
    }

    int prod = 1;
    for (int basin : top3_basins) {
        prod *= basin;
    }
    return prod;
}


int main() 
{
    input_t input = parse_inputs();
    auto risk = part_1(input);
    auto res = part_2(input);

    cout << "---PART 1---\n";
    cout << "Sum of risk levels " << risk << endl;
    cout << "---PART 2---\n";
    cout << "Sum of risk levels " << res << endl;

    return 0;
}