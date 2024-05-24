
#include "levels.h"


void level::draw_loaded_level() {
    ClearBackground(BLACK);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            float x = shift_to_center_cell_by_x + static_cast<float>(column) * cell_size;
            float y = shift_to_center_cell_by_y + static_cast<float>(row) * cell_size;

            char cell = get_level_cell(row, column);
            switch (cell) {
                case FLOOR:
                case GOAL:
                case BOX:
                case BOX_ON_GOAL:
                    draw_image(floor_image, x, y, cell_size);
                default:
                    break;
            }
            switch (cell) {
                case WALL:
                    draw_image(wall_image, x, y, cell_size);
                    break;
                case GOAL:
                    draw_image(goal_image, x, y, cell_size);
                    break;
                case BOX:
                    draw_image(box_image, x, y, cell_size);
                    break;
                case BOX_ON_GOAL:
                    draw_image(box_on_goal_image, x, y, cell_size);
                    break;
                default:
                    break;
            }
        }
    }
}

void level::load_next_level(player &player1) {
    ++level_index;
    if (level_index >= LEVEL_COUNT) {
        level_index = 0;
        game_state = VICTORY_STATE;
        create_victory_menu_background();
    }

    rows = LEVELS[level_index].rows;
    columns = LEVELS[level_index].columns;
    data = new char[rows * columns];

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            char cell = LEVELS[level_index].data[row * columns + column];
            if (cell == PLAYER) {
                set_level_cell(row, column, FLOOR);
                player1.spawn_player(row, column);
            } else if (cell == PLAYER_ON_GOAL) {
                set_level_cell(row, column, GOAL);
                player1.spawn_player(row, column);
            } else {
                set_level_cell(row, column, cell);
            }
        }
    }

    derive_graphics_metrics_from_loaded_level();
}
void level::set_data(const std::vector<char>& other) {
    std::copy(other.begin(), other.end(), this->data);
}
void level::clear_data() {
    delete[] data;
    data = nullptr;
}