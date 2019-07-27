#include <stdio.h>

void drawRectangle(int width,int height, int startingPoint, int printLastLine);
void drawDoubleCircle(int radius, int startingPoint , int whellDistance);
void drawCar();

int main()
{
	drawCar();
	return 0;
}

void drawRectangle(int width,int height, int startingPoint, int printLastLine)
{
	int i,j,k,l;
	
	for(i = 0; i < startingPoint-1; i++)
	{
		printf(" ");
	}
	
	for(j = 0; j < height; ++j)
	{
		printf("*");
	}
	printf("\n");
	
	while( width > 1 )
	{
		for(k = 0; k < startingPoint-1; k++)
		{
			printf(" ");
		}
		printf("*");
		for(l = 2; l < height; ++l)
		{
			printf(" ");
		}
		printf("*\n");
		
		width--;
	}
	for(i = 0; i < startingPoint && printLastLine; i++)
	{
		printf(" ");
	}
	
	for(i = 0; i < height && printLastLine; ++i)
	{
		printf("*");
	}
	if(printLastLine == 1)
	{
		printf("\n");
	}
} 

void drawDoubleCircle(int radius, int startingPoint , int whellDistance)
{
	int i,j,k;
	
	k = 2*radius;
	
	while( k > -1 )
	{
		if ( k == 4 )
		{
			for(i = 0; i < startingPoint+1; i++)
			{
				printf(" ");
			}
			for(i = 0; i < startingPoint+2; i++)
			{
				printf("* ");
			}
			for(j = 0; j < whellDistance; j++)
			{
				printf(" ");
			}
			for(i = 0; i < startingPoint+2; i++)
			{
				printf("* ");
			}
			printf("\n");
		}
		
		if ( k == 5 || k == 6 || k == 3 || k == 2 )
		{
			for(i = 0; i < startingPoint+3; i++)
			{
				printf(" ");
			}
			for(i = 0; i < startingPoint; i++)
			{
				printf("* ");
			}
			for(j = 0; j < whellDistance+4; j++)
			{
				printf(" ");
			}
			for(i = 0; i < startingPoint; i++)
			{
				printf("* ");
			}
			printf("\n");
		}
		
		if ( k == 1 || k == 7 )
		{
			for(i = 0; i < startingPoint+5; i++)
			{
				printf(" ");
			}
			for(i = 0; i < startingPoint-2; i++)
			{
				printf("* ");
			}
			for(j = 0; j < whellDistance+8; j++)
			{
				printf(" ");
			}
			for(i = 0; i < startingPoint-2; i++)
			{
				printf("* ");
			}
			printf("\n");
		}
		if ( k == 8 || k == 0 )
		{
			for(i = 0; i < startingPoint+1; i++)
			{
				printf("  ");
			}
			printf("* ");
			
			for(j = 0; j < whellDistance+2; j++)
			{
				printf("  ");
			}
			printf("*\n");
		}
		
		k--;
	}
}

void drawCar()
{
	drawRectangle (10,40,11,0);
	drawRectangle (10,60,0,1);
	drawDoubleCircle(4, 7 ,12);
}
