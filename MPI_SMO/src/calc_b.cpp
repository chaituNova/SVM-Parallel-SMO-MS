#include "includes/computeL_H.h"

void calc_b()
{
		myb_low = -1000000.0;
    myb_up = 10000000.0;
    
    for(int p=0; p < myI0.size(); p++)
    {
    	if(myfcache[myI0[p]] > myb_low)
    	{
    		myb_low = myfcache[myI0[p]];
    		myi_low = myI0[p];
    	}
    	if(myfcache[myI0[p]] < myb_up)
    	{
    		myb_up = myfcache[myI0[p]];
    		myi_up = myI0[p];
    	}
    }
    float temp;
    for(int p=0;p<myI3.size();p++)
    {
    	temp = myfcache[myI3[p]];
    	if(temp > myb_low)
    	{
    		myb_low = temp;
    		myi_low = myI3[p];
    	}
    }
    for(int p=0;p<myI4.size();p++)
    {
    	temp = myfcache[myI4[p]];
    	if(temp > myb_low)
    	{
    		myb_low = temp;
    		myi_low = myI4[p];
    	}
    }
    for(int p=0;p<myI1.size();p++)
    {
    	temp = myfcache[myI1[p]];
    	if(temp < myb_up)
    	{
    		myb_up = temp;
    		myi_up = myI1[p];
    	}
    }
    for(int p=0;p<myI2.size();p++)
    {
    	temp = myfcache[myI2[p]];
    	if(temp < myb_up)
    	{
    		myb_up = temp;
    		myi_up = myI2[p];
    	}
    }
	myi_up_g = mystart_index+myi_up;
	myi_low_g = mystart_index+myi_low;
}
