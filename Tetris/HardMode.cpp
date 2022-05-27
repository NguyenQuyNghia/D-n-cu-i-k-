#include "HardMode.h"
void update_score (Board board)
{
	int tmp=0;
	for (int i=0;i<Rows;i++)
	{
		for (int j=0;j<Cols;j++)
		{
			tmp+=board[i][j];
		}
	}
	score=tmp;
}
void draw_score(SDL_Renderer *renderer,TTF_Font *font)
{
	SDL_Rect fillRect = {306, 0, 194, 610};
	Color g_color_score;
	g_color_score.r=3;
	g_color_score.g=138;
	g_color_score.b=255;
	g_color_score.a=1;
	SDL_SetRenderDrawColor(renderer, g_color_score.r, g_color_score.g,g_color_score.b,g_color_score.a);
	SDL_RenderFillRect(renderer, &fillRect);
	SDL_Color white={255,255,255};
	SDL_Rect rect = {405,(SCREEN_HEIGHT/2)-50,0,0};
	draw_text(renderer, font, "SCORE", rect, white);
	char str[10];
	itoa(score,str,10);
	SDL_Rect rect_score = {405,(SCREEN_HEIGHT/2),0,0};
	draw_text(renderer, font, str, rect_score, white);
	SDL_RenderPresent(renderer);
}
void set_current_time (Uint32 t)
{
	end=t;
}
void swap(int a,int b)
{
	int tmp=a;
	a=b;
	b=tmp;
}
int pow(int x)
{
	int power=1;
	int value=2;
	while (value != x)
	{
		value *=2;
		power++;
	}
	return power;
}
bool initSDL(SDL_Window **window, SDL_Renderer **renderer)
{
	TTF_Init();
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout<< SDL_GetError();
		return false;
	}
	*window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout<< SDL_GetError();
		return false;
	}
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout<< SDL_GetError();
		return false;
	}
    return true;
}
void add_random(Board board)
{
	int mark[Cols];
	int length=0;
	for (int i=0;i<Cols;i++)
	{
		if (board[0][i]==0)
		{
			mark[length]=i;
			length++;
		}
	}
	int index=rand() % length;
	int randomValue=rand() % 100;
	if (randomValue<20)
	{
		board[0][mark[index]]=4;
	}
	else
	{
		board[0][mark[index]]=2;
	}
}

void draw_board(SDL_Renderer *renderer, const Board board, TTF_Font *font)
{
	for (int x = 0; x < Rows; x++)
	{
		for (int y = 0; y < Cols; y++)
		{
			if (board[x][y] % 2 ==0 && board[x][y]!=0)
			{
				int value=board[x][y];
				SDL_Rect fillRect = {SCREEN_PAD + y * (squareSize + SCREEN_PAD), SCREEN_PAD + x * (squareSize + SCREEN_PAD), squareSize, squareSize};
				Color g_color=color[pow(board[x][y])-1];
				SDL_SetRenderDrawColor(renderer, g_color.r, g_color.g,g_color.b,g_color.a);
				SDL_RenderFillRect(renderer, &fillRect);
				char s[10];
				itoa (value,s,10);
				draw_white_text(renderer, font, s, fillRect);
			}
			else if (board[x][y] ==1)
			{
				SDL_Rect fillRect = {SCREEN_PAD + y * (squareSize + SCREEN_PAD), SCREEN_PAD + x * (squareSize + SCREEN_PAD), squareSize, squareSize};
				
				SDL_SetRenderDrawColor(renderer, 144, 144, 144, 0);
				SDL_RenderFillRect(renderer, &fillRect);
			}	
			else
			{
				SDL_Rect fillRect = {SCREEN_PAD + y * (squareSize + SCREEN_PAD), SCREEN_PAD + x * (squareSize + SCREEN_PAD), squareSize, squareSize};
				
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderFillRect(renderer, &fillRect);
			}
		}
	}
}
void closeSDL(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}
void clear_screen(SDL_Renderer *renderer)
{

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}
void render_game(SDL_Renderer *renderer, Board board, TTF_Font *font)
{
	clear_screen(renderer);
	draw_board(renderer, board, font);
	draw_score(renderer,font);
	SDL_RenderPresent(renderer);
}
void game_loop(Board board, SDL_Renderer *renderer,SDL_Window *window)
{
	TTF_Font *font = NULL;
	font = TTF_OpenFont(FONT_PATH, CELL_FONT_SIZE);
	if (font == NULL)
	{
		return;
	}
	add_random(board);
	render_game(renderer, board, font);

	bool quit = false;
	SDL_Event e;
	bool out_game=false;
	// auto start = std::chrono::steady_clock::now();
	bool use_hammer= false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			
			if (e.type == SDL_QUIT)
			{
				quit = true;
				out_game=true;
			}
			if (e.type== SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_LEFT)
				{
					move_left(board);
				}
				else if (e.key.keysym.sym == SDLK_RIGHT)
				{
					move_right(board);
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					STEP_DELAY=50;
				}
				else if (e.key.keysym.sym == SDLK_SPACE)
				{
					use_hammer=true;
				}
			}
			else 
			{
				STEP_DELAY=500;
			}
		}
		
		bool nextBlock=false;
		Position idx;
		//danh dau vi tri vien vua roi xuong
		set_current_time(SDL_GetTicks());

		if (end-start>STEP_DELAY)
		{
			bool success=false;
			drop_block(board,success,nextBlock,idx);
			start=end;
		}

		render_game(renderer, board, font);
		if (nextBlock)
		{
			while (can_merge(board))
			{
				merge(board,idx,renderer,font);
				delete_empty_block (board,renderer,font);
				while (is_continue_merge(board,idx))
				{
					merge(board,idx,renderer,font);
					delete_empty_block (board,renderer,font);
				}
				merge_y(board,idx,renderer,font);
				merge_x(board,idx,renderer,font);
			}
			delete_empty_block (board,renderer,font);
			if (isWinning(board) || isGameOver(board) )
			{
				quit=true;
			}
			update_score (board);
			render_game(renderer, board, font);
			// if (use_hammer)
			// {
			// 	hammer(renderer,board,font);
			// }
			delete_empty_block (board,renderer,font);
			add_random(board);
		}
		
	}
	if (!out_game)
	{
		retry(renderer, GOVER_FONT_SIZE,window);
	}
}
// void hammer(SDL_Renderer *renderer,Board board, TTF_Font *font)
// {
// 	SDL_Event e;
// 	int backup[Rows][Cols];
// 	for (int i=0;i<Rows;i++)
// 	{
// 		for (int j=0;j<Cols;j++)
// 		{
// 			backup[i][j]=board[i][j];
// 		}
// 	}
// 	bool quit=false;
// 	while (!quit)
// 	{
// 		while (SDL_PollEvent(&e) != 0)
// 		{
// 			if (e.type == SDL_QUIT)
// 			{
// 				quit = true;
// 			}
// 			if (e.type==SDL_MOUSEBUTTONDOWN)
// 			{
// 				if (e.button.button==SDL_BUTTON_LEFT)
// 				{
// 					int xb=e.button.x;
// 					int yb=e.button.y;
// 					int idxX=xb/squareSize;
// 					int idxY=yb/squareSize;
// 					board[idxX][idxY]=0;
// 					quit=true;
// 				}
// 			}
// 			if (e.type == SDL_MOUSEMOTION)
// 			{
// 				int xm=e.motion.x;
//                 int ym=e.motion.y;
// 				if (xm>=0 && xm <= BOARD_WIDTH && ym >=0 && ym <=BOARD_HEIGHT)
// 				{
// 					int idxX=xm / squareSize;
// 					int idxY=ym / squareSize;
// 					for (int i=0;i<Rows;i++)
// 					{
// 						for (int j=0;j<Cols;j++)
// 						{
// 							if (i==idxY&&j==idxX)
// 							{
// 								board[i][j]=1;
// 							}
// 							else
// 							{
// 								board[i][j]=backup[i][j];
// 							}
// 						}
// 					}

// 					render_game(renderer, board, font);
// 				}
// 			}
			
// 		}
// 		// SDL_RenderPresent(renderer);
// 	}
// 	return;
// }
void drop_block(Board board,bool &success,bool &nextBlock,Position &idx)
{
	for (int i=0;i<Rows-1;i++)
	{
		for (int j=0;j<Cols;j++)
		{
			if (i==Rows-2 && board[i][j]!=0 && board[i+1][j]==0)
			{
				nextBlock=true;
				idx.x=i+1;
				idx.y=j;
			}
			else if (board[i][j]!=0 && board[i+1][j]==0 && board[i+2][j]!=0)
			{
				nextBlock=true;
				idx.x=i+1;
				idx.y=j;
			}
			if (board[i][j]!=0 && board[i+1][j]==0)
			{
				success=true;
				//swap(board[i][j],board[i+1][j]);
				int tmp=board[i][j];
				board[i+1][j]=tmp;
				board[i][j]=0;
				break;
			}
		}
		if (success)
		{
			break;
		}
	}
}
bool isWinning(Board board)
{
	for (int i=0;i<Rows;i++)
	{
		for (int j=0;j<Cols;j++)
		{
			if (board[i][j]==WINNING_BLOCK)
			{
				return true;
			}
		}
	}
	return false;
}
bool isGameOver(Board board)
{
	int cnt=0;
	for (int i=0;i<Rows;i++)
	{
		for (int j=0;j<Cols;j++)
		{
			if (board[i][j]!=0)
			{
				cnt++;
			}
		}
	}
	if (cnt==Rows * Cols)
	{
		return true;
	}
	return false;
}
void merge_y (Board board,Position idx,SDL_Renderer *renderer, TTF_Font *font)
{
	bool is_merge_y = false;
	for (int i=0;i<Rows-1;i++)
	{
		for (int j=0;j<idx.y;j++)
		{
			if  (board[i][j]==board[i+1][j] && board[i][j]!=0 )
			{
				board[i][j] *=2;
				board[i+1][j]=0;
				is_merge_y=true;
			}
		}
	}
	for (int i=0;i<Rows-1;i++)
	{
		for (int j=idx.y+1;j<Cols;j++)
		{
			if  (board[i][j]==board[i+1][j] && board[i][j]!=0 )
			{
				board[i][j] *=2;
				board[i+1][j]=0;
				is_merge_y=true;
			}
		}
	}
	if (is_merge_y)
	{
		delete_empty_block (board,renderer, font);
		// SDL_Delay(200);
	}
}
void merge_x (Board board,Position idx,SDL_Renderer *renderer, TTF_Font *font)
{
	bool is_merge_x = false;
	for (int i=0;i<Rows;i++)
	{
		for (int j=idx.y;j>0;j--)
		{
			if  (board[i][j]==board[i][j-1] && board[i][j]!=0 )
			{
				board[i][j] *=2;
				board[i][j-1]=0;
				is_merge_x=true;
			}
		}
	}
	for (int i=0;i<Rows;i++)
	{
		for (int j=idx.y;j<Cols-1;j++)
		{
			if  (board[i][j]==board[i][j+1] && board[i][j]!=0 )
			{
				board[i][j] *=2;
				board[i][j+1]=0;
				is_merge_x=true;
			}
		}
	}
	if  (is_merge_x)
	{
		delete_empty_block (board,renderer, font);
		// SDL_Delay(200);
	}
	
}
void move_left(Board board)
{
	bool checkLeft=false;
	for (int i=0;i<Rows-1;i++)
	{
		for (int j=1;j<Cols;j++)
		{
			if (board[i][j]!=0 && board[i+1][j]==0 && board[i][j-1]==0)
			{
				checkLeft=true;
				//swap(board[i][j],board[i][j-1]);
				int tam1=board[i][j];
				board[i][j-1]=tam1;
				board[i][j]=0;
				break;
			}
		}
		if (checkLeft)
		{
			break;
		}
	}
}
void move_right(Board board)
{
	bool checkRight=false;
	for (int i=0;i<Rows-1;i++)
	{
		for (int j=0;j<Cols-1;j++)
		{
			if (board[i][j]!=0 && board[i+1][j]==0 && board[i][j+1]==0)
			{
				checkRight=true;
				//swap(board[i][j],board[i][j+1]);
				int tam2=board[i][j];
				board[i][j+1]=tam2;
				board[i][j]=0;
				break;
			}
		}
		if (checkRight)
		{
			break;
		}
	}
}
bool can_merge(Board board)
{
	//kiem tra xem con o nao dang lo lung hay khong
	for (int i=0;i<Rows-1;i++)
	{
		for (int j=0;j<Cols;j++)
		{
			if (board[i][j]!=0 && board[i+1][j]==0)
			{
				return false;
			}
		}
	}
	//kiem tra xem co hop cac o lai theo chieu doc
	for (int i=0;i<Rows-1;i++)
	{
		for (int j=0;j<Cols;j++)
		{
			if (board[i][j]==board[i+1][j] && board[i][j]!=0 )
			{
				return true;
			}
		}
	}
	//kiem tra xem co hop cac o lai theo chieu ngang
	for (int i=0;i<Rows;i++)
	{
		for (int j=0;j<Cols-1;j++)
		{
			if (board[i][j]==board[i][j+1] && board[i][j]!=0 )
			{
				return true;
			}
		}
	}
	return false;
}

void merge( Board board,Position idx,SDL_Renderer *renderer, TTF_Font *font)
{
	bool is_merge=false;
	int count=0;
	//kiem tra o duoi cung ben trai
	if (idx.x==Rows-1 && idx.y==0 )
	{
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1])
		{
			count++;
			board[idx.x][idx.y+1]=0;
			is_merge=true;
		}
	}
	//kiem tra o duoi cung ben phai
	else if (idx.x==Rows-1 && idx.y==Cols-1 )
	{
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1])
		{
			count++;
			board[idx.x][idx.y-1]=0;
			is_merge=true;
		}
	}
	//kiem tra hang duoi cung 
	else if (idx.x==Rows-1)
	{
		//kiem tra ve ben tay phai
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1])
		{
			count++;
			board[idx.x][idx.y+1]=0;
			is_merge=true;
		}
		//kiem tra ve ben tay trai
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1])
		{
			count++;
			board[idx.x][idx.y-1]=0;
			is_merge=true;
		}
	}
	//kiem tra cot ngoai cung ben trai
	else if (idx.y==0)
	{
		//kiem tra dong duoi
		if (board[idx.x][idx.y]==board[idx.x+1][idx.y])
		{
			count++;
			board[idx.x+1][idx.y]=0;
			is_merge=true;
		}
		//kiem tra ve ben tay phai
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1])
		{
			count++;
			board[idx.x][idx.y+1]=0;
			is_merge=true;
		}
	}
	//kiem tra cot ngoai cung ben phai
	else if (idx.y==Cols-1)
	{
		//kiem tra dong duoi
		if (board[idx.x][idx.y]==board[idx.x+1][idx.y])
		{
			count++;
			board[idx.x+1][idx.y]=0;
			is_merge=true;
		}
		//kiem tra ve ben tay trai
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1])
		{
			count++;
			board[idx.x][idx.y-1]=0;
			is_merge=true;
		}
	}
	// neu khong phai la truong hop dac biet
	else
	{
		//kiem tra ve ben tay phai
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1])
		{
			count++;
			board[idx.x][idx.y+1]=0;
			is_merge=true;
		}
		//kiem tra ve ben tay trai
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1])
		{
			count++;
			board[idx.x][idx.y-1]=0;
			is_merge=true;
		}
		//kiem tra dong duoi
		if (board[idx.x][idx.y]==board[idx.x+1][idx.y])
		{
			count++;
			board[idx.x+1][idx.y]=0;
			is_merge=true;
		}
	}
	// tang gia tri tai o board[idx.x][idx.y]
	int value=board[idx.x][idx.y];

	for (int i=0;i<count;i++)
	{
		board[idx.x][idx.y]*=2;
	}
	if (is_merge)
	{
		render_game(renderer, board, font);
		// SDL_Delay(200);
	}
	
}

void delete_empty_block (Board board,SDL_Renderer *renderer, TTF_Font *font)
{
	bool is_delete=false;
	for (int i=Rows-1;i>0;i--)
	{
		for (int j=0;j<Cols;j++)
		{
			if (board[i][j]==0 && board[i-1][j]!=0)
			{
				board[i][j]= board[i-1][j];
				board[i-1][j]=0;
				is_delete=true;
			}
		}
	}
	if (is_delete)
	{
		render_game(renderer, board, font);
		// SDL_Delay(200);
	}
}
bool is_continue_merge(Board board,Position &idx)
{
	if (idx.x==Rows-1 && idx.y==0 )
	{
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1] && board[idx.x][idx.y]!=0 )
		{
			return true;
		}
	}
	//kiem tra o duoi cung ben phai
	if (idx.x==Rows-1 && idx.y==Cols-1 )
	{
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1] && board[idx.x][idx.y]!=0 )
		{
			return true;
		}
	}
	//kiem tra hang duoi cung 
	if (idx.x==Rows-1)
	{
		//kiem tra ve ben tay phai
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1] && board[idx.x][idx.y]!=0)
		{
			return true;
		}
		//kiem tra ve ben tay trai
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1] && board[idx.x][idx.y]!=0)
		{
			return true;
		}
	}
	//kiem tra cot ngoai cung ben trai
	if (idx.y==0)
	{
		//kiem tra dong duoi
		if (board[idx.x][idx.y]==board[idx.x+1][idx.y] && board[idx.x][idx.y]!=0)
		{
			return true;
		}
		//kiem tra ve ben tay phai
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1] && board[idx.x][idx.y]!=0)
		{
			return true;
		}
	}
	//kiem tra cot ngoai cung ben phai
	if (idx.y==Cols-1)
	{
		//kiem tra dong duoi
		if (board[idx.x][idx.y]==board[idx.x+1][idx.y] && board[idx.x][idx.y]!=0 )
		{
			return true;
		}
		//kiem tra ve ben tay trai
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1] && board[idx.x][idx.y]!=0 )
		{
			return true;
		}
	}
	// neu khong phai la truong hop dac biet
	else
	{
		//kiem tra ve ben tay phai
		if (board[idx.x][idx.y]==board[idx.x][idx.y+1] && board[idx.x][idx.y]!=0)
		{
			return true;
		}
		//kiem tra ve ben tay trai
		if (board[idx.x][idx.y]==board[idx.x][idx.y-1] && board[idx.x][idx.y]!=0)
		{
			return true;
		}
		//kiem tra dong duoi
		if (board[idx.x][idx.y]==board[idx.x+1][idx.y] && board[idx.x][idx.y]!=0 )
		{
			return true;
		}
	}
	if (idx.x==Rows-2 && idx.y==0)
	{
		if (board[Rows-1][0]==board[Rows-1][1])
		{
			idx.x++;
			return true;
		}
	}
	if (idx.x==Rows-2 && idx.y==Cols-1)
	{
		if (board[Rows-1][Cols-1]==board[Rows-1][Cols-2] )
		{
			idx.x++;
			return true;
		}
	}
	if (idx.x!=Rows-2 && idx.y==0)
	{
		if (board[idx.x+1][idx.y]==board[idx.x+1][idx.y+1] || board[idx.x+1][idx.y]==board[idx.x+2][idx.y] )
		{
			idx.x++;
			return true;
		}
	}
	if ( idx.x!=Rows-2 && idx.y==Cols-1)
	{
		if (board[idx.x+1][idx.y]==board[idx.x+1][idx.y-1] || board[idx.x+1][idx.y]==board[idx.x+2][idx.y] )
		{
			idx.x++;
			return true;
		}
	}
	if (idx.x == Rows-2 && (board[idx.x+1][idx.y]==board[idx.x+1][idx.y+1] || board[idx.x+1][idx.y]==board[idx.x+1][idx.y-1] ))
	{
		idx.x++;
		return true;
	}
	if (idx.x != Rows-2 )
	{
		if (board[idx.x+1][idx.y]==board[idx.x+1][idx.y+1] || board[idx.x+1][idx.y]==board[idx.x+1][idx.y-1] || board[idx.x+1][idx.y]==board[idx.x+2][idx.y])
		{
			idx.x++;
			return true;
		}
	}
	return false;
}
void display_text(SDL_Renderer *renderer, const char *text, int size)
{
	
	TTF_Font *font = NULL;
	font = TTF_OpenFont(FONT_PATH, size);
	if (font == NULL)
	{
		return;
	}
	SDL_Color white = {0,0,0};
	clear_screen(renderer);
	SDL_Rect rect = {0, BOARD_HEIGHT / 4, BOARD_WIDTH, BOARD_HEIGHT / 2};
	draw_text(renderer, font, text, rect, white);
	SDL_Event e;
	bool quit=false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			
		}
		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(font);
}

void retry(SDL_Renderer *renderer,int size, SDL_Window *window)
{
	TTF_Font *font = NULL;
	font = TTF_OpenFont(FONT_PATH, size);
	if (font == NULL)
	{
		return;
	}
	SDL_Color black = {0,0,0};
	clear_screen(renderer);
	SDL_Rect rect_gameover = {0, BOARD_HEIGHT / 4, BOARD_WIDTH, BOARD_HEIGHT / 2};
	draw_text(renderer, font,"Game Over", rect_gameover, black);

	SDL_Rect rect_retry = {0, (BOARD_HEIGHT / 4 ) + 100, BOARD_WIDTH, (BOARD_HEIGHT / 2) + 100};
	draw_text(renderer, font,"Retry", rect_retry, black);
	SDL_Event e;
	bool quit=false;
	bool retry=false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				int xm=e.motion.x;
                int ym=e.motion.y;
				if (xm>100 && xm<210 && ym > 420 && ym < 470)
				{
					draw_text(renderer, font,"Retry", rect_retry, {255,0,0});
				}
				else
				{
					draw_text(renderer, font,"Retry", rect_retry, black);
				}
			}
			else if (e.type==SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button==SDL_BUTTON_LEFT)
				{
					int xb=e.button.x;
					int yb=e.button.y;
					if (xb>100 && xb<210 && yb > 420 && yb < 470)
					{
						retry=true;
					}
					quit=true;
					break;
				}
			}
		}
		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(font);
	closeSDL(window);
	if (retry)
	{
		newGame();
	}
}
void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect rect, SDL_Color color)
{
	SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, text, color);
	SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_Rect message_rect;

	TTF_SizeText(font, text, &message_rect.w, &message_rect.h);
	message_rect.x = rect.x + rect.w / 2 - message_rect.w / 2;
	message_rect.y = rect.y + rect.h / 2 - message_rect.h / 2;

	SDL_RenderCopy(renderer, Message, NULL, &message_rect);
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}

void draw_white_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect rect)
{
	SDL_Color White = {255, 255, 255};
	draw_text(renderer, font, text, rect, White);
}
void newGame()
{
	Board board={0};
	
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	if (!initSDL(&window, &renderer))
	{
		return;
	}
	game_loop(board, renderer,window);
	closeSDL(window);
}