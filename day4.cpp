#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::string;

typedef vector<vector<int>> Board_t;
typedef vector<vector<bool>> HitBoard_t;

class Bingo
{
public:
    vector<int> numbers;
    vector<Board_t> boards;
    vector<HitBoard_t> hit_boards;    

    void print_numbers()
    {
        for (int num : numbers)
            std::cout << num << ",";
        std::cout << "\n";
    }

    void mark_hit(const int number)
    {
        for (int i = 0; i < boards.size(); i++) {
            for (int row = 0; row < boards[i].size(); row++) {
                for (int col = 0; col < boards[i][row].size(); col++) {
                    if (boards[i][row][col] == number)
                        hit_boards[i][row][col] = true;
                }
            }
        }
    }

    int sum_board(const int index)
    {
        int sum = 0;
        for (int row = 0; row < boards[index].size(); row++) {
            for (int col = 0; col < boards[index][row].size(); col++) {
                if (!hit_boards[index][row][col])
                    sum += boards[index][row][col];
            }
        }
        return sum;
    }

    bool is_board_skipped(vector<int>& skip_boards, const int current_index) 
    {
        for (int skip_board : skip_boards) {
                if (current_index == skip_board) {
                    return true;
                }
        }
        return false;
    }

    int wining_board(vector<int> skip_boards = {})
    {
        for (int i = 0; i < hit_boards.size(); i++)
        {
            if (is_board_skipped(skip_boards, i))
                continue;            

            // row-wise check
            bool hit_all;
            for (auto row : hit_boards[i]) {
                hit_all = true;
                for (auto elem : row) {
                    hit_all = elem && hit_all;
                }
                if (hit_all)
                    return i;
            }

            // column-wise check
            for (int col = 0; col < hit_boards[0].size(); col++) {
                hit_all = true;
                for (int row = 0; row < hit_boards[i][0].size(); row++) {
                    hit_all = hit_all && hit_boards[i][row][col];
                }
                if (hit_all)
                    return i;
            }
        }

        return -1;
    }
};

template<class T>
void print_board(T board)
{
    for (auto row : board) {
        for (int elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
}


void parse_inputs(Bingo& bingo) 
{
    std::ifstream file("inputs/day4.dat");
    string line;

    // first line parse
    std::getline(file, line);
    std::stringstream nums(line);
    string num;
    while (std::getline(nums, num, ','))
        bingo.numbers.push_back(stoi(num));
    
    // boards parse
    Board_t board = {};
    HitBoard_t hit_board = {};
    while (std::getline(file, line)) {
        if (line.size() == 0) {
            if (!board.empty()) {
                bingo.boards.emplace_back(board);
                bingo.hit_boards.push_back(hit_board);
                board.clear();
                hit_board.clear();
            }
            continue;
        }

        vector<int> row = {};
        int num;
        std::istringstream nums(line);
        while (nums >> num) {
            // std::cout << nums.str() << std::endl;
            row.emplace_back(num);
        }
        
        board.emplace_back(row);
        hit_board.emplace_back(row.size(), false);
    }
}


int part_1(Bingo& bingo)
{
    int winning_board;
    for (auto number : bingo.numbers) {
        bingo.mark_hit(number);
        
        winning_board = bingo.wining_board();
        if (winning_board != -1) {
            return bingo.sum_board(winning_board) * number;
        }

    }
    return -1;
}


int part_2(Bingo& bingo) 
{
    int winning_board;
    vector<int> won_boards = {};
    for (auto number : bingo.numbers) {
        bingo.mark_hit(number);

        while ((winning_board = bingo.wining_board(won_boards)) != -1) {
            won_boards.push_back(winning_board);
        }
        
        if (won_boards.size() == bingo.boards.size() || number == bingo.numbers.back()) {
            return bingo.sum_board(won_boards.back()) * number;
        }
    }
    return -1;
}


int main()
{
    Bingo bingo;
    parse_inputs(bingo);

    auto score = part_1(bingo);
    auto score2 = part_2(bingo);

    std::cout << "---Part 1---\n"; 
    std::cout << "score = " << score << "\n";
    std::cout << "---Part 2---\n"; 
    std::cout << "score = " << score2 << "\n";

    return 0;
}
