
#include "player.h"
#include "levels.h"
#include "globals.h"

void player::move_player(level &level1, player &player1, int dx, int dy) {
    int next_row = static_cast<int>(player_row) + dy;
    int next_column = static_cast<int>(player_column) + dx;
    if (!level1.is_cell_inside_level(next_row, next_column)) {
        return;
    }

    char &cell = level1.get_level_cell(static_cast<size_t>(next_row), static_cast<size_t>(next_column));
    if (cell == FLOOR || cell == GOAL) {
        player_row = static_cast<size_t>(next_row);
        player_column = static_cast<size_t>(next_column);
    } else if (cell == BOX || cell == BOX_ON_GOAL) {
        int target_row = next_row + dy;
        int target_column = next_column + dx;
        if (!level1.is_cell_inside_level(target_row, target_column)) {
            return;
        }
        char &target_cell = level1.get_level_cell(static_cast<size_t>(target_row), static_cast<size_t>(target_column));
        if (target_cell == FLOOR || target_cell == GOAL) {
            cell = cell == BOX ? FLOOR : GOAL;
            if (target_cell == FLOOR) {
                target_cell = BOX;
            } else {
                target_cell = BOX_ON_GOAL;
                play_sound(goal_sound);
            }

            player_row = static_cast<size_t>(next_row);
            player_column = static_cast<size_t>(next_column);

            bool level_solved = true;
            for (size_t row = 0; level_solved && row < level1.get_rows(); ++row) {
                for (size_t column = 0; level_solved && column < level1.get_columns(); ++column) {
                    char cell_to_test = level1.get_level_cell(row, column);
                    if (cell_to_test == GOAL) {
                        level_solved = false;
                    }
                }
            }

            if (level_solved) {
                //level1.unload_level();
                level1.load_next_level(player1);
                play_sound(exit_sound);
            }
        }
    }
}

void player::draw_player_level() {
    {
        const float level_font_size = GAME_LEVEL_FONT_SIZE * screen_scale;
        const float level_top_margin = GAME_LEVEL_Y_SHIFT * screen_scale;

        std::string level_text = std::string("Level ");
        level_text += std::to_string(level_index + 1);
        level_text += " out of ";
        level_text += std::to_string(LEVEL_COUNT);

        Vector2 level_size = MeasureTextEx(menu_font, level_text.c_str(), level_font_size, 1);
        Vector2 level_position = {(screen_width - level_size.x) * 0.5f, level_top_margin};
        DrawTextEx(menu_font, level_text.c_str(), level_position, level_font_size, 1, GAME_LEVEL_COLOR1);
        level_position.x -= 4 * screen_scale;
        level_position.y -= 4 * screen_scale;
        DrawTextEx(menu_font, level_text.c_str(), level_position, level_font_size, 1, GAME_LEVEL_COLOR2);
    }
}

void player::draw_player() const {
    {
        float x = shift_to_center_cell_by_x + static_cast<float>(player_column) * cell_size;
        float y = shift_to_center_cell_by_y + static_cast<float>(player_row) * cell_size;
        draw_sprite(player_sprite, x, y, cell_size);
    }
}