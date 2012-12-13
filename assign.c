#include<stdio.h>

static const n=4;
enum flag{nz,crossed,assigned,nassigned};

struct tupule
{
	int assigned_count;
	int nassigned_count;
	int crossed_count;
};

struct block
{
	int value;
	enum flag state; 
};

struct block cell[4][4],question[4][4];

int check(int);

void print();
void step1();
void step2();
void step3();
void optimalitytest();


void main()
{
 	int i,j;
 	
 	printf("\nStart Entering the values for a %dx%d matrix:\n",n,n);
	for (i = 0; i < n; i += 1)
	{
		for (j = 0; j < n; j += 1)
		{
			printf(" ");
			scanf("%d",&cell[i][j].value);
			cell[i][j].state=check(cell[i][j].value);
			question[i][j]=cell[i][j];
		}
		printf("\n");
	}

	print();
	step1();
//	print();
	step2();
/*	print();*/
	step3();
	print();
	optimalitytest();
}



void print()
{
	int i,j;
	printf("\n");
	for (i = 0; i < n; i += 1)
	{
		for (j = 0; j < n; j += 1)
		{
			printf("| %d, %d|",cell[i][j].value,cell[i][j].state);
		}
		printf("\n");
	}

}

void step1()
{
	int i=0,j=0,least[n];
	for(i=0;i<n;i++)
	 {
	  least[i]=cell[i][0].value;
/*Finding the Least element of the row*/
	  for(j=1;j<n;j++)
	  {
		if(least[i]>cell[i][j].value)
		 	least[i]=cell[i][j].value;
	  }
/*Subtracting the least element from the rest of the elements of row	 */
	  for(j=0;j<n;j++)
	  {
		cell[i][j].value= cell[i][j].value-least[i];
		cell[i][j].state= check(cell[i][j].value);
	  }

 }

}

void step2()
{
	int i=0,j=0,least[n];
	for(i=0;i<n;i++)
	 {
	  least[i]=cell[0][i].value;
/*Finding the Least element of the Column*/
	  for(j=1;j<n;j++)
	  {
		if(least[i]>cell[j][i].value)
		 	least[i]=cell[j][i].value;
	  }
/*Subtracting the least element from the rest of the elements of Column	 */
	  for(j=0;j<n;j++)
	  {
		cell[j][i].value= cell[j][i].value-least[i];
		cell[j][i].state=check(cell[j][i].value);
	  }

 }

}


int check(int i)
{
	if(i==0)
		{return nassigned;}
	else
		{return nz;}	
}

void optimalitytest()
{
	int i,j,sum=0,sum_ROW,sum_COL;
	struct tupule row_status[n],col_status[n];//Array to keep the count of 0 elements

	for (i = 0; i < n; i += 1)
	{
		row_status[i].nassigned_count=0;
		row_status[i].assigned_count=0;
		row_status[i].crossed_count=0;
	 /*	Loop to count the no of unssigned 0 elements in a Row*/
		for (j = 0; j < n; j += 1)
		{
			switch (cell[i][j].state)
			{
				case 1:
					row_status[i].crossed_count++;
					break;
				case 2:
					row_status[i].assigned_count++;
					break;
				case 3:				
					row_status[i].nassigned_count++;
					break;
					
			}
		}
	}
	
	for (i = 0; i < n; i += 1)
	{
		col_status[i].nassigned_count=0;
		col_status[i].assigned_count=0;
		col_status[i].crossed_count=0;
	 /*	Loop to count the no of unssigned 0 elements in a Column*/
		for (j = 0; j < n; j += 1)
		{
			switch (cell[j][i].state)
			{
				case 1:
					col_status[i].crossed_count++;
					break;
				case 2:
					col_status[i].assigned_count++;
					break;
				case 3:
					col_status[i].nassigned_count++;
					break;
					
			}
		}
	}


	sum_ROW = sum_COL = 0;

	for (i = 0; i < n; i++)
	{
		sum_ROW = sum_ROW + row_status[i].assigned_count;
		sum_COL = sum_COL + col_status[i].assigned_count;
	}

	if( sum_COL==4 && sum_ROW == 4)
	{
		printf("\n\n The Solution is optiaml\n");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if(cell[i][j].state==assigned)
				{
					printf("\n%d",question[i][j].value);
					sum += question[i][j].value;
				}
			}
		}
		printf("\nThe Total cost is: %d\n",sum);
		exit(0);
	}

}

void step3()

{
	int i,j;									//The usual Loop variables
	int i1;									//to be used inside the loop to avoid illegal modification of i
	struct tupule row_status[n],col_status[n];//Array to keep the count of 0 elements
	int i_point,j_point;					//stores the i'th and j'th value of the lone 0 element 


/*3.a.i: Examine all the rows having exactly one zero element */
	for (i = 0; i < n; i += 1)
	{
		row_status[i].nassigned_count=0;
		row_status[i].assigned_count=0;
		row_status[i].crossed_count=0;
	 /*	Loop to count the no of unssigned 0 elements in a Row*/
		for (j = 0; j < n; j += 1)
		{
			switch (cell[i][j].state)
			{
				case 1:
					row_status[i].crossed_count++;
					break;
				case 2:
					row_status[i].assigned_count++;
					break;
				case 3:				
					row_status[i].nassigned_count++;
					i_point=i;
					j_point=j;
					break;
					
			}
		}
/*If there is only one unassigned 0(count of unassigned 0's found by n_assigned _count[]) in the Row then: 
(1)assign it 
(2)cross the 0's in the column of the candidate cell*/
		if ( row_status[i].nassigned_count == 1)
		{
//(1)		
			cell[i_point][j_point].state=assigned;
				 		
//(2)Starting from the cell right under the candidate cell			
			for ( j = 0; j < n; j++)
			{
				if( j!=i_point && cell[j][j_point].state==nassigned)
				{
					cell[j][j_point].state=crossed;	
				}	
			}				
		}
	}
/* Columnwise */	
	for (i = 0; i < n; i += 1)
	{
		col_status[i].nassigned_count=0;
		col_status[i].assigned_count=0;
		col_status[i].crossed_count=0;
	 /*	Loop to count the no of unssigned 0 elements in a Column*/
		for (j = 0; j < n; j += 1)
		{
			switch (cell[j][i].state)
			{
				case 1:
					col_status[i].crossed_count++;
					break;
				case 2:
					col_status[i].assigned_count++;
					break;
				case 3:
					col_status[i].nassigned_count++;
					i_point=j;
					j_point=i;
					break;
					
			}
		}
/*If there is only one unassigned 0(count of unassigned 0's found by n_assigned _count[]) in the Row then: 
(1)assign it 
(2)cross the 0's in the Rows of the candidate cell*/
		if ( col_status[i].nassigned_count == 1)
		{
//(1)		
			cell[i_point][j_point].state=assigned;
//(2)		
			for ( j = 0; j < n; j++)
			{
				if( j!=j_point && cell[i][j].state==nassigned)
				{
					cell[i_point][j].state=crossed;	
				}	
			}				
		}
	}
}
	


			


