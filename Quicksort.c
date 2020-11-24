/*
  S17002346 - Peralta Luna Karen Lisseth
  Ordenamiento: Quicksort 
*/
#include <stdio.h>
#include <stdlib.h>

void quicksort(int a[],int first,int last);

int main(int argc, char const *argv[])
{
	int array[12];
	array[0]=72;
	array[1]=21;
	array[2]=15;
	array[3]=99;
	array[4]=88;
	array[5]=65;
	array[6]=75;
	array[7]=85;
	array[8]=76;
	array[9]=46;
	array[10]=84;
	array[11]=24;
	printf("**Vector original**\n");
	for(int i=0;i<12;i++)
	{
		printf("|%i",array[i]);
	}
	printf("\n");
	quicksort(array,0,12);
	printf("**Vector ordenado con quicksort**\n");
		for(int i=0;i<12;i++)
	{
		printf("|%i",array[i]);
	}
	return 0;
}

void quicksort(int a[],int first,int last)
{
	int i,j,center,piv;
	center=(first+last)/2;
	piv=a[center];

	i=first;
	j=last;

	do
	{
		while(a[i] < piv) i++;
		while(a[j] > piv) j--;

		if(i<=j)
		{
			int tmp;
			tmp=a[i];
			a[i]=a[j];
			a[j]=tmp;
			i++;
			j--;
		}
	}while(i <= j);

	if(first < j)
		quicksort(a,first,j);
	if( i < last)
		quicksort(a,i,last);
	return;
}