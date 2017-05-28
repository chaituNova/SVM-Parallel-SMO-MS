#include "includes/computeL_H.h"
void SMO()
{
for(int p=0;p<N;p++)
	{
		alpha[p] = 0.0;
		if(target[p] == 1)
		{
			i_up = p;
			I1.push_back(p);
			fcache[p] = -1.0;
		}
		else
		{
			i_low = p;
			I4.push_back(p);
			fcache[p] = 1.0;
		}
	}

	b_up = -1.0;
	b_low = 1.0;
	fcache[i_low] = 1.0;
	fcache[i_up]  = -1.0;
	int numChanged = 0;
	int examineAll = 1;
	int i1,i2, y2;
	float alpha2,F2;
	int inner_loop_success = 1;
	//Modification 1
			while((b_up<=b_low-2*tol) && (inner_loop_success != 0))
			{
				i2 = i_low;
				y2 = target[i2];
				alpha2 = alpha[i2];
				F2 = fcache[i2];
				i1 = i_up;
				inner_loop_success = takeStep(i_up,i_low);
				numChanged += inner_loop_success;
				//cout << b_up << " B_UP B_LOW  " << b_low << endl;
			}

}
