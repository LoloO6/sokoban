#ifndef LEVELS_H
#define LEVELS_H


#include <cstddef>
#include "player.h"
#include <vector>

class level {
public:
    level() : rows(0), columns(0), data(nullptr) {}

    level(size_t rows, size_t columns, char *data) {
        this->rows = rows;
        this->columns = columns;
        this->data = data;
    }
    level(size_t rows, size_t columns, const std::vector<char>& data) {
        this->rows = rows;
        this->columns = columns;
        this->data = new char[rows * columns];
        std::copy(data.begin(), data.end(), this->data);
    }

    level(char *data) {
        rows = 0;
        columns = 0;
        this->data = data;

    }

    ~level() {
        rows = 0;
        columns = 0;

        delete[] data;
        data = nullptr;
    }


    [[nodiscard]]bool is_cell_inside_level(int row, int column) const {
        return row < rows && column < columns;
    }

    char &get_level_cell(size_t row, size_t column) {
        return data[row * columns + column];
    }

    void set_level_cell(size_t row, size_t column, char cell) {
        data[row * columns + column] = cell;
    }

    void load_next_level(player &player1);

    void derive_graphics_metrics_from_loaded_level() const;

    [[nodiscard]] size_t get_rows() const {
        return rows;
    }

    [[nodiscard]] size_t get_columns() const {
        return columns;
    }
    void set_rows(const size_t& other){
        rows = other;
    }
    void set_columns(const size_t& other){
        columns = other;
    }

    void draw_loaded_level();

    void clear_data();
    void set_data(const std::vector<char>& other);


private:
    size_t rows;
    size_t columns;
    char *data;
};

#endif // LEVELS_H
