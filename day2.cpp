#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using std::vector; 
using std::string;
using std::ifstream;

#define PRINT(x) std::cout << x << std::endl;


struct Command
{
    string operation;
    int units;

    Command(string instuction) 
    {
        // Split the string
        vector<string> tokens = {};
        size_t pos = 0;
        std::istringstream ss(instuction);

        ss >> operation;
        ss >> units;
    }
    
    void print()
    {
        PRINT(operation << " " << units)
    }
};


vector<Command> parse_inputs() 
{
    vector<Command> commands = {};

    // Parsing
    string line;
    ifstream file("day2-inputs.dat");
    while (std::getline(file, line))
    {
        commands.push_back(Command(line));
    }

    file.close();
    return commands;
}


int main()
{    
    // Part 1
    vector<Command> commands = parse_inputs();
    int depth = 0;
    int horizontal = 0;

    for (auto command : commands)
    {
        if (command.operation == "forward")
            horizontal += command.units;
        else if (command.operation == "down")
            depth += command.units;
        else
            depth -= command.units;         
    }

    PRINT("---Part 1---")
    PRINT("horizontal: " << horizontal)
    PRINT("depth: " << depth)
    PRINT("multiplication " << depth * horizontal)  

    // Part 2
    int aim = 0;
    depth = 0; 
    horizontal = 0;

    for (auto command : commands)
    {
        if (command.operation == "forward")
        {
            horizontal += command.units;
            depth += aim * command.units;
        }
        else if (command.operation == "down")
            aim += command.units;
        else
            aim -= command.units;         
    }
    
    PRINT("\n---Part 2---")
    PRINT("horizontal: " << horizontal)
    PRINT("depth: " << depth)
    PRINT("multiplication " << depth * horizontal)  


    return 0;
}