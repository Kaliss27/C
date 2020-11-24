/*
  S17002346 - Peralta Luna Karen Lisseth
  Ordenamiento: Selectsort
*/
#include <stdio.h>
#include <stdlib.h>

void selectsort(int a[],int n);

int main(int argc, char const *argv[])
{
	int array[12];
	array[0]=51;
	array[1]=21;
	array[2]=39;
	array[3]=80;
	array[4]=36;
	printf("**Vector original**\n");
	for(int i=0;i<5;i++)
	{
		printf("|%i",array[i]);
	}
	printf("\n");
	selectsort(array,5);
	printf("**Vector ordenado con Select sort**\n");
		for(int i=0;i<5;i++)
	{
		printf("|%i",array[i]);
	}
	return 0;
}

void selectsort(int a[],int n)
{
	int less_i,i,j;
	for(i=0;i<n-1;i++)
	{
		less_i=i;
		for (j=i+1;j<n;j++)
		{
			if(a[j]<a[less_i])
				less_i=j;
		}
		if(i!=less_i)
		{
			int aux=a[i];
			a[i]=a[less_i];
			a[less_i]=aux;
		}
	}
}