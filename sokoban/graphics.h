#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"

#include "globals.h"
#include "images.h"
#include "levels.h"
#include "player.h"
#include "utilities.h"

#include <string>
#include <cmath>

void draw_menu() {
    ClearBackground(BLACK);

    const char *title = MENU_TITLE.c_str();
    const float title_font_size = MENU_TITLE_FONT_SIZE * screen_scale;
    const float title_y_shift   = MENU_TITLE_Y_SHIFT   * screen_scale;
    Vector2 title_size = MeasureTextEx(menu_font, title, title_font_size, 1);
    Vector2 title_position = {
            (screen_width - title_size.x) * 0.5f,
            screen_height * 0.5f - title_size.y * 0.5f - title_y_shift
    };
    DrawTextEx(menu_font, title, title_position, title_font_size, 1, MENU_TITLE_COLOR);

    const char *subtitle = MENU_SUBTITLE.c_str();
    const float subtitle_font_size = MENU_SUBTITLE_FONT_SIZE * screen_scale;
    const float subtitle_y_shift   = MENU_SUBTITLE_Y_SHIFT   * screen_scale;
    Vector2 subtitle_size = MeasureTextEx(menu_font, subtitle, subtitle_font_size, 1);
    Vector2 subtitle_position = {
            (screen_width - subtitle_size.x) * 0.5f,
            screen_height * 0.5f - subtitle_size.y * 0.5f + subtitle_y_shift
    };
    DrawTextEx(menu_font, subtitle, subtitle_position, subtitle_font_size, 1, MENU_SUBTITLE_COLOR);
}








void draw_reload_req_menu() {
    ClearBackground(BLACK);

    const char *title = RELOAD_REQ_TITLE.c_str();
    const float title_font_size = RELOAD_REQ_TITLE_FONT_SIZE * screen_scale;
    const float title_y_shift   = RELOAD_REQ_TITLE_Y_SHIFT   * screen_scale;
    Vector2 title_size = MeasureTextEx(menu_font, title, title_font_size, 1);
    Vector2 title_position = {
            (screen_width - title_size.x) * 0.5f,
            screen_height * 0.5f - title_size.y * 0.5f + title_y_shift
    };
    DrawTextEx(menu_font, title, title_position, title_font_size, 1, RELOAD_REQ_TITLE_COLOR);
}

void create_victory_menu_background() {
    for (auto &ball : victory_balls) {
        ball.x  = rand_up_to(screen_width);
        ball.y  = rand_up_to(screen_height);
        ball.dx = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED);
        ball.dx *= screen_scale;
        if (abs(ball.dx) < 0E-1) ball.dx = 1.0f;
        ball.dy = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED);
        ball.dy *= screen_scale;
        if (abs(ball.dy) < 0E-1) ball.dy = 1.0f;
        ball.radius = rand_from_to(VICTORY_BALL_MIN_RADIUS, VICTORY_BALL_MAX_RADIUS);
        ball.radius *= screen_scale;
    }

    /* Clear both the front buffer and the back buffer to avoid ghosting of the game graphics. */
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
}

void animate_victory_menu_background() {
    for (auto &ball : victory_balls) {
        ball.x += ball.dx;
        if (ball.x - ball.radius < 0 ||
            ball.x + ball.radius >= screen_width) {
            ball.dx = -ball.dx;
        }
        ball.y += ball.dy;
        if (ball.y - ball.radius < 0 ||
            ball.y + ball.radius >= screen_height) {
            ball.dy = -ball.dy;
        }
    }
}

void draw_victory_menu_background() {
    for (auto &ball : victory_balls) {
        DrawCircleV({ ball.x, ball.y }, ball.radius, VICTORY_BALL_COLOR);
    }
}

void draw_victory_menu() {
    DrawRectangle(
            0, 0,
            static_cast<int>(screen_width), static_cast<int>(screen_height),
            { 0, 0, 0, VICTORY_BALL_TRAIL_TRANSPARENCY }
    );

    animate_victory_menu_background();
    draw_victory_menu_background();

    const char *title = VICTORY_TITLE.c_str();
    const float title_font_size = VICTORY_TITLE_FONT_SIZE * screen_scale;
    const float title_y_shift   = VICTORY_TITLE_Y_SHIFT   * screen_scale;
    Vector2 title_size = MeasureTextEx(menu_font, title, title_font_size, 1);
    Vector2 title_position = {
            (screen_width - title_size.x) * 0.5f,
            screen_height * 0.5f - title_size.y * 0.5f - title_y_shift
    };
    DrawTextEx(menu_font, title, title_position, title_font_size, 1, VICTORY_TITLE_COLOR);

    const char *subtitle = VICTORY_SUBTITLE.c_str();
    const float subtitle_font_size = VICTORY_SUBTITLE_FONT_SIZE * screen_scale;
    const float subtitle_y_shift   = VICTORY_SUBTITLE_Y_SHIFT   * screen_scale;
    Vector2 subtitle_size = MeasureTextEx(menu_font, subtitle, subtitle_font_size, 1);
    Vector2 subtitle_position = {
            (screen_width - subtitle_size.x) * 0.5f,
            screen_height * 0.5f - subtitle_size.y * 0.5f + subtitle_y_shift
    };
    DrawTextEx(menu_font, subtitle, subtitle_position, subtitle_font_size, 1, VICTORY_SUBTITLE_COLOR);
}

void level::derive_graphics_metrics_from_loaded_level() const {
    screen_width = static_cast<float>(GetScreenWidth());
    screen_height = static_cast<float>(GetScreenHeight());

    cell_size = std::min(
            screen_width / static_cast<float>(columns),
            screen_height / static_cast<float>(rows)
    ) * CELL_SCALE;
    screen_scale = std::min(
            screen_width,
            screen_height
    ) / SCREEN_SCALE_DIVISOR;
    float level_width = static_cast<float>(columns) * cell_size;
    float level_height = static_cast<float>(rows) * cell_size;
    shift_to_center_cell_by_x = (screen_width - level_width) * 0.5f;
    shift_to_center_cell_by_y = (screen_height - level_height) * 0.5f;
}

#endif // GRAPHICS_H
