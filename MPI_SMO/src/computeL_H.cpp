// It needs access to alpha and target Kernel matrix K, N

#include "includes/computeL_H.h"


float compute_L(int i1,int i2,float C)
{
	float a1_old = alpha[i1];
	float a2_old = alpha[i2];
	int y1 = target[i1];
	int y2 = target[i2];
	
	if(y1 != y2)
	{
		if(a2_old-a1_old > 0)
			return a2_old-a1_old;
	}
	else
	{
		if(a2_old+a1_old-C > 0)
			return a2_old+a1_old-C;
	}
	return 0.0;
}
			

float compute_H(int i1, int i2, float C)
{
	float a1_old = alpha[i1];
	float a2_old = alpha[i2];
	int y1 = target[i1];
	int y2 = target[i2];
	
	if(y1!=y2)
	{
		if(C+a2_old-a1_old < C){
			return C+a2_old-a1_old;}
	}
	else
	{
		if(a1_old+a2_old < C){
			return a1_old+a2_old;}
	}
	return C;
}

void computeL_H(int i1, int i2)
{
	float a1_old = alpha[i1];
	float a2_old = alpha[i2];
	int y1 = target[i1];
	int y2 = target[i2];
	float g;
	if(y1 == y2)
	{
		g = a1_old+a2_old;
		if(g>C)
		{
			L = g-C;
			H = C;
		}
		else
		{
			L = 0;
			H = g;
		}
	}
	else
	{
		g = a1_old-a2_old;
		if(g>0)
		{
			L = 0;
			H = C-g;
		}
		else
		{
			L = -1*g;
			H = C;
		}
	}
}

float compute_F(int i)
{
	int l;
	float sum = 0.0;
	for(l=0;l<N;l++)
	{
		sum = sum+(alpha[l]*target[l]*K[l][i]);
	}
	return sum-target[i];
}

