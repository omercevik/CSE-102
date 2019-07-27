#include <stdio.h>

int theAge(int day,int month, int year, int today,int this_month, int this_year );
int daysLeft(int day,int month, int today,int this_month);

int main()
{
	int ageOfUser,days;
	
	ageOfUser = theAge(4,7,1984,22,2,2017);
	days = daysLeft(4,7,22,2);
	
	printf("Age of user is %d.\n",ageOfUser);
	printf("%d days left to user's birthday.\n",days);
	
	return 0;
}

int theAge(int day,int month, int year, int today,int this_month, int this_year )
{
	return (((this_year*365)+(this_month*30)+today)-((year*365)+(month*30)+day))/365;
}

int daysLeft(int day,int month, int today,int this_month)
{
	return (((month*30)+day)-((this_month*30)+today)+365)%365;
}
