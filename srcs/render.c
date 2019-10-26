#include "tiktaktoe.h"

SDL_Color const g_grid_color = { .r = 255, .g = 255, .b = 255 };
SDL_Color const	g_x_color = { .r = 255, .g = 50, .b = 50 };
SDL_Color const	g_o_color = { .r = 50, .g = 100, .b = 255 };
SDL_Color const	g_tie_color = { .r = 100, .g = 100, .b = 100 };

static void	render_grid(SDL_Renderer *renderer, SDL_Color const *color)
{
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

	for (int i = 1; BOARD_SIZE > i; i++) {
		SDL_RenderDrawLine(renderer, i * CELL_X, 0, i * CELL_X, WIN_Y);
		SDL_RenderDrawLine(renderer, 0, i * CELL_Y, WIN_X, i * CELL_Y);
	}
}

static void	render_x(SDL_Renderer *renderer, int y, int x,
				SDL_Color const *color)
{
	float const	half_box_size = fmin(CELL_X, CELL_Y) * .25f;
	float const center_x = CELL_X * .5f + x * CELL_X;
	float const center_y = CELL_Y * .5f + y * CELL_Y;

	thickLineRGBA(renderer,
		center_x - half_box_size, center_y - half_box_size,
		center_x + half_box_size, center_y + half_box_size, 10,
		color->r, color->g, color->b, 255);
	thickLineRGBA(renderer,
		center_x + half_box_size, center_y - half_box_size,
		center_x - half_box_size, center_y + half_box_size, 10,
		color->r, color->g, color->b, 255);
}

static void	render_o(SDL_Renderer *renderer, int y, int x,
				SDL_Color const *color)
{
	float const	half_box_size = fmin(CELL_X, CELL_Y) * .25f;
	float const center_x = CELL_X * .5f + x * CELL_X;
	float const center_y = CELL_Y * .5f + y * CELL_Y;

	filledCircleRGBA(renderer,
		center_x, center_y, half_box_size + 5,
		color->r, color->g, color->b, 255);
	filledCircleRGBA(renderer,
		center_x, center_y, half_box_size - 5,
		0, 0, 0, 255);
}

static void	render_board(SDL_Renderer *renderer,
				enum e_board const *board,
				SDL_Color const *x_color,
				SDL_Color const *o_color)
{
	for (int y = 0; BOARD_SIZE > y; y++)
		for (int x = 0; BOARD_SIZE > x; x++)
			switch (board[y * BOARD_SIZE + x]) {
			case board_player_x: render_x(renderer, y, x, x_color); break;
			case board_player_o: render_o(renderer, y, x, o_color); break;
			default: break;
			}
}

static void	render_runing_state(SDL_Renderer *renderer,
							struct s_game const *game)
{
	render_grid(renderer, &g_grid_color);
	render_board(renderer, game->board, &g_x_color, &g_o_color);
}

static void	render_game_over_state(SDL_Renderer *renderer,
							struct s_game const *game,
							SDL_Color const *color)
{
	render_grid(renderer, color);
	render_board(renderer, game->board, color, color);
}

void	render_game(SDL_Renderer *renderer, struct s_game const *game)
{
	switch (game->state) {
	case state_runing: render_runing_state(renderer, game); break;
	case state_x_won: render_game_over_state(renderer, game, &g_x_color); break;
	case state_o_won: render_game_over_state(renderer, game, &g_o_color); break;
	case state_tie: render_game_over_state(renderer, game, &g_tie_color);
	default: break;
	}
}
