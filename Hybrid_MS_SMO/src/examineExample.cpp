//globals : fcache, target, alpha, b_low, b_up, i_up, i_low, C, tol

#include "includes/computeL_H.h"


bool Contains(const std::vector<int> &list, int x)
{
	return std::find(list.begin(), list.end(), x) != list.end();
}

int examineExample(int i2)
{
	int i1;
	int y2 = target[i2];
	float a2 = alpha[i2];
	float F2;
	int optimality = 1;
	if(Contains(I0,i2))
	{
		F2 = fcache[i2];
	}
	else
	{
		F2 = compute_F(i2);
		fcache[i2] = F2;
		// 
		if((Contains(I1,i2) || Contains(I2,i2)) && F2 <b_up)
		{
			//cout << "There " << endl;
			b_up = F2;
			i_up = i2;
		}
		else if((Contains(I3,i2) || Contains(I4,i2)) && F2 > b_low)
		{
			//cout << "Here " << endl;
			b_low = F2;
			i_low = i2;
		}
	}
	if(Contains(I0,i2) || Contains(I1,i2) || Contains(I2,i2))
	{
		//cout << i2 << "I0 or I1 or I2 F2: " << F2 << "b_low :" << b_low << endl;
		if(b_low-F2 > 2*tol)
		{
			//cout << "Entering optimality 0" << endl;
			optimality = 0;
			i1 = i_low;
		}
	}
	if(Contains(I0,i2) || Contains(I3,i2) || Contains(I4,i2))
	{
				//cout << i2 << "I0 or I3 or I4 F2: " << F2 << "b_up :" << b_up << endl;
		if(F2-b_up > 2*tol)
		{
			//cout << "Entering optimality 0 " << "i2: " << i2 << endl;
			optimality = 0;
			i1 = i_up;
		}
	}
	if(optimality == 1)
		return 0;
	if(Contains(I0,i2))
	{
		if(b_low-F2 > F2-b_up)
			i1 = i_low;
		else
			i1 = i_up;
	}
	if(takeStep(i1,i2))
	{
		//cout << "takestep 1 i1:" << i1 << "i2 " << i2 << endl;
		return 1;
	}
	else
	{
		
		return 0;
	}
}
