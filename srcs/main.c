#include "tiktaktoe.h"

int	main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Couldn't initialize SDL2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window	*window = SDL_CreateWindow("Procedural",
							100, 100, WIN_X, WIN_Y, SDL_WINDOW_SHOWN);

	if (!window) {
		fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer	*renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Event		e;
	struct s_game	game = {
		.board = { board_empty, board_empty, board_empty,
				board_player_o, board_empty, board_empty,
				board_player_x, board_empty, board_empty },
		.player = player_x,
		.state = state_tie
	};

	while (state_quit != game.state) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: game.state = state_quit; break;

			case SDL_MOUSEBUTTONDOWN:
				click_on_sell(&game,
					e.button.y / CELL_Y,
					e.button.x / CELL_X);
				break;

			default:
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		render_game(renderer, &game);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}
