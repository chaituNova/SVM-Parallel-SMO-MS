#include "includes/computeL_H.h"

float mykernel_calc(int i1, int i2)
{
	float k=0;
	if(i2 == 1){
		for(int i=0;i<M;i++)
		{
			k = k+((myX[i1][i]-myX1[i])*(myX[i1][i]-myX1[i]));
		}
	}
	else{
		for(int i=0;i<M;i++)
		{
			k = k+((myX[i1][i]-myX2[i])*(myX[i1][i]-myX2[i]));
		}
	}
	
	k = exp(-1.0*k*gama);
	return k;
}

float kernel_calc(int i1, int i2)
{
	float k=0;
	for(int i=0;i<M;i++)
	{
		k = k+((X[i1][i]-X[i2][i])*(X[i1][i]-X[i2][i]));
	}
	k = exp(-1.0*k*gama);
	return k;
}
