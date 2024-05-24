#include "raylib.h"

#include "globals.h"
#include "graphics.h"
#include "images.h"
#include "sounds.h"
#include "levels.h"
#include "player.h"
#include "player.cpp"
#include "levels.cpp"
#include "level_manager.h"

level level_1;
player player_1;

void update_game() {
    switch (game_state) {
        case MENU_STATE:
            SetExitKey(KEY_ESCAPE);
            if (IsKeyPressed(KEY_ENTER)) {
                game_state = GAME_STATE;
            }
            break;
        case GAME_STATE:
            SetExitKey(0);
            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
                player_1.move_player(level_1, player_1, 0, -1);
                return;
            } else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
                player_1.move_player(level_1, player_1, 0, 1);
                return;
            } else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
                player_1.move_player(level_1, player_1, -1, 0);
                return;
            } else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
                player_1.move_player(level_1, player_1, 1, 0);
                return;
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                game_state = RELOAD_REQ_STATE;
            }

            break;
        case RELOAD_REQ_STATE:
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
                game_state = GAME_STATE;
            } else if (IsKeyPressed(KEY_R)) {
                --level_index;
                level_1.load_next_level(player_1);
                game_state = GAME_STATE;
            }
            break;
        case VICTORY_STATE:
            SetExitKey(KEY_ESCAPE);
            if (IsKeyPressed(KEY_ENTER)) {
                game_state = MENU_STATE;
            }
            break;
    }
}

void draw_game() {
    ++game_frame;

    switch (game_state) {
        case MENU_STATE:
            draw_menu();
            break;
        case GAME_STATE:
            level_1.draw_loaded_level();
            player_1.draw_player();
            player_1.draw_player_level();
            break;
        case RELOAD_REQ_STATE:
            draw_reload_req_menu();
            break;
        case VICTORY_STATE:
            draw_victory_menu();
            break;
    }
}

int main() {
    string filename("data/levels.sl");
    readFileToString(filename);
    initColumns();
    initRows();
    initData();
    modifyVector(levelData);

    for(int i = 0; i < LEVEL_COUNT; i++){
        LEVELS[i].set_rows(levelsRows[i]);
        LEVELS[i].set_columns(levelsColumns[i]);
        LEVELS[i].set_data(levelData[i]);
    }

    displayThings();

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(1024, 480, "Sokoban");
    SetTargetFPS(60);
    HideCursor();

    load_fonts();
    load_images();
    load_sounds();
    level_1.load_next_level(player_1);





    while (!WindowShouldClose()) {

        BeginDrawing();

        update_game();
        draw_game();

        EndDrawing();
    }
    CloseWindow();

    unload_sounds();
    unload_images();
    unload_fonts();

    return 0;
}
