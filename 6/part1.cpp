#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <cctype>

int parse_values(std::vector<std::vector<double>>& numbers, std::ifstream& file)
{
    char c;
    std::stringstream ss;
    file.clear();
    file.seekg(0);
    int cur_index = 0;
    int cur_row = 0;
    bool inNumber = false;
    while (file.get(c))
    {
        if(std::isdigit(c))
        {
            ss << c;
            inNumber = true;
        }
        else
        {
            //should be some form of white space
            if(inNumber)
            {
                numbers[cur_row][cur_index] = std::stod(ss.str());
                inNumber = false;
                ss.str("");
                cur_index++;
            }

            if(c == '\n')
            {
                cur_row++;
                cur_index = 0;
            }
        }
    }

    return -1;
}

char get_operand(int prob, int prob_line, std::ifstream& file)
{
    file.clear();
    file.seekg(0);
    char c;
    for(int i = 0; i < prob_line; i++)
    {
        file.get(c);
        while(c != '\n')
            file.get(c);
    }

    file.get(c);
    for(int i = 0; i < prob; i++)
    {
        while(c == ' ')
        {
            file.get(c);
        }

        while(c != ' ')
        {
            file.get(c);
        }

        while(c == ' ')
        {
            file.get(c);
        }
    }

    return c;
}

int count_problems(std::ifstream& file)
{
    int out = 0;
    file.clear();
    file.seekg(0);
    bool inNumber = false;
    char c;
    while (file.get(c))
    {
        if(std::isdigit(c))
        {
            inNumber = true;
        }
        else
        {
            //should be some form of white space
            if(inNumber)
            {
                out++;
                inNumber = false;
            }
            if(c == '\n')
            {
                return out;
            }

        }
    }
    return -1;
}

int count_values(std::ifstream& file)
{
    int out = 0;
    file.clear();
    file.seekg(0);
    char c;
    while (file.get(c))
    {
        if(c == '\n')
        {
            out++;
        }
    }
    return out - 1;
}


int main()
{
    // std::ifstream inputFile("example.txt");
    std::ifstream inputFile("input.txt");
    std::stringstream ss;

    if (!inputFile.is_open())
    {
        std::cout << "File no work" << std::endl;
        return 1;
    }

    const int problems = count_problems(inputFile);
    const int values = count_values(inputFile);

    std::cout << "problems: "  << problems << std::endl;
    std::cout << "values: "  << values << std::endl;

    std::cout << "==============================================" << std::endl;
    std::vector<std::vector<double>> numbers(values, std::vector<double>(problems));
    parse_values(numbers, inputFile);

    double total_sum = 0;
    for(int pi = 0; pi < problems; pi++)
    {
        //get the operand and do the stuff. should be homefree from here.
        char operand = get_operand(pi, values, inputFile);

        double out_val = numbers[0][pi];
        switch(operand)
        {
        case '*':
            for(int vi = 1; vi < values; vi++)
            {
                out_val *= numbers[vi][pi];
            }
            break;
        case '+':
            for(int vi = 1; vi < values; vi++)
            {
                out_val += numbers[vi][pi];
            }
            break;
        }
        total_sum += out_val;
    }

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Total: " << total_sum << std::endl;
    return 0;
}