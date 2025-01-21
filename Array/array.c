#include<stdio.h>

// THE FUNCTION OF SUM-ROW - THE SUM OF XTH ROW'S ELEMENTS AND ADDED TO ALL ELEMENTS OF THE XTH COLUMN IN ORDER
void AddRows(int array[5][5], int x)
{	
	int sum = 0;
	for(int i=0; i<5; i++)
	{
		sum += array[x][i]; // THE SUM OF ROW
	}

	for(int j=0; j<5; j++)
	{
		array[j][x] += sum; // THE SUM IS ADDED TO RELATED COL'S ELEMENTS
	}
}

// THE FUNCTION OF SUM-COL - THE SUM OF XTH COL'S ELEMENTS AND ADDED TO ALL ELEMENTS OF THE XTH ROW IN ORDER
void AddCols(int array[5][5], int y)
{
	int sum=0;
	for(int i=0; i<5; i++)
	{
		sum += array[i][y]; // THE SUM OF COL
	}

	for(int j=0; j<5; j++)
	{
		array[y][j] += sum; // THE SUM IS ADDED TO RELATED ROW'S ELEMENTS
	}

}

// THE MAIN FUNCTION
int main()
{
	int array[5][5]; // BASE ARRAY DEFINITION 5*5
	int sum;

	// INPUT OF ARRAY ELEMENTS
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			scanf("%d", &array[i][j]);
		}
	}

	// THE ADDING AND ASSIGNING PROCESSES ARE DONE AT RELATED FUNCTIONS
	for (int i = 0; i < 5; i++)
	{
		AddRows(array, i);
		AddCols(array, i);
	}

	// PRINTING THE FINAL 2D ARRAY
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}

	return 0;
}
