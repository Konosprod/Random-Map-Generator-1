#include "SDL.h"
#include <SDL_image.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>

/*******
 *3 2 1*
 *4   0*
 *5 6 7*
 *******/

int rand_a_b(int a, int b)
{
    int c = rand()%(b-a) +a;
    return c;
}

void init_tab(char tab[][20])
{
	for(int x = 0; x < 20; x++)
	{
		for(int y = 0; y < 20; y++)
		{
			tab[y][x] = 0;
		}
	}
}

void correct_rl(char map[][20])
{
    int x = 0;
    int y = 0;
    int dir = 1;

    while(map[y][x] != 'R')
    {
        x++;
    }
 
    if(map[y][x-1] == 'R')
    {
        dir = 0;
    }
    else
    {
        dir = 1;
    }

    while(y < 20)
    {
        if(dir == 0)
        {
            while((x > 0) && (map[y][x] == 'R'))
            {
                map[y][x] = 2;
                x--;
            }
            x++;
            map[y][x] = 5;
            y++;
            dir = 1;
        }
        else
        {
            while((y < 20) && (map[y][x] == 'R'))
            {
                map[y][x] = 3;
                y++;
            }
            y--;
            map[y][x] = 7;
            x--;
            dir = 0;
        }
    }

    map[y-1][x] = 3;
}

void correct_lr(char map[][20])
{
    int x = 0;
    int y = 0;
    int dir = 1;

    while(map[y][x] != 'R')
    {
        x++;
    }
 
    if(map[y][x+1] == 'R')
    {
        dir = 0;
    }
    else
    {
        dir = 1;
    }

    while(y < 20)
    {
        if(dir == 0)
        {
            while((x < 20) && (map[y][x] == 'R'))
            {
                map[y][x] = 2;
                x++;
            }
            x--;
            map[y][x] = 4;
            y++;
            dir = 1;
        }
        else
        {
            while((y < 20) && (map[y][x] == 'R'))
            {
                map[y][x] = 3;
                y++;
            }
            y--;
            map[y][x] = 6;
            x++;
            dir = 0;
        }
    }
   
    map[y-1][x] = 3;
}

void gen_river_rl(char tab[][20])
{
    int x = rand_a_b(16, 20);
	int y = 0;

	while(tab[y][x] != 0)
	{
		x = rand_a_b(0, 20);
	}


	tab[y][x] = 'R';

	while(y < 19)
	{
		switch(rand_a_b(0, 2))
		{
			case 1:
				y++;
			break;

			case 0:
				if(x-1 > 0)
				{
					x--;
				}
				else
				{
					y++;
				}
			break;
		}
		
		if(tab[y][x] == 0 || tab[y][x] == 'W')
		{
			tab[y][x] = 'R';
		}
	}

    correct_rl(tab);
}

void gen_river_lr(char tab[][20])
{
    int x = rand_a_b(0, 4);
	int y = 0;

	while(tab[y][x] != 0)
	{
		x = rand_a_b(0, 20);
	}


	tab[y][x] = 'R';

	while(y < 19)
	{
		switch(rand_a_b(0, 2))
		{
			case 0:
				if(x+1 < 20)
				{
					x++;
				}
				else
				{
					y++;
				}
			break;

			case 1:
				y++;
			break;
		}
		
		if(tab[y][x] == 0 || tab[y][x] == 'W')
		{
			tab[y][x] = 'R';
		}
	}

    correct_lr(tab);
}

int fill_trees(char tab[][20], int x, int y, int percent)
{
    if(((x+1) < 20) && ((y+1) < 20) && percent > 0)
	{
		if(tab[y+1][x+1] == 0)
		{
			tab[y+1][x+1] = 8;
			percent--;
		}
	}
	if(((x-1) >= 0) && ((y-1) >= 0) && percent > 0)
	{
		if(tab[y-1][x-1] == 0)
		{
			tab[y-1][x-1] = 8;
			percent--;
		}
	}
	if((x+1) < 20 && percent > 0)
	{
		if(tab[y][x+1] == 0)
		{
			tab[y][x+1] = 8;
			percent--;
		}
	}
	if((x-1) >= 0 && percent > 0)
	{
		if(tab[y][x-1] == 0)
		{
			tab[y][x-1] = 8;
			percent--;
		}
	}
	if((y+1) < 20 && percent > 0)
	{
		if(tab[y+1][x] == 0)
		{
			tab[y+1][x] = 8;
			percent--;
		}
	}
	if((y-1) >= 0 && percent > 0)
	{
		if(tab[y-1][x] == 0)
		{
			tab[y-1][x] = 8;
			percent--;
		}
	}
	if(((x+1) < 20) && ((y-1) >= 0) && percent > 0)
	{
		if(tab[y-1][x+1] == 0)
		{
			tab[y-1][x+1] = 8;
			percent--;
		}
	}
	if(((x-1) >= 0) && ((y+1) < 20) && percent > 0)
	{
		if(tab[y+1][x-1] == 0)
		{
			tab[y+1][x-1] = 8;
			percent--;
		}
	}

	return percent;
}

void gen_trees(char tab[][20], int percent)
{
    int x = 0;
    int y = 0;
    int p = percent;

    while(p != 0)
    {
        x = rand_a_b(0, 20);
        y = rand_a_b(0, 20);

        if(tab[y][x] == 0)
        {
            tab[y][x] = 8;
            p--;
        }
        p = fill_trees(tab, x, y, p);
    }
}

void gen_rocks(char tab[][20], int percent)
{
    int x = 0;
    int y = 0;

    while(percent != 0)
    {
        x = rand_a_b(0, 20);
        y = rand_a_b(0, 20);

        if(tab[y][x] == 0)
        {
            tab[y][x] = 1;
            percent--;
        }
    }
}


void pause(void)
{
    int continuer = 1;
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_QUIT: 
                continuer=0;
            break;
        }
    }
}

void draw_map(char map[][20], SDL_Surface* tiles[])
{
    SDL_Surface* ecran = SDL_GetVideoSurface();
    SDL_Rect pos;

    pos.x = 0;
    pos.y = 0;

    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            pos.x = j*32;
            pos.y = i*32;
            SDL_BlitSurface(tiles[map[i][j]], NULL, ecran, &pos);
        }
    }

}

void gen_random_map(char map[][20])
{
    init_tab(map);
    switch(rand_a_b(0, 2))
	{
		case 0:
			gen_river_lr(map);
		break;

		case 1:
			gen_river_rl(map);
		break;
	}
    gen_trees(map, 40);
    gen_rocks(map, 20);
}

int main( int argc, char* args[] )
{ 
    SDL_Surface* ecran = NULL;
    SDL_Surface* tiles[9] = {NULL};
    char map[20][20] = {{0}};

    srand(time(NULL));

    if((tiles[0] = IMG_Load("grass.png")) == NULL)
    {
        printf("Fuck this shit\n");
    }
    tiles[1] = IMG_Load("roc.png");
    tiles[2] = IMG_Load("riverh.png");
    tiles[3] = IMG_Load("riverv.png");
    tiles[4] = IMG_Load("rdcorner.png");
    tiles[5] = IMG_Load("ldcorner.png");
    tiles[6] = IMG_Load("drcorner.png");
    tiles[7] = IMG_Load("dlcorner.png");
    tiles[8] = IMG_Load("tree.png");

    SDL_Init(SDL_INIT_EVERYTHING);
    ecran = SDL_SetVideoMode(640, 640, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    gen_random_map(map);

    draw_map(map, tiles);
    SDL_Flip(ecran);

    pause();

    for(int i = 0; i < 9; i++)
    {
        SDL_FreeSurface(tiles[i]);
    }
    return 0; 
}