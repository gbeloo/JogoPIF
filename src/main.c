#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../cli-lib/cli.h"
#include "game.h"

int main() {
    hide_cursor();

    Game *game = init_game();

    show_start_screen();

    while (game->game_over == 0) {
        clear_screen();

        update_game(game);
        render_game(game);
        usleep(100000);
    }

    show_game_over_screen(game);

    save_scores(game);
    destroy_game(game);
    reset_terminal();
    return 0;
}
