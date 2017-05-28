#include "includes/computeL_H.h"

int update_alpha(int i1,int i2) //i1 is always up, i2 is always low
{
		float alpha1 = alpha[i1];
    float alpha2 = alpha[i2];
    int y1 = target[i1];
    int y2 = target[i2];
	float b1 = b_up;
	float b2 = b_low;
    float Lobj, Hobj;
    int s = y1*y2;
    float k11, k12, k22, eta;
    float a2,a1;
		
		float eps = numeric_limits<float>::epsilon();
	alpha1_old = alpha[i1];
	alpha2_old = alpha[i2];
		
		if (i1 == i2){
        return 0;
    }
    computeL_H(i1,i2);
    
    if (L == H){
        return 0;
    }
    k11 = 1.0;
    k12 = kernel_calc(i1,i2);				//Function to be written need to check syntax
    k22 = 1.0;
    
    eta = (2*k12) - k11 - k22;
    
    if(eta < 0){
        a1 = alpha1 - ((y1*(b2-b1))/eta);
        if (a1 < L){
            a1 = L;
        }
        else{
            if(a1 > H){
                a1 = H;
            }
        }
    }
    else{
        Lobj = (0.5*eta*L*L)+(((target[i1]*(b2-b1))-(eta*alpha1))*L);
        Hobj = (0.5*eta*H*H)+(((target[i1]*(b2-b1))-(eta*alpha1))*H);
        if (Lobj > Hobj+eps){   
            a1 = L;
        }
        else if (Lobj < Hobj-eps){
            a1 = H;
        }
        else{
            a1 = alpha1;
        }
    }
    
    if (fabs(a1 - alpha1) < eps*(a1+alpha1+eps)){
        return 0;
    }
    
    a2 = alpha2 + s*(alpha1 - a1);
    //update the alpha array

    
    alpha1_new = a1;
    alpha2_new = a2;


    alpha[i1] = alpha1_new;
    alpha[i2] = alpha2_new;
    return 1;
}
