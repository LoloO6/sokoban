#ifndef SOKOBAN_PARSER_H
#define SOKOBAN_PARSER_H

#include <sstream>
#include <fstream>
#include <array>
#include <iomanip>
#include <iostream>

struct Level {
    std::string data;
    int max_row;
    int max_column;

    Level() {
        max_row = 1;
        max_column = 1;
    }
};

Level Levels[3];

std::array<Level, 3> parse(const std::string& input) {
    std::istringstream stream(input);
    std::string line;
    int level_index_count = 0;
    int current_row_width = 0;

    while (getline(stream, line) && level_index_count < 3) {
        // trunc
        line.erase(0, line.find_first_not_of(" \n\r\t"));
        line.erase(line.find_last_not_of(" \n\r\t") + 1);

        // Check for level headers and skip them
        if (line.at(0) == ';') {
            Levels[level_index_count].max_row = 1; // Reset rows for each level
            continue;
        }

        Levels[level_index_count].data.clear();
        current_row_width = 0;

        size_t max_col_width = 0;
        size_t cur_col_width = 0;
        for(int i = 0; i < line.length(); i++){
            char symbol = line.at(i);
            if(isdigit(symbol)){
                cur_col_width += line.at(i) - '1';
            }
            else if (symbol == '|'){
                if(cur_col_width > max_col_width) {
                    max_col_width = cur_col_width;
                }
                cur_col_width = 0;
                current_row_width++;
            }
            else{
                cur_col_width += 1;
            }
        }
        if(current_row_width != 0) {current_row_width++;}

        cur_col_width = 0;
        std::string atr;
        for(int i = 0; i < line.length(); i++) {
            char symbol = line.at(i);
            if(isdigit(symbol)){
                int repeat = symbol - '1';
                while(isdigit(line.at(i+1))){
                    repeat = stoi(std::string(1,symbol)+line.at(i+1)) - 1;
                    i++;
                }
                atr += std::string(repeat, line.at(i+1));
                cur_col_width += repeat;
            }
            else if (symbol == '|'){
                if(cur_col_width < max_col_width) {
                    atr += std::string(max_col_width - cur_col_width, ' ');
                }
                cur_col_width = 0;
            }
            else {
                atr += symbol;
                cur_col_width += 1;
            }
        }
        Levels[level_index_count].data = atr;
        Levels[level_index_count].max_row = current_row_width;
        Levels[level_index_count].max_column = max_col_width;

        if (!Levels[level_index_count].data.empty()) {
            level_index_count++;
        }
    }
    return reinterpret_cast<const std::array<Level, 3> &>(Levels);
}

std::array<Level, 3> create() {
    std::ifstream level_data_file("data/levels.sl");
    std::string extracted_data;
    std::stringstream level_data_stream;
    level_data_stream << level_data_file.rdbuf();
    extracted_data = level_data_stream.str();
    std::cout << extracted_data << std::endl;
    level_data_file.close();
    return parse(extracted_data);
}
#endif
