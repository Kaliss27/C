/*
  S17002346 - Peralta Luna Karen Lisseth
  Ordenamiento: Shell Sort 
*/
#include <stdio.h>
#include <stdlib.h>

void shellsort(int a[],int n);

int main(int argc, char const *argv[])
{
	int array[12];
	array[0]=6;
	array[1]=1;
	array[2]=5;
	array[3]=2;
	array[4]=3;
	array[5]=4;
	array[6]=0;
	printf("**Vector original**\n");
	for(int i=0;i<7;i++)
	{
		printf("|%i",array[i]);
	}
	printf("\n");
	shellsort(array,7);
	printf("**Vector ordenado con shellsort**\n");
		for(int i=0;i<7;i++)
	{
		printf("|%i",array[i]);
	}
	return 0;
}

void shellsort(int a[],int n)
{
	int intr,i,j,k;
	intr=n/2;
	while(intr>0)
	{
		for(i=intr;i<n;i++)
		{
			j=i-intr;
			while(j>=0)
			{
				k=j+intr;
				if(a[j] <= a[k])
					j=-1;
				else
				{
					int temp;
					temp=a[j];
					a[j]=a[k];
					a[k]=temp;
					j-=intr;
				}
			}
		}
		intr=intr/2;
	}
}