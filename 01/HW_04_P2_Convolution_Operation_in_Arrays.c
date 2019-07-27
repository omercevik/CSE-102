#include <stdio.h>

typedef enum _paddingType { ZERO, HALF, SAME } PaddingType;

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);
void shiftArray(double inputArr[],int size,int width);
void copyArray(double inputArr[],double outputArr[],int inputArraySize);

int convolution(double inputArr[], int inputArraySize, double kernelArr[], int kernelArraySize, double outputArr[], int *outputArraySize, int stride, PaddingType padding);

int main()
{
	double inputArr[] = {3, 5, 7, 9, 11, 13, 15};
	double kernelArr[] = {-1, 2, 0.5, 4, 1.7};
	double outputArr[255];
	int outputArrSize = 0;
	int i;
	
	convolution(inputArr, 7, kernelArr, 5, outputArr, &outputArrSize, 1, ZERO);
		
	for (i = 0; i < outputArrSize; ++i)
		{
			printf("%.1lf ",outputArr[i]);
		}
	printf("\n");
	
	return 0;
}

int convolution(double inputArr[], int inputArraySize, double kernelArr[], int kernelArraySize, double outputArr[], int *outputArraySize, int stride, PaddingType padding)
{	
	double outputArrTemp[255],sum = 0;
	int i,j, paddingWidth;
	
	paddingWidth = (kernelArraySize-1)/2;
	
	if ( kernelArraySize > inputArraySize )
	{
		return -1;
	}
	else
	{
		switch(padding)
		{
			case 0 : addPadding(inputArr, inputArraySize , outputArrTemp, outputArraySize, paddingWidth, zeroPadding);
					break;
			case 1 : addPadding(inputArr, inputArraySize , outputArrTemp, outputArraySize, paddingWidth, halfPadding);
					break;
			case 2 : addPadding(inputArr, inputArraySize , outputArrTemp, outputArraySize, paddingWidth, samePadding);
					break;
		}
		
		for (i = 0; i < inputArraySize; i+=stride)
		{
			for ( j = 0; j < kernelArraySize; ++j)
			{	
				sum+=kernelArr[j]*outputArrTemp[j+i];
			}
			outputArr[i]=sum;
			sum=0;
		}

		*outputArraySize = ((inputArraySize-kernelArraySize+2*paddingWidth)/stride)+1;
		
		return 0;
	}
}

void shiftArray(double inputArr[],int size,int width)
{
	int i = 0;
	while( width > 0 )
	{
		for ( i = size; i>0; --i)
		{	
			inputArr[i]=inputArr[i-1];
		}
		size++;
		width--;
	}
}

void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i = 0;

	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[i] = 0;
		outputArr[paddingWidth+outputArraySize+i] = 0;
	}
}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i = 0;
	int temp = outputArr[outputArraySize+paddingWidth-1];

	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[paddingWidth+outputArraySize+i] = temp;
	}
}

void halfPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i = 0;
	double temp = outputArr[0]/2;
	double temp2 = outputArr[outputArraySize+paddingWidth-1]/2;

	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[i] = temp;
		outputArr[paddingWidth+outputArraySize+i] = temp2;
	}
}

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int))
{
	copyArray(inputArr,outputArr,inputArraySize);
	*outputArraySize = inputArraySize;

	shiftArray(outputArr,*outputArraySize,paddingWidth);
	paddingMethod(outputArr,*outputArraySize,paddingWidth);
	*outputArraySize = *outputArraySize+2*paddingWidth;
}

void copyArray(double inputArr[],double outputArr[],int inputArraySize)
{
	int i = 0;
	for (i = 0; i < inputArraySize; ++i)
	{
		outputArr[i] = inputArr[i];
	}
}
