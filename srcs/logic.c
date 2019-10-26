#include "tiktaktoe.h"

static inline void	switch_player(struct s_game *game)
{
	if (player_x == game->player) {
		game->player = player_o;
	} else if (player_o == game->player) {
		game->player = player_x;
	}
}

static bool	check_player_won(struct s_game *game, enum e_player player)
{
	enum e_board _player = player + 1;
	int	y_count = 0;
	int	x_count = 0;
	int	diag1_count = 0;
	int	diag2_count = 0;

	for (int y = 0; BOARD_SIZE > y; y++) {
		for (int x = 0; BOARD_SIZE > x; x++) {
			if (_player == game->board[y * BOARD_SIZE + x])
				++y_count;
			if (_player == game->board[x * BOARD_SIZE + y])
				++x_count;
		}
		if (BOARD_SIZE <= y_count || BOARD_SIZE <= x_count)
			return true;
		y_count = 0;
		x_count = 0;
		if (_player == game->board[y * BOARD_SIZE + y])
			++diag1_count;
		if (_player == game->board[y * BOARD_SIZE + BOARD_SIZE - y - 1])
			++diag2_count;
	}
	return BOARD_SIZE <= diag1_count || BOARD_SIZE <= diag2_count;
}

static int	count_cells(enum e_board const *board, enum e_board cell)
{
	int	count = 0;

	for (int i = 0; BOARD_SIZE * BOARD_SIZE > i; i++)
		if (cell == board[i])
			++count;
	return count;
}

static inline void	game_over_condition(struct s_game *game)
{
	if (check_player_won(game, player_x)) {
		game->state = state_x_won;
	} else if (check_player_won(game, player_o)) {
		game->state = state_o_won;
	} else if (!count_cells(game->board, board_empty)) {
		game->state = state_tie;
	}
}

static inline void	player_turn(struct s_game *game, int y, int x)
{
	if (board_empty == game->board[y * BOARD_SIZE + x]) {
		game->board[y * BOARD_SIZE + x] = game->player + 1;
		switch_player(game);
		game_over_condition(game);
	}
}

static inline void	reset_game(struct s_game *game)
{
	memset(game, 0, sizeof(struct s_game));
}

void	click_on_sell(struct s_game *game, int y, int x)
{
	if (state_runing == game->state)
		player_turn(game, y, x);
	else
		reset_game(game);
}
