#include <stdio.h>

int fTheFunction(int x,int functionNumber);
void drawFunction(int xAxis,int yAxis,int functionNumber);

int main()
{
	int result;
	
	result = fTheFunction(4,1);
	drawFunction(40,40,1);
	
	printf("Result is %d.\n",result);
	
	return 0;
}

int fTheFunction(int x,int functionNumber)
{
	switch(functionNumber)
	{
		case 1 : return 2*x;
		break;
		
		case 2 : return x;
		break;
	}
}

void drawFunction(int xAxis,int yAxis,int functionNumber)
{
	int i,j,k,l,x,space;
	
	for (i = 0; fTheFunction(i,1) <= yAxis; ++i); /*	i burada yAxisi hesaplamak i�in kullan�ld�. Her fonksiyonda (x*2 mesela) farkl� sonu� ��kaca�� i�in for kulland�.  */

	space = (yAxis/ i);								/* space her sat�r aras�ndaki fonksiyona ba�l� (fTheFunction) bo�lu�u g�sterir. */

	x = i;								/*    i de�eri korunmas� i�in x e atand�.  */
	
	for (j = 0; j < i + 1; ++j)
	{
		printf("|");
		for (k = 0; k < x; ++k)			/* x her sat�rda b�rak�lmas� gereken bo�luk say�s�d�r. */
		{
			printf(" ");
		}

		printf("*\n");

		for (l = 0; l < space; ++l)		/*  ka� sat�rda '*' olmayacak sadece bo�luk olacak onu hesaplar. */
		{
			printf("|\n");
		}
		--x;
	}
	
	printf("|");
	
	for(i=0; i < xAxis;++i)			/* en alttaki koordinat� g�sterir. */
	{
		printf("-");
	}
	printf("\n");
}
