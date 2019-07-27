#include <stdio.h>

int charge(int cardType, int* monthlyUse, double* balance);

int main()
{
	int monthlyUse = 120;
	double balance = 20.0;
	
	if(!(charge(1,&monthlyUse, &balance) < 0))
		printf("Remaining monthly use: %d – Remaining Balance: %.2f\n",monthlyUse,balance);
	else
		printf("Insufficient balance.");
	
	return 0;
}

int charge(int cardType, int* monthlyUse, double* balance)
{
	if( *balance < 0 )
	{
		return -1;
	}
	
	if( *monthlyUse > 0 )
	{
		(*monthlyUse)--;
	}
	else
	{
		switch(cardType)
		{
			case 0 : *balance -= 2.30;
			break;
			
			case 1 : *balance -= 1.15;
			break;
			
			case 2 : *balance -= 1.65;
			break;
			
			default : return -2;
			break;
		}
	}
	return 0;
}
