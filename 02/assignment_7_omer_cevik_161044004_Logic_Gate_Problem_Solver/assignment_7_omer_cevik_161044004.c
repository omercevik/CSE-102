/*
											CSE 102 Homework Assignment 7

												OMER_CEVIK_161044004


					# 				In that programme, we read two text files.					 #
					# 				   One of them is about a logic problem.				     #
					#					The other one is input variables. 						 # 
					#				We try to solve that logic with inputs.						 #


																															*/
#include <stdio.h>		/* We use fscanf, printf, if, else, for etc.	*/
#include <stdlib.h>		/* We use dynamic allocation functions.			*/
#include <string.h>		/* We use strlen, strcmp etc.					*/

struct logic{					/* It's our gate struct.								*/
	int *result;				/* We use it to save our result of gates.				*/
	int temp1,					/* We use it to save our result of AND gate.			*/
		temp2,					/* We use it to save our result of OR gate.				*/
		temp3,					/* We use it to save our result of NOT gate.			*/
		temp4,					/* We use it to save our result of FLIPFLOP gate.		*/
		temp;					/* We use it to save our result of logic.				*/
	int former_out;				/* It's our former-out special to FLIPFLOP gate.		*/
	char Input[10];				/* It saves Input strings.								*/
	char AndGates[10];			/* It saves And gate strings.							*/
	char OrGates[10];			/* It saves Or gate strings.							*/
	char NotGates[10];			/* It saves Not gate strings.							*/
	char FlipflopGates[10];		/* It saves Flipflop gate strings.						*/
};

int ReadCircuitFile(char *CircuitFile, char ***CircuitArray);			/* We read circuit.txt into the char array.		*/
int ReadInputFile(char *InputFile, int InputValues[][200][250]);		/* We read input.txt into the int array.		*/
int FindingLogicOperators(char **Circuit, struct logic **gate, int *InputSize, int CounterCircuit);			/* We find gates and save them.	*/
int LogicSolving(struct logic *gate, char **Circuit, int Value[200][250], int ValueCounter, int SizeC);		/* We calculate the logic.		*/

int main()				/* We call our functions.	*/
{
	struct logic *GATE = NULL;		/* We initialize our gate.				*/
	char **Circuit = NULL;			/* We declare our Circuit array.		*/
	int Values[200][250];			/* We declare our Input array.			*/
	int i = 0,						/* It's just a counter.					*/
		CounterValues = 0,			/* It saves size of Inputs.				*/
		CounterCircuit = 0,			/* It saves columns size of Circuits.	*/
		SizeOfColumn = 0,			/* It saves columns size of Inputs.		*/
		InputSize = 0;				/* It saves columns size of Inputs.		*/

	CounterCircuit = ReadCircuitFile("circuit.txt",&Circuit);							/* We read circuit.txt into the Circuit array. We save the return value.	*/

	CounterValues =	ReadInputFile("input.txt",&Values);									/* We read input.txt into the Value array. We save the return value.		*/

	SizeOfColumn = FindingLogicOperators(Circuit,&GATE,&InputSize,CounterCircuit);		/* We find the gates and save the return value.								*/

	for (i = 0; i < CounterValues; ++i)													/* We make a loop to calculate logic for all inputs.						*/
	{
		printf("%d\n",LogicSolving(GATE,Circuit,&Values[i],InputSize,SizeOfColumn));	/* We calculate logic then we print the results to screen.	*/
	}

	for (i = 0; i < CounterCircuit; ++i)			/* We start a loop to free.		*/
	{
		free(Circuit[i]);							/* We free Circuit array.		*/
	}		
	free(Circuit);									/* We free Circuit 2D array.	*/

	free(GATE);		/* We free our gates.		*/

	return 0;		/* Ending our story truely.	*/
}

int ReadCircuitFile(char *CircuitFile, char ***CircuitArray)	/* We read our circuit.txt file.		*/
{
	FILE *fp = fopen(CircuitFile,"r");									/* We open our text file.				*/

	int i = 0, j = 0;													/* They are just counters.				*/
	char c;																/* We use it to scan.					*/

	while( fscanf(fp,"%c",&c) != EOF )									/* We start a loop to scan the file.	*/
	{
		*CircuitArray = (char**)realloc(*CircuitArray,sizeof(char*)*(j+1));				/* We allocate dynammical for 2D char array.	*/
		(*CircuitArray)[j] = (char*)realloc((*CircuitArray)[j],sizeof(char)*(i+1));		/* We allocate dynammical for char array.		*/

		if ( c == '\n' )					/* If we found a new line character then we make a string array.	*/ 
		{
			(*CircuitArray)[j][i] = '\0';	/* We put a null character end of string.							*/
			++j;							/* New array.														*/
			i = 0;							/* We re-initialize our counter.									*/
			continue;						/* We go back to scanning.											*/ 
		}

		(*CircuitArray)[j][i] = c;			/* We assign character to our array.								*/

		++i;								/* We count characters.												*/
	}

	(*CircuitArray)[j] = (char*)realloc((*CircuitArray)[j],sizeof(char)*(i+1));		/* We allocate dynammical for last character.	*/

	(*CircuitArray)[j][i] = '\0';			/* We put the null character to end of array.						*/					

	fclose(fp);								/* We close our file.												*/

	return j+1;								/* We return how many columns that we have in circuit.				*/
}

int ReadInputFile(char *InputFile, int InputValues[][200][250])		/* We read our input.txt file.				*/
{
	FILE *fp = fopen(InputFile,"r");								/* We open our text file.					*/

	int i = 0, j = 0;												/* They are just counters.					*/
	char c;															/* We use it to scan.						*/

	while( fscanf(fp,"%c",&c) != EOF )								/* We start a loop to scan the file.		*/
	{
		if ( c == '0' || c == '1' )									/* If we got a 0 or 1 we check it.			*/
		{
			(*InputValues)[j][i] = c - '0';							/* If we got, then we assign to array.		*/

			++i;													/* New count variables.						*/
		}
		else if ( c == '\n' )										/* We check if we have a new line.			*/
		{	
			++j;													/* If we got then new array.				*/
			i = 0; 													/* We re-initialize our counter.			*/
		}	
	}

	fclose(fp);														/* We close our file.						*/

	return j+1;														/* We return columns of inputs.				*/
}

int FindingLogicOperators(char **Circuit, struct logic **gate, int *InputSize, int CounterCircuit)		/* It finds logic gates.	*/
{
	int i = 0, j = 0, t = 0, l = 0, m = 0, p = 0, q = 0, w = 0;			/* They are just counters.					*/

	*gate = (struct logic*)calloc(50,sizeof(char*));					/* We allocate dynammical to gate.			*/

	for (i = 0; i < CounterCircuit; ++i)								/* We start a loop in our Circuit array.	*/
	{
		if ( strncmp(Circuit[i],"INPUT",5) == 0 )							/* We check if we found the INPUT.			*/
		{
			for (j = strlen("INPUT")+1; Circuit[i][j] != '\0'; ++j)		/* If we got, then we start a loop.			*/
			{
				if ( Circuit[i][j] == ' ' )								/* We check the spaces.						*/
				{
					(*gate)[t].Input[l] = '\0';							/* If we have a space then we make a string.*/
					++t;												/* New array.								*/
					l = 0; 												/* We re-initialize our counter.			*/
				}
				else if ( Circuit[i][j+1] == '\0' )						/* We check if we are end of array.			*/
				{
					(*gate)[t].Input[l] = Circuit[i][j];				/* Then we get the last character.			*/
					(*gate)[t].Input[l+1] = '\0';						/* We make a last string.					*/
					l = 0;												/* We re-initialize our counter.			*/			
					++t;												/* We count for a new array.				*/
				}
				else{													/* If we don't finish an array we go on.	*/
					(*gate)[t].Input[l] = Circuit[i][j];				/* We assign characters to our input gate.	*/
					++l;												/* We count characters.						*/
				}
			}
			*InputSize = t;												/* We save the size of inputs.				*/		
		}
		else if ( strncmp(Circuit[i],"AND",3) == 0 )						/* We check if we found the AND.				*/
		{	
			for (j = strlen("AND")+1; Circuit[i][j] != '\0' ; ++j)		/* If we got, then we start a loop.			*/
			{
				if ( Circuit[i][j] == ' ' )								/* We check the spaces.						*/
				{
					(*gate)[m].AndGates[l] = '\0';						/* If we have a space then we make a string.*/
					++m;												/* New array.								*/
					l = 0;												/* We re-initialize our counter.			*/
				}
				else if ( Circuit[i][j+1] == '\0' )						/* We check if we are end of array.			*/
				{
					(*gate)[m].AndGates[l] = Circuit[i][j];				/* Then we get the last character.			*/
					(*gate)[m].AndGates[l+1] = '\0';					/* We make a last string.					*/
					l = 0;												/* We re-initialize our counter.			*/
					++m;												/* We count for a new array.				*/
				}
				else{													/* If we don't finish an array we go on.	*/
					(*gate)[m].AndGates[l] = Circuit[i][j];				/* We assign characters to our and gate.	*/
					++l;												/* We count characters.						*/
				}
			}
		}
		else if ( strncmp(Circuit[i],"OR",2) == 0 )							/* We check if we found the OR.			 		*/
		{	
			for (j = strlen("OR")+1; Circuit[i][j] != '\0' ; ++j)		/* If we got, then we start a loop.			*/
			{
				if ( Circuit[i][j] == ' ' )								/* We check the spaces.						*/
				{
					(*gate)[p].OrGates[l] = '\0';						/* If we have a space then we make a string.*/
					++p;												/* New array.								*/
					l = 0;												/* We re-initialize our counter.			*/
				}
				else if ( Circuit[i][j+1] == '\0' )						/* We check if we are end of array.			*/
				{
					(*gate)[p].OrGates[l] = Circuit[i][j];				/* Then we get the last character.			*/
					(*gate)[p].OrGates[l+1] = '\0';						/* We make a last string.					*/
					l = 0;												/* We re-initialize our counter.			*/
					++p;												/* We count for a new array.				*/
				}
				else{													/* If we don't finish an array we go on.	*/
					(*gate)[p].OrGates[l] = Circuit[i][j];				/* We assign characters to our or gate.		*/
					++l;												/* We count characters.						*/
				}
			}
		}
		else if ( strncmp(Circuit[i],"NOT",3) == 0 )						/* We check if we found the NOT.				*/
		{	
			for (j = strlen("NOT")+1; Circuit[i][j] != '\0' ; ++j)		/* If we got, then we start a loop.			*/
			{
				if ( Circuit[i][j] == ' ' )								/* We check the spaces.						*/
				{
					(*gate)[q].NotGates[l] = '\0';						/* If we have a space then we make a string.*/
					++q;												/* New array.								*/
					l = 0;												/* We re-initialize our counter.			*/
				}
				else if ( Circuit[i][j+1] == '\0' )						/* We check if we are end of array.			*/
				{
					(*gate)[q].NotGates[l] = Circuit[i][j];				/* Then we get the last character.			*/
					(*gate)[q].NotGates[l+1] = '\0';					/* We make a last string.					*/
					l = 0;												/* We re-initialize our counter.			*/
					++q;												/* We count for a new array.				*/
				}
				else{													/* If we don't finish an array we go on.	*/
					(*gate)[q].NotGates[l] = Circuit[i][j];				/* We assign characters to our not gate.	*/
					++l;												/* We count characters.						*/
				}
			}
		}
		else if ( strncmp(Circuit[i],"FLIPFLOP",8) == 0 )					/* We check if we found the FLIPFLOP.			*/
		{	
			for (j = strlen("FLIPFLOP")+1; Circuit[i][j] != '\0' ; ++j) /* If we got, then we start a loop.			*/
			{
				if ( Circuit[i][j] == ' ' )								/* We check the spaces.						*/
				{
					(*gate)[w].FlipflopGates[l] = '\0';					/* If we have a space then we make a string.*/
					++w;												/* New array.								*/
					l = 0;												/* We re-initialize our counter.			*/
				}
				else if ( Circuit[i][j+1] == '\0' )						/* We check if we are end of array.			*/
				{
					(*gate)[w].FlipflopGates[l] = Circuit[i][j];		/* Then we get the last character.			*/
					(*gate)[w].FlipflopGates[l+1] = '\0';				/* We make a last string.					*/
					l = 0;												/* We re-initialize our counter.			*/
					++w;												/* We count for a new array.				*/
				}
				else{													/* If we don't finish an array we go on.	*/
					(*gate)[w].FlipflopGates[l] = Circuit[i][j];		/* We assign characters to our flipflop gate.	*/
					++l;												/* We count characters.						*/
				}
			}
		}

		j = 0;				/* We re-initialize our counter.			*/
	}

	return i;				/* We return how many columns that we have.	*/
}

int LogicSolving(struct logic *gate, char **Circuit, int Value[200][250], int ValueCounter, int SizeC)	/* We solve the logic problem.		*/
{
	int i = 0, j = 0, k = 1, l = 1, m = 1, n = 1, TWO = 0;					/* They are just counters.					*/

	struct logic output,res,flip;											/* We declare our struct identifiers.		*/

	output.result = (int*)malloc(sizeof(int)*2);							/* We allocate dynammicly for our result.	*/

	output.result[0] = 0;													/* We initialize our results.				*/
	output.result[1] = 0;													/* We initialize our results.				*/

	flip.former_out = 0;													/* We initialize our former-out.			*/						

	for (i = 1; i < SizeC; ++i)												/* We start a loop in our Circuit array.	*/
	{
		if ( strncmp(Circuit[i],"AND",3) == 0 )								/* We check if we got AND.					*/
		{	
			for (j = 0; j < ValueCounter; ++j)								/* We got, then we start a loop for inputs.	*/
			{	
				if ( strcmp(gate[l].AndGates,gate[j].Input) == 0 )			/* We check if we have same strings.		*/
				{	
					output.result[0] = (*Value)[j];							/* If we have then we assign the 1st result.*/
					++TWO;													/* We count the TWO for 2 input of gate.	*/

				}
				else if ( strcmp(gate[l+1].AndGates,gate[j].Input) == 0 )	/* We check for if 2nd string are same.		*/
				{
					if ( TWO == 1 )											/* If we already found a variable we check.	*/
					{
						output.result[1] = (*Value)[j];						/* Then we assign 2nd variable.				*/
						res.temp1 = output.result[0] * output.result[1];	/* We make and operations to our result.	*/
					}
					else{													/* If we haven't found a variable.			*/
						output.result[0] = (*Value)[j];						/* Then we assign 1st variable.				*/
					}
					++TWO;													/* We found variables so we count it.		*/
				}
			}

			if ( TWO == 0 || TWO == 1 )					/* We check if we found 1st variable or we found nothing.		*/
			{
				if ( (strcmp(gate[l].AndGates,gate[k-1].OrGates) == 0) || (strcmp(gate[l+1].AndGates,gate[k-1].OrGates) == 0) )	/* We check if our gate connects to or gate.	*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{
						output.result[1] = res.temp2;								/* Then we assign to 2nd variable the or gate's results.		*/
						res.temp1 = output.result[0] * output.result[1];			/* We make and operations to our result.						*/
					}
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp2;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}					

					k += 3;															/* We count it for other gate.	*/
				}
				if ( (strcmp(gate[l].AndGates,gate[l-1].AndGates) == 0) || (strcmp(gate[l+1].AndGates,gate[l-1].AndGates) == 0) ) /* We check if our gate connects to and gate.	*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{
						output.result[1] = res.temp1;								/* Then we assign to 2nd variable the and gate's results.		*/
						res.temp1 = output.result[0] * output.result[1];			/* We make and operations to our result.						*/
					}	
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp1;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}

					l += 3;															/* We count it for other gate.	*/
				}
				if ( (strcmp(gate[l].AndGates,gate[m-1].NotGates) == 0) || (strcmp(gate[l+1].AndGates,gate[m-1].NotGates) == 0) ) /* We check if our gate connects to not gate.	*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{	
						output.result[1] = res.temp3;								/* Then we assign to 2nd variable the not gate's results.		*/
						res.temp1 = output.result[0] * output.result[1];			/* We make and operations to our result.						*/
					}
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp3;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}

					m += 2;															/* We count it for other gate.	*/
				}
				if ( (strcmp(gate[l].AndGates,gate[n-1].FlipflopGates) == 0) || (strcmp(gate[l+1].AndGates,gate[n-1].FlipflopGates) == 0) ) /* We check if our gate connects to flipflop gate.	*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{
						output.result[1] = res.temp4;								/* Then we assign to 2nd variable the flipflop gate's results.	*/
						res.temp1 = output.result[0] * output.result[1];			/* We make and operations to our result.						*/
					}
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp4;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}

					n += 2;															/* We count it for other gate.	*/
				}

				++TWO;																/* We found variables so we count it.							*/
				
				res.temp = res.temp1;				/* We assign it to last result.		*/
			}
		}
		else if ( strncmp(Circuit[i],"OR",2) == 0 )					/* We check if we got OR.					*/
		{
			for (j = 0; j < ValueCounter; ++j)						/* We got, then we start a loop for inputs.	*/
			{
				if ( strcmp(gate[k].OrGates,gate[j].Input) == 0 )	/* We check if we have same strings.		*/
				{
					output.result[0] = (*Value)[j];					/* If we have then we assign the 1st result.*/
					++TWO;											/* We count the TWO for 2 input of gate.	*/
				}
				else if ( strcmp(gate[k+1].OrGates,gate[j].Input) == 0 )	/* We check for if 2nd string are same.		*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{
						output.result[1] = (*Value)[j];								/* Then we assign 2nd variable.							*/
						if ( output.result[0] == 1 || output.result[1] == 1 )		/* We check if at least one input equals to 1.			*/
						{
							res.temp2 = 1;											/* Then we assign 1 to our result.						*/
						}
						else{														/* If both of them equals to zero.						*/
							res.temp2 = 0;											/* Then we assign 0 to our result.						*/
						}
					}
					else{															/* If we haven't found a variable.						*/
						output.result[0] = (*Value)[j];								/* Then we assign 1st variable.							*/
					}
					++TWO;															/* We found variables so we count it.					*/
				}
			}

			if ( TWO == 0 || TWO == 1 )					/* We check if we found 1st variable or we found nothing.		*/
			{
				if ( (strcmp(gate[k].OrGates,gate[k-1].OrGates) == 0) || (strcmp(gate[k+1].OrGates,gate[k-1].OrGates) == 0) )	/* We check if our gate connects to or gate.	*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{
						output.result[1] = res.temp2;								/* Then we assign to 2nd variable the or gate's results.		*/
						if ( output.result[0] == 1 || output.result[1] == 1 )		/* We check if at least one input equals to 1.					*/
						{
							res.temp2 = 1;											/* Then we assign 1 to our result.								*/
						}
						else{														/* If both of them equals to zero.								*/
							res.temp2 = 0;											/* Then we assign 0 to our result.								*/
						}
					}
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp2;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}

					k += 3;															/* We count it for other gate.	*/
				}
				if ( (strcmp(gate[k].OrGates,gate[l-1].AndGates) == 0) || (strcmp(gate[k+1].OrGates,gate[l-1].AndGates) == 0) )	/* We check if our gate connects to and gate.	*/
				{	
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{	
						output.result[1] = res.temp1;								/* Then we assign to 2nd variable the and gate's results.		*/
						if ( output.result[0] == 1 || output.result[1] == 1 )		/* We check if at least one input equals to 1.					*/
						{
							res.temp2 = 1;											/* Then we assign 1 to our result.								*/
						}
						else{														/* If both of them equals to zero.								*/
							res.temp2 = 0;											/* Then we assign 0 to our result.								*/			
						}
					}
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp1;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}

					l += 3;															/* We count it for other gate.	*/
				}
				if ( (strcmp(gate[k].OrGates,gate[m-1].NotGates) == 0) || (strcmp(gate[k+1].OrGates,gate[m-1].NotGates) == 0) )	/* We check if our gate connects to not gate.	*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{	
						output.result[1] = res.temp3;								/* Then we assign to 2nd variable the not gate's results.		*/
						if ( output.result[0] == 1 || output.result[1] == 1 )		/* We check if at least one input equals to 1.					*/
						{
							res.temp2 = 1;											/* Then we assign 1 to our result.								*/
						}
						else{														/* If both of them equals to zero.								*/
							res.temp2 = 0;											/* Then we assign 0 to our result.								*/
						}
					}
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp3;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}

					m += 2;															/* We count it for other gate.	*/
				}
				if ( (strcmp(gate[k].OrGates,gate[n-1].FlipflopGates) == 0) || (strcmp(gate[k+1].OrGates,gate[n-1].FlipflopGates) == 0) )	/* We check if our gate connects to flipflop gate.	*/
				{
					if ( TWO == 1 )			/* We check if we already found 1st variable.	*/
					{			
						output.result[1] = res.temp4;								/* Then we assign to 2nd variable the flipflop gate's results.	*/
						if ( output.result[0] == 1 || output.result[1] == 1 )		/* We check if at least one input equals to 1.					*/
						{
							res.temp2 = 1;											/* Then we assign 1 to our result.								*/
						}
						else{														/* If both of them equals to zero.								*/
							res.temp2 = 0;											/* Then we assign 0 to our result.								*/
						}
					}
					else{															/* If we haven't found a variable.								*/
						output.result[0] = res.temp4;								/* We assign 1st variable.										*/
						++TWO;														/* We found variables so we count it.							*/
					}

					n += 2;															/* We count it for other gate.	*/
				}

				++TWO;																/* We found variables so we count it.							*/
				res.temp = res.temp2;				/* We assign it to last result.		*/
			}	
		}
		else if ( strncmp(Circuit[i],"NOT",3) == 0 )				/* We check if we got NOT.					*/
		{
			for (j = 0; j < ValueCounter; ++j)						/* We got, then we start a loop for inputs.	*/
			{
				if ( strcmp(gate[m].NotGates,gate[j].Input) == 0 )	/* We check if we have same strings.		*/
				{
					output.result[0] = (*Value)[j];					/* If we have then we assign the 1st result.*/
					++TWO;											/* We count the TWO for 1 input of gate.	*/
				}
			}

			if ( TWO == 0 )						/* We check if we didn't find 1st variable.	*/
			{
				if ( (strcmp(gate[m].NotGates,gate[k-1].OrGates) == 0) )				/* We check if our gate connects to or gate.						*/
				{
					output.result[0] = res.temp2;									/* Then we assign to 1st variable the or gate's results.			*/
					k += 3;															/* We count it for other gate.	*/
				}	
				else if ( (strcmp(gate[m].NotGates,gate[l-1].AndGates) == 0) )		/* We check if our gate connects to and gate.						*/
				{
					output.result[0] = res.temp1;									/* Then we assign to 1st variable the and gate's results.			*/
					l += 3;															/* We count it for other gate.	*/
				}
				else if ( (strcmp(gate[m].NotGates,gate[m-1].NotGates) == 0) )		/* We check if our gate connects to not gate.						*/
				{
					output.result[0] = res.temp3;									/* Then we assign to 1st variable the not gate's results.			*/
					m += 2;															/* We count it for other gate.	*/
				}
				else if ( (strcmp(gate[m].NotGates,gate[n-1].FlipflopGates) == 0) )	/* We check if our gate connects to flipflop gate.					*/
				{
					output.result[0] = res.temp4;									/* Then we assign to 1st variable the flipflop gate's results.		*/
					n += 2;															/* We count it for other gate.	*/
				}
			}

			if ( output.result[0] == 1 )		/* We check if our result equals to 1.		*/
			{
				res.temp3 = 0;					/* Then we assign 0 to our result.			*/
			}
			else{								/* If our result equals to 0.				*/
				res.temp3 = 1;					/* Then we assign 1 to our result.			*/
			}

			res.temp = res.temp3;				/* We assign it to last result.				*/
		}
		else if ( strncmp(Circuit[i],"FLIPFLOP",8) == 0 )				/* We check if we got FLIPFLOP.					*/
		{
			for (j = 0; j < ValueCounter; ++j)							/* We got, then we start a loop for inputs.		*/
			{
				if ( strcmp(gate[n].FlipflopGates,gate[j].Input) == 0 )	/* We check if we have same strings.			*/
				{
					output.result[0] = (*Value)[j];						/* If we have then we assign the 1st result.	*/
					++TWO;												/* We count the TWO for 1 input of gate.		*/
				}
			}

			if ( TWO == 0 )						/* We check if we didn't find 1st variable.	*/
			{
				if ( (strcmp(gate[n].FlipflopGates,gate[k-1].OrGates) == 0) )				/* We check if our gate connects to or gate.						*/
				{
					output.result[0] = res.temp2;										/* Then we assign to 1st variable the or gate's results.			*/	
					k += 3;																/* We count it for other gate.	*/	
				}
				else if ( (strcmp(gate[n].FlipflopGates,gate[m-1].NotGates) == 0) )		/* We check if our gate connects to not gate.						*/
				{
					output.result[0] = res.temp3;										/* Then we assign to 1st variable the not gate's results.			*/
					m += 2;																/* We count it for other gate.	*/
				}	
				else if ( (strcmp(gate[n].FlipflopGates,gate[l-1].AndGates) == 0) )		/* We check if our gate connects to and gate.						*/
				{
					output.result[0] = res.temp1;										/* Then we assign to 1st variable the and gate's results.			*/
					l += 3;																/* We count it for other gate.	*/
				}
				else if ( (strcmp(gate[n].FlipflopGates,gate[n-1].FlipflopGates) == 0) )	/* We check if our gate connects to flipflop gate.					*/
				{
					output.result[0] = res.temp4;										/* Then we assign to 1st variable the flipflop gate's results.		*/
					n += 2;																/* We count it for other gate.	*/
				}
			}

			if ( (flip.former_out == 0 && output.result[0] == 0) || (flip.former_out == 1 && output.result[0] == 1) )	/* We check if our former-out and results are same.			*/
			{
				res.temp4 = 0;				/* If they are same then our result is 0.			*/
			}
			else{							/* If they have different values.					*/
				res.temp4 = 1;				/* Then our result is 1.							*/
			} 

			res.temp = res.temp4;			/* We assign it to last result.						*/	
		}

		flip.former_out = res.temp4;		/* We re-initialize our former-out.					*/
		TWO = 0;							/* We re-initialize our counter of inputs.			*/
	}

	free(output.result);					/* We free our result.								*/

	return res.temp;						/* We return our result of logic problem.			*/
}