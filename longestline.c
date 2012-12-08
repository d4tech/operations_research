#include<stdio.h>
//#include<conio.h>

struct longline
{
	int length;
	long startpos;
	long endpos;
}longestline={0,0,0};

void main()
{
	char c,next;
	FILE *fp;
	long prev,curr;
	long pos;
	
	fp=fopen("test.txt","r");
	prev=ftell(fp);
	printf("\n");
	while ((c=getc(fp)) != EOF)
	{
		printf("%c",c);
		if (c=='.')
			{
				curr=ftell(fp);
				if ((curr-prev) > longestline.length)
				{
					longestline.length=curr-prev;
					longestline.startpos=prev;
					longestline.endpos=curr;
					prev=curr;
				}
			}
	}
	printf("\nLength=%d startpos=%ld endpos=%ld\n\n",longestline.length,longestline.startpos,longestline.endpos);
	
	fseek(fp,longestline.startpos,0);
	pos=longestline.startpos;
	
	while (pos!=longestline.endpos)
	{
		c=getc(fp);
		printf("%c",c);
		pos=ftell(fp);
	}

}


