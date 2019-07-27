#include <stdio.h>
#define PI 3.14

float diameter(float circumference);
float ageOfTree(float diameter , float growth_factor);

int main()
{
	float dia;
	dia = diameter(60.5);
	float age;
	age = ageOfTree(diameter(60.5), 4.5);
	
	printf("Diameter of tree is %.2f.\n",dia);
	printf("Age of tree is %.2f.\n",age);
	
	return 0;
}

float diameter(float circumference)
{
	return circumference/PI;
}
float ageOfTree(float diameter , float growth_factor)
{
	return growth_factor*diameter;
}
