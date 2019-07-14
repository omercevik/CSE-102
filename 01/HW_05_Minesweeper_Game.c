#include <stdio.h>
#define GRIDSIZE 5

typedef enum {mined,empty,flaggedMined,flaggedEmpty,closedEmpty,closedMined}cell;

void printGrid (cell grid[][GRIDSIZE]);
void flagCell(cell grid[][GRIDSIZE], int x, int y);
int isCellEmpty(cell grid[][GRIDSIZE], int x, int y);
int isAllOpen(cell grid[][GRIDSIZE]);
int isCellFlagged(cell grid[][GRIDSIZE], int x, int y);
int isLocationLegal(int x, int y);
void initGrid(cell grid[][GRIDSIZE]);
int openCell(cell grid[][GRIDSIZE], int x, int y);
void printGameOver(cell grid[][GRIDSIZE]);

int main(int argc, char const *argv[])
{
	cell MainGrid[GRIDSIZE][GRIDSIZE];
	int x = 0, y = 0, move = 0;

	initGrid(MainGrid);

	while(1)
	{
		printf("Enter the coordination x and y : ");
		scanf("%d %d",&x,&y);

		if ( openCell(MainGrid,x,y) == -2 )
		{
			printGrid(MainGrid);
			break;
		}

		if ( MainGrid[x][y] == mined )
		{
			printGameOver(MainGrid);
			break;
		}

		printGrid(MainGrid);
		++move;

		if ( isAllOpen(MainGrid) )
		{
			printf("Congratulations! You win the game with %d moves.\n",move );
			break;
		}
	}
	return 0;
}
void printGameOver(cell grid[][GRIDSIZE])
{
	int i = 0, j = 0;

	for (i = 0; i < GRIDSIZE; ++i)
	{
		for (j = 0; j < GRIDSIZE; ++j)
		{
			if ( grid[i][j] == closedMined || grid[i][j] == mined )
			{
				printf("* ");
			}
			else if ( grid[i][j] == flaggedEmpty || grid[i][j] == flaggedMined )
			{
				printf("f ");
			}
			else if ( grid[i][j] == closedEmpty )
			{
				printf(". ");
			}
			else if ( grid[i][j] == empty )
			{
				printf("e ");
			}
		}
		printf("\n");
	}
	printf("\nYou hit the mine!\nGAME OVER\n");
}

int isAllOpen(cell grid[][GRIDSIZE])
{
	int i = 0, j = 0, flagCounter = 0;

	for (i = 0; i < GRIDSIZE; ++i)
	{
		for (j = 0; j < GRIDSIZE; ++j)
		{
			if ( grid[i][j] == closedMined )
			{
				++flagCounter;
			}
		}
	}
	
	if ( flagCounter == 0 )
	{
		return 1;
	}

	for (i = 0; i < GRIDSIZE; ++i)
	{
		for (j = 0; j < GRIDSIZE; ++j)
		{
			if ( grid[i][j] == closedEmpty || grid[i][j] == flaggedEmpty )
			{
				return 0;
			}
		}
	}
	return 1;
}

int openCell(cell grid[][GRIDSIZE], int x, int y)
{
	if ( !isLocationLegal(x,y) )
	{
		return -2;
	}
	char f;

	printf("Do you want to flag ? (Yes : Y/y No : N/n) = ");
	scanf(" %c",&f);

	if ( f == 'y' || f == 'Y' )
	{
		flagCell(grid,x,y);
	}
	else
	{
		if ( grid[x][y] == closedMined )
		{
			grid[x][y] = mined;
		}
		else if ( grid[x][y] == closedEmpty )
		{
			grid[x][y] = empty;

			if ( isLocationLegal(x-1,y-1) && isCellEmpty(grid,x-1,y-1) )
			{
				grid[x-1][y-1] = empty;
			}
			if ( isLocationLegal(x-1,y) && isCellEmpty(grid,x-1,y) )
			{
				grid[x-1][y] = empty;
			}
			if ( isLocationLegal(x-1,y+1) && isCellEmpty(grid,x-1,y+1) )
			{
				grid[x-1][y+1] = empty;
			}
			if ( isLocationLegal(x,y-1) && isCellEmpty(grid,x,y-1) )
			{
				grid[x][y-1] = empty;
			}
			if ( isLocationLegal(x,y+1) && isCellEmpty(grid,x,y+1) )
			{
				grid[x][y+1] = empty;
			}
			if ( isLocationLegal(x+1,y-1) && isCellEmpty(grid,x+1,y-1) )
			{
				grid[x+1][y-1] = empty;
			}
			if ( isLocationLegal(x+1,y) && isCellEmpty(grid,x+1,y) )
			{
				grid[x+1][y] = empty;
			}
			if ( isLocationLegal(x+1,y+1) && isCellEmpty(grid,x+1,y+1) )
			{
				grid[x+1][y+1] = empty;
			}
		}
		else if ( isCellFlagged(grid,x,y) )
		{
			if ( grid[x][y] == flaggedEmpty )
			{
				grid[x][y] = closedEmpty;
			}
			else
			{
				grid[x][y] = closedMined;
			}
		}
	}

	return 1;
}

void flagCell(cell grid[][GRIDSIZE], int x, int y)
{
	if ( grid[x][y] == closedEmpty || grid[x][y] == closedMined )
	{
		if ( grid[x][y] == closedEmpty )
		{
			grid[x][y] = flaggedEmpty;
		}
		else
		{
			grid[x][y] = flaggedMined;
		}
	}
}

int isCellFlagged(cell grid[][GRIDSIZE], int x, int y)
{
	return grid[x][y] == flaggedEmpty || grid[x][y] == flaggedMined ? 1 : 0;
}

int isCellEmpty(cell grid[][GRIDSIZE], int x, int y)
{
	return grid[x][y] == closedEmpty ? 1 : 0;
}

void initGrid(cell grid[][GRIDSIZE])
{
	int i = 0, j = 0, random = 0, random1 = 0;

	for (i = 0; i < GRIDSIZE; ++i)
	{
		for (j = 0; j < GRIDSIZE; ++j)
		{
			if ( j%GRIDSIZE == i && i%GRIDSIZE == j )
			{
				grid[i][j] = closedMined;
			}
			else
			{
				grid[i][j] = closedEmpty;
			}
			printf(". ");
		}
		printf("\n");
	}
	printf("\n");
}

int isLocationLegal(int x, int y)
{
	return x >= GRIDSIZE || x < 0 || y >= GRIDSIZE || y < 0 ? 0 : 1;
}

void printGrid (cell grid[][GRIDSIZE])
{
	int i = 0, j = 0;

	for (i = 0; i < GRIDSIZE; ++i)
	{
		for (j = 0; j < GRIDSIZE; ++j)
		{
			switch(grid[i][j])
			{
				case empty : printf("e ");
				break;

				case closedEmpty : 
				case closedMined : printf(". ");
				break;

				case flaggedEmpty :
				case flaggedMined : printf("f ");
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}