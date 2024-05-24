
#ifndef SOKOBAN_LEVEL_MANAGER_H
#define SOKOBAN_LEVEL_MANAGER_H

#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include "globals.h"


using namespace std;
vector<string> allData;
vector<size_t> levelsColumns;
vector<size_t> levelsRows;
vector<vector<char>> levelData;
level LEVEL_1(LEVEL_1_DATA);
level LEVEL_2(LEVEL_2_DATA);
level LEVEL_3(LEVEL_3_DATA);


const size_t LEVEL_COUNT = 3;

level LEVELS[LEVEL_COUNT] = {
        LEVEL_1,
        LEVEL_2,
        LEVEL_3
};

void readFileToString(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filename << endl;
        return;
    }

    string lineFromFile;
    while (getline(file, lineFromFile)) {
        if (lineFromFile[0] != ';')
            allData.push_back(lineFromFile);
    }

    file.close();
}

void initRows() {
    levelsRows.clear();
    for (size_t i = 0; i < allData.size(); ++i) {
        int count = 1;
        for (size_t j = 0; j < allData[i].size(); ++j) {
            if (allData[i][j] == '|') {
                count++;
            }
        }
        levelsRows.push_back(count);
    }
}


void initColumns() {
    levelsColumns.clear();
    for (size_t i = 0; i < allData.size(); ++i) {
        int maxCount = 0;
        int count = 0;
        for (size_t j = 0; j < allData[i].size(); ++j) {
            if (allData[i][j] == '|') {
                maxCount = max(maxCount, count);
                count = 0;
            }
            if (allData[i][j] == WALL || allData[i][j] == FLOOR || allData[i][j] == BOX ||
                allData[i][j] == BOX_ON_GOAL
                || allData[i][j] == GOAL) {
                count++;
            }
            if (isdigit(allData[i][j])) {
                count += allData[i][j] - '1';
            }

        }
        levelsColumns.push_back(maxCount);
    }
}

void initData() {
    levelData.clear();
    levelData.resize(allData.size());
    for (size_t i = 0; i < allData.size(); ++i) {
        levelData[i].resize(allData[i].size());
        for (size_t j = 0; j < allData[i].size(); ++j) {

            levelData[i][j] = allData[i][j];

        }
    }

}

void modifyVector(std::vector<std::vector<char>> &input) {
    for (size_t lineIndex = 0; lineIndex < input.size(); ++lineIndex) {
        std::vector<char> result;
        size_t i = 0;
        int currentLineSize = 0;  // Track the current line size

        while (i < input[lineIndex].size()) {
            if (isdigit(input[lineIndex][i])) {
                int repetitions = 0;
                while (isdigit(input[lineIndex][i])) {
                    repetitions = repetitions * 10 + (input[lineIndex][i] - '0');
                    ++i;
                }
                char nextChar = input[lineIndex][i++];
                for (int j = 0; j < repetitions; ++j) {
                    result.push_back(nextChar);
                }
                currentLineSize += repetitions;
            } else if (input[lineIndex][i] == '|') {
                // Calculate how many ' ' characters to add
                size_t numSpacesToAdd = levelsColumns[lineIndex] - currentLineSize;
                for (int t = 0; t < numSpacesToAdd; ++t) {
                    result.push_back(' ');

                }
                currentLineSize = 0;
                ++i;
            } else {
                result.push_back(input[lineIndex][i++]);
                ++currentLineSize;
            }
        }
        if (result.size() != levelsColumns[lineIndex] * levelsRows[lineIndex]) {
            for (int k = 0; k < (levelsColumns[lineIndex] * levelsRows[lineIndex] - result.size()); k++) {
                result.push_back(' ');
            }
        }// After processing the line, assign the result to the input vector
        input[lineIndex] = result;

    }
}

void displayThings() {
    for (const auto &newline: allData) {
        cerr << newline << endl;
    }
    for (const auto &levelRow: levelsRows) {
        cerr << levelRow << endl;
    }
    for (const auto &levelColumn: levelsColumns) {
        cerr << levelColumn << endl;
    }
    for (const auto &row: levelData) {
        for (char ch: row) {
            cerr << ch;
        }
        cerr << endl;
    }
    cerr << endl << endl << endl << "data from globals:" << endl;
    for (auto ch: LEVEL_1_DATA) {
        cerr << ch;
    }
    cerr << endl;
    for (auto ch: LEVEL_2_DATA) {
        cerr << ch;
    }
    cerr << endl;
    for (auto ch: LEVEL_3_DATA) {
        cerr << ch;
    }
    cerr << endl;


}


#endif //SOKOBAN_LEVEL_MANAGER_H
