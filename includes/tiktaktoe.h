#ifndef TIKTAKTOE_H
# define TIKTAKTOE_H

# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL2_gfxPrimitives.h>
# include <stdbool.h>

# define BOARD_SIZE 3

# define WIN_X 640
# define WIN_Y 480

# define CELL_X (WIN_X / BOARD_SIZE)
# define CELL_Y (WIN_Y / BOARD_SIZE)

enum	e_board {
	board_empty,
	board_player_x,
	board_player_o
};

enum	e_player {
	player_x,
	player_o
};

enum	e_state {
	state_runing,
	state_x_won,
	state_o_won,
	state_tie,
	state_quit
};

struct s_game{
	enum e_board	board[BOARD_SIZE * BOARD_SIZE];
	enum e_player	player;
	enum e_state	state;
};

void	render_game(SDL_Renderer *renderer, struct s_game const *game);
void	click_on_sell(struct s_game *game, int y, int x);

#endif /* TIKTAKTOE_H */
