#include <stdio.h>

int isPrime(int num);
int goldbach(int num, int *p1, int *p2);

int main()
{
	int num = 824, p1, p2;
	if(goldbach(num,&p1,&p2))
		printf("%d = %d + %d",num,p1,p2); /* may print 824 = 821 + 3 */
	else
		printf("You should provide even number.");
	
	return 0;
}

int isPrime(int num)
{
	int j;
	
	if(num < 2)
	{
		return 0;
	}
	
	for(j = 2; j < num/2; j++)
	{
		if( num%j == 0 )
		{
			return 0;
		}
	}
	return 1;
}

int goldbach(int num, int *p1, int *p2)
{
	int partOfNum;
	
	if( num % 2 != 0 )
	{
		return 0;
	}
	
	for( partOfNum = 3; partOfNum <= num/2; partOfNum)
	{
		if( isPrime(partOfNum) && isPrime(num - partOfNum) )
		{
			*p1 = num - partOfNum;
			*p2 = partOfNum;
			
			return 1;
		}
	}
}
