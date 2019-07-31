/*
    CSE 102 Computer Programming
    OMER CEVIK
    161044004
    Homework 07
*/
#include <stdio.h>

#define MAX_WEIGHT 99999
#define SHORTEST_DAMAGE 4
#define COMFORTABLE_DAMAGE 2
#define SAFEST_DAMAGE 6
#define TOTAL_LIFE 40 // can change for different tests


typedef enum _tileType {BORDER, WALL, EMPTY, USED, START} TILE_TYPE;
typedef enum _pathType {DISTANCE, COMFORT, DANGER} PATH_TYPE;
typedef enum _printType {P_DISTANCE, P_COMFORT, P_DANGER, P_TRAP} PRINT_TYPE;

typedef struct _tiles{
	TILE_TYPE type;
	int distance;
	int dangerLevel;
	int comfortLevel;
	int trapDamage;
}TILES;

typedef struct _coord{
	int x;
	int y;
}Coord;

typedef struct _path{
	Coord coords[200];
	int size;
	int totalDistance;
	int totalDanger;
	int totalComfort;
	int totalDamage;
}Path;

/*starter functions*/
int testMaze(char * fileName, Coord startTile, PATH_TYPE pType);
void readMaze(TILES maze[100][100], char * fileName, int *w, int *h);
void printMaze(TILES maze[100][100], int a, int b);
void printMazeWithValues(TILES maze[100][100], int a, int b, PRINT_TYPE pType);
void printAll(TILES maze[100][100], int a, int b);
void markPath(TILES maze[100][100], Path path);
void clearBoard(TILES maze[100][100]);

/*Required*/
int isStuck(TILES maze[100][100], Coord currentTile);
int isExit(TILES maze[100][100], Coord currentTile);
Path shortestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);
Path comfortableExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);
Path safestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);

/*Optional*/
void addCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType);
void removeLastCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType);


int testMaze(char * fileName, Coord startTile, PATH_TYPE pType)
{
	int w = 0, h = 0;
	Path path, resultPath;
	int result = 0;

	TILES maze[100][100];
	int minWeight = MAX_WEIGHT;

	printf("Board name: %s\n", fileName);

	readMaze(maze, fileName, &w, &h);
    path.size = 0;
    maze[startTile.x][startTile.y].type = START;

	switch(pType)
    {
		case DISTANCE:
            resultPath = shortestExit(maze, startTile, path, &minWeight);
            markPath(maze, resultPath);
			printf("Shortest Path\n");
			result = resultPath.totalDistance;
			printMazeWithValues(maze, w, h, P_DISTANCE);
			break;
		case COMFORT:
            resultPath = comfortableExit(maze,startTile,path,&minWeight);
            markPath(maze, resultPath);
			printf("Comfortable Path\n");
			result = resultPath.totalComfort;
			printMazeWithValues(maze, w, h, P_COMFORT);
			break;
		case DANGER:
            resultPath = safestExit(maze,startTile,path,&minWeight);
            markPath(maze, resultPath);
			printf("Safest Path\n");
			result = resultPath.totalDanger;
			printMazeWithValues(maze, w, h, P_DANGER);
			break;
	}

	printMaze(maze, w, h);

	printf("Total weight: %d\n", result);
	printf("-------------------------------------\n");
	return result;
}

/*marks path tiles as USED for printing*/
void markPath(TILES maze[100][100], Path path)
{
	int i = 0;

	for (i = 0; i < path.size; ++i){
		maze[path.coords[i].x][path.coords[i].y].type = USED;
	}
}

void readMaze(TILES maze[100][100], char * fileName, int *w, int *h)
{
	int i = 0, j = 0, tile = 0, distance, comfort, danger, trap;
	FILE *fp = fopen (fileName, "r");

	clearBoard(maze);

	fscanf(fp, "%d", w);
	fscanf(fp, "%d", h);

	/* Tile type*/
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &tile);
			switch(tile){
				case 0:
					maze[i][j].type = EMPTY;
					break;
				case 1:
					maze[i][j].type = WALL;
					break;
				case 2:
					maze[i][j].type = USED;
					break;
				case 3:
					maze[i][j].type = BORDER;
					break;
			}
		}
	}

	fscanf(fp, "%d", &distance);/*useless seperator*/

	/* distance values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &distance);
			maze[i][j].distance = distance;
		}
	}

	fscanf(fp, "%d", &comfort);/*useless seperator*/

	/* comfort values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &comfort);
			maze[i][j].comfortLevel = comfort;
		}
	}
	fscanf(fp, "%d", &danger);/*useless seperator*/

	/* danger values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &danger);
			maze[i][j].dangerLevel = danger;
		}
	}

	/* trap values */
	fscanf(fp, "%d", &trap);/*useless seperator*/

	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &trap);
			maze[i][j].trapDamage = trap;
		}
	}

	fclose(fp);
}

void printMaze(TILES maze[100][100], int a, int b)
{
	int i = 0, j = 0;

	printf("  ");
	for (j = 0; j < b; ++j){
		printf("%d ", j%10);
	}
	printf("\n");

	for (i = 0; i < a; ++i){
		printf("%d ", i%10);
		for (j = 0; j < b; ++j){
			switch(maze[i][j].type){
				case EMPTY:
					printf("  ");
					break;
				case WALL:
					printf("W ");
					break;
				case USED:
					printf(". ");
					break;
				case BORDER:
					printf("B ");
					break;
				case START:
					printf("* ");
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printMazeWithValues(TILES maze[100][100], int a, int b, PRINT_TYPE pType)
{
	int i = 0, j = 0;

	printf("  ");
	for (j = 0; j < b; ++j){
		printf("%d ", j%10);
	}
	printf("\n");

	for (i = 0; i < a; ++i){
		printf("%d ", i%10);
		for (j = 0; j < b; ++j){
			if(maze[i][j].type == EMPTY || maze[i][j].type == USED || maze[i][j].type == START){
				if(pType == P_DISTANCE)
					printf("%d ", maze[i][j].distance);
				else if(pType == P_COMFORT)
					printf("%d ", maze[i][j].comfortLevel);
				else if(pType == P_DANGER)
					printf("%d ", maze[i][j].dangerLevel);
				else
					printf("%d ", maze[i][j].trapDamage);
			}else if(maze[i][j].type == BORDER){
				printf("B ");
			}else{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printAll(TILES maze[100][100], int a, int b)
{
	printf("Distance Map:\n");
	printMazeWithValues(maze, a, b, P_DISTANCE);
	printf("Comfort Map:\n");
	printMazeWithValues(maze, a, b, P_COMFORT);
	printf("Danger Map:\n");
	printMazeWithValues(maze, a, b, P_DANGER);
	printf("Trap Map:\n");
	printMazeWithValues(maze, a, b, P_TRAP);
	printf("Path:\n");
	printMaze(maze, a, b);
}

void clearBoard(TILES maze[100][100])
{
	int i = 0, j = 0;

	for (i = 0; i < 100; ++i){
		for (j = 0; j < 100; ++j){
			maze[i][j].type = BORDER;
		}
	}
}

/***********************************************************/

int isStuck(TILES maze[100][100], Coord currentTile)
{
	if ((maze[currentTile.x][currentTile.y+1].type == WALL || maze[currentTile.x][currentTile.y+1].type == USED)
        && (maze[currentTile.x-1][currentTile.y].type == WALL || maze[currentTile.x-1][currentTile.y].type == USED)
        && (maze[currentTile.x+1][currentTile.y].type == WALL || maze[currentTile.x+1][currentTile.y].type == USED)
        && maze[currentTile.x][currentTile.y-1].type == USED)
    {
        return 1;
    }
    else if ((maze[currentTile.x][currentTile.y-1].type == WALL || maze[currentTile.x][currentTile.y-1].type == USED)
        && (maze[currentTile.x-1][currentTile.y].type == WALL || maze[currentTile.x-1][currentTile.y].type == USED)
        && (maze[currentTile.x+1][currentTile.y].type == WALL || maze[currentTile.x+1][currentTile.y].type == USED)
        && maze[currentTile.x][currentTile.y+1].type == USED)
    {
        return 1;
    }
    else if ((maze[currentTile.x-1][currentTile.y].type == WALL || maze[currentTile.x-1][currentTile.y].type == USED)
        && (maze[currentTile.x][currentTile.y-1].type == WALL || maze[currentTile.x][currentTile.y-1].type == USED)
        && (maze[currentTile.x][currentTile.y+1].type == WALL || maze[currentTile.x][currentTile.y+1].type == USED)
        && maze[currentTile.x+1][currentTile.y].type == USED)
    {
        return 1;
    }
    else if ((maze[currentTile.x+1][currentTile.y].type == WALL || maze[currentTile.x+1][currentTile.y].type == USED)
        && (maze[currentTile.x][currentTile.y-1].type == WALL || maze[currentTile.x][currentTile.y-1].type == USED)
        && (maze[currentTile.x][currentTile.y+1].type == WALL || maze[currentTile.x][currentTile.y+1].type == USED)
        && maze[currentTile.x-1][currentTile.y].type == USED)
    {
        return 1;
    }
    return 0;
}

int isExit(TILES maze[100][100], Coord currentTile)
{
	return (maze[currentTile.x][currentTile.y+1].type == BORDER) || (maze[currentTile.x][currentTile.y-1].type == BORDER) ||
           (maze[currentTile.x+1][currentTile.y].type == BORDER) || (maze[currentTile.x-1][currentTile.y].type == BORDER) ? 1 : 0;
}

Path shortestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight)
{
    if (maze[currentTile.x][currentTile.y].type != START)
    {
        maze[currentTile.x][currentTile.y].type = USED;
    }
    path.totalDistance += maze[currentTile.x][currentTile.y].distance;
    path.totalDamage += maze[currentTile.x][currentTile.y].trapDamage;
    path.totalDamage += SHORTEST_DAMAGE;

	if (isExit(maze,currentTile))
    {
        if (*minWeight > path.totalDistance && TOTAL_LIFE > path.totalDamage)
        {
            *minWeight = path.totalDistance;
        }
        if (path.size > 0)
        {
            path.totalDistance = 0;
            path.totalDamage = 0;
            return shortestExit(maze,path.coords[--path.size],path,minWeight);
        }
        return path;
    }
    else if (isStuck(maze,currentTile))
    {
        if (path.size > 0)
        {
            return shortestExit(maze,path.coords[--path.size],path,minWeight);
        }
        path.totalDistance = *minWeight;
        return path;
    }
    else if ( maze[currentTile.x-1][currentTile.y].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x][currentTile.y-1].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x-1;
        nextTile.y = currentTile.y;
        return shortestExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x+1][currentTile.y].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x][currentTile.y-1].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x+1;
        nextTile.y = currentTile.y;
        return shortestExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x][currentTile.y-1].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x;
        nextTile.y = currentTile.y-1;
        return shortestExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x][currentTile.y+1].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y-1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x;
        nextTile.y = currentTile.y+1;
        return shortestExit(maze,nextTile,path,minWeight);
    }
}

Path comfortableExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight)
{
	if (maze[currentTile.x][currentTile.y].type != START)
    {
        maze[currentTile.x][currentTile.y].type = USED;
    }
    path.totalComfort += maze[currentTile.x][currentTile.y].comfortLevel;
    path.totalDamage += maze[currentTile.x][currentTile.y].trapDamage;
    path.totalDamage += COMFORTABLE_DAMAGE;

    if (isExit(maze,currentTile))
    {
        if (*minWeight > path.totalComfort && TOTAL_LIFE > path.totalDamage)
        {
            *minWeight = path.totalComfort;
        }
        if (path.size > 0)
        {
            path.totalComfort = 0;
            path.totalDamage = 0;
            return comfortableExit(maze,path.coords[--path.size],path,minWeight);
        }
        return path;
    }
    else if (isStuck(maze,currentTile))
    {
        if (path.size > 0)
        {
            return comfortableExit(maze,path.coords[--path.size],path,minWeight);
        }
        path.totalComfort = *minWeight;
        return path;
    }
    else if ( maze[currentTile.x-1][currentTile.y].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x][currentTile.y-1].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x-1;
        nextTile.y = currentTile.y;
        return comfortableExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x+1][currentTile.y].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x][currentTile.y-1].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x+1;
        nextTile.y = currentTile.y;
        return comfortableExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x][currentTile.y-1].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x;
        nextTile.y = currentTile.y-1;
        return comfortableExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x][currentTile.y+1].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y-1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x;
        nextTile.y = currentTile.y+1;
        return comfortableExit(maze,nextTile,path,minWeight);
    }
}

Path safestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight)
{
	if (maze[currentTile.x][currentTile.y].type != START)
    {
        maze[currentTile.x][currentTile.y].type = USED;
    }
    path.totalDanger += maze[currentTile.x][currentTile.y].dangerLevel;
    path.totalDamage += maze[currentTile.x][currentTile.y].trapDamage;
    path.totalDamage += SAFEST_DAMAGE;

    if (isExit(maze,currentTile))
    {
        if (*minWeight > path.totalDanger && TOTAL_LIFE > path.totalDamage)
        {
            *minWeight = path.totalDanger;
        }
        if (path.size > 0)
        {
            path.totalDanger = 0;
            path.totalDamage = 0;
            return safestExit(maze,path.coords[--path.size],path,minWeight);
        }
        return path;
    }
    else if (isStuck(maze,currentTile))
    {
        if (path.size > 0)
        {
            return safestExit(maze,path.coords[--path.size],path,minWeight);
        }
        path.totalDanger = *minWeight;
        return path;
    }
    else if ( maze[currentTile.x-1][currentTile.y].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x][currentTile.y-1].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x-1;
        nextTile.y = currentTile.y;
        return safestExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x+1][currentTile.y].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x][currentTile.y-1].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x+1;
        nextTile.y = currentTile.y;
        return safestExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x][currentTile.y-1].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y+1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x;
        nextTile.y = currentTile.y-1;
        return safestExit(maze,nextTile,path,minWeight);
    }
    else if ( maze[currentTile.x][currentTile.y+1].type == EMPTY )
    {
        if (maze[currentTile.x][currentTile.y-1].type == EMPTY || maze[currentTile.x-1][currentTile.y].type == EMPTY ||
            maze[currentTile.x+1][currentTile.y].type == EMPTY)
        {
            path.coords[path.size].x = currentTile.x;
            path.coords[path.size++].y = currentTile.y;
        }
        Coord nextTile;
        nextTile.x = currentTile.x;
        nextTile.y = currentTile.y+1;
        return safestExit(maze,nextTile,path,minWeight);
    }
}

int main()
{
	Coord startTile1;
	startTile1.x = 5;
	startTile1.y = 2;

	testMaze("maze1.txt", startTile1, DISTANCE);
	testMaze("maze1.txt", startTile1, COMFORT);
	testMaze("maze1.txt", startTile1, DANGER);

	return 0;
}
