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

struct block cell[4][4];

int check(int);

void print();
void step1();
void step2();
void step3();
void step3b();

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
			}
			printf("\n");
		}
		print();
		step1();
		print();
		step2();
		print();
}



void print()
{
	int i,j;
	printf("\n");
	for (i = 0; i < n; i += 1)
	{
		for (j = 0; j < n; j += 1)
		{
			printf(" %d",cell[i][j].value);
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
		{return nz;}
	else
		{return nassigned;}	
}


void step3()
{
	int i,j;									//The usual Loop variables
	int i1;									//to be used inside the loop to avoid illegal modification of i
	struct tuple row_n_assigned_count[n]={{0},{0},{0}},col_n_assigned_count[n]={{0},{0},{0}};//Array to keep the count of 0 elements
	int i_point,j_point;					//stores the i'th and j'th value of the lone 0 element 

	void 3a();								//
	
	3a();
	
	void 3a()
	{
/*3.a.i: Examine all the rows having exactly one zero element */
		for (i = 0; i < n; i += 1)
		{
				
	/*	Loop to count the no of unssigned 0 elements in a Row*/
			for (j = 0; j < n; j += 1)
			{
				if(cell[i][j].state == nassigned) 
				{
					row_n_assigned_count[i]++;  //incremented upon encountering an unassigned 0
					i_point=i;j_point=j;		//store the address of the unassigned 0 element
				}
			}
/*If there is only one unassigned 0(count of unassigned 0's found by n_assigned _count[]) in the Row then: 
(1)assign it 
(2)cross the 0's in the column of the candidate cell*/
			if (n_assigned_count[i]==1)
			{
//(1)		
				cell[i_point][j_point].state=assigned;
				 		
//(2)Starting from the cell right under the candidate cell			
				for (i1 = i_point+1; i1 != i_point; i1 += 1)	
				{
					if(i1==n)
						i1=0;
					if (cell[i1][j_point].state==nassigned)
					{
						cell[i1][j_point].state=crossed;
					}
					
				}
						
			}
		}
	}
}			


