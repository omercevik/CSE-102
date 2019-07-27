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
	
	for (i = 0; fTheFunction(i,1) <= yAxis; ++i); /*	i burada yAxisi hesaplamak için kullanýldý. Her fonksiyonda (x*2 mesela) farklý sonuç çýkacaðý için for kullandý.  */

	space = (yAxis/ i);								/* space her satýr arasýndaki fonksiyona baðlý (fTheFunction) boþluðu gösterir. */

	x = i;								/*    i deðeri korunmasý için x e atandý.  */
	
	for (j = 0; j < i + 1; ++j)
	{
		printf("|");
		for (k = 0; k < x; ++k)			/* x her satýrda býrakýlmasý gereken boþluk sayýsýdýr. */
		{
			printf(" ");
		}

		printf("*\n");

		for (l = 0; l < space; ++l)		/*  kaç satýrda '*' olmayacak sadece boþluk olacak onu hesaplar. */
		{
			printf("|\n");
		}
		--x;
	}
	
	printf("|");
	
	for(i=0; i < xAxis;++i)			/* en alttaki koordinatý gösterir. */
	{
		printf("-");
	}
	printf("\n");
}
