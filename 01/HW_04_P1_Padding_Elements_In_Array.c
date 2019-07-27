#include <stdio.h>

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

void copyArray(double inputArr[], int inputArraySize, double outputArr[]);
void shiftArray(double inputArr[],int shiftedSize,int WidthOfMethod);
int main()
{
	double inputArr[] = {5, 6, 7, 8, 9};
	double outputArr[255];
	int outputArraySize = 0;
	int i;

	addPadding(inputArr, 5 , outputArr, &outputArraySize, 4, samePadding);
	for(i = 0; i < outputArraySize; ++i)
	{
		printf("%1.lf",outputArr[i]);
	}
	printf("\n");
	
	addPadding(inputArr, 5 , outputArr, &outputArraySize, 3, zeroPadding);
	for(i = 0; i < outputArraySize; ++i)
	{
		printf("%1.lf",outputArr[i]);
	}
	printf("\n");
	
	addPadding(inputArr, 5 , outputArr, &outputArraySize, 2, halfPadding);
	for(i = 0; i < outputArraySize; ++i)
	{
		printf("%.1lf ",outputArr[i]);
	}
	printf("\n");
	
	return 0;
}

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int))
{
	copyArray(inputArr,inputArraySize,outputArr);
	*outputArraySize = inputArraySize;
	
	shiftArray(outputArr,*outputArraySize,paddingWidth);
	paddingMethod(outputArr,*outputArraySize,paddingWidth);
	*outputArraySize = *outputArraySize+2*paddingWidth;
}

void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i;

	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[i] = 0;
		outputArr[paddingWidth+outputArraySize+i] = 0;
	}
}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i;
	int temp = outputArr[outputArraySize+paddingWidth-1];

	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[paddingWidth+outputArraySize+i] = temp;
	}
}

void halfPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i;
	double temp = outputArr[0]/2;
	double temp2 = outputArr[outputArraySize+paddingWidth-1]/2;

	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[i] = temp;
		outputArr[paddingWidth+outputArraySize+i] = temp2;
	}	
}

void copyArray(double inputArr[], int inputArraySize, double outputArr[])
{
	int i;
	
	for(i = 0; i < inputArraySize; ++i)
	{
		outputArr[i] = inputArr[i];
	}
}

void shiftArray(double inputArr[],int shiftedSize,int WidthOfMethod)
{
	int i;
	
	while( WidthOfMethod > 0 )
	{
		for(i = shiftedSize; i > 0; --i )
		{
			inputArr[i] = inputArr[i-1];
		}
		WidthOfMethod--;
		shiftedSize++;
	} 
}

