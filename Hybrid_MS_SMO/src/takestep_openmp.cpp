//Global variables: N is number of training images
// float alpha[N] = array of Lagrange multipliers
// int target[N] = array of classes
// int fcache[N] = array of F = Sigma_j(aj yj k(xi, xj)) - yi
// float C = cost
// vector<int>I0, I1, I2, I3, I4
// vectro<int>::iterator I1_itr, I2_itr, I3_itr, I4_itr
// N = no. of training images


#include "includes/computeL_H.h"


// function prototype:
// int takeStep(int i1, int i2, float**K)
// float compute_L(int i1,int i2,float C);
// float compute_H(int i1, int i2, float C);
int takeStep(int i1, int i2){   //i1, i2 indices
    float alpha1 = alpha[i1];
    float alpha2 = alpha[i2];
    int y1 = target[i1];
    int y2 = target[i2];
    float Lobj, Hobj;
    int s = y1*y2;
    float k11, k12, k22, eta;
    float a2,a1;
    float F1 = fcache[i1];
    float F2 = fcache[i2];
    int i;

    float eps = numeric_limits<float>::epsilon();
		int I0_val;
		vector<int>::iterator I0_itr, I1_itr, I2_itr, I3_itr, I4_itr;
		
    if (i1 == i2){
    		//cout << "i1==i2 ts return 0" << endl;
        return 0;
    }
    s = y1*y2;
    computeL_H(i1,i2);

    if (L == H){
    		//cout << "L==h ts return 0 L:" <<  L << "H:" << H << endl;
        return 0;
    }

    k11 = K[i1][i1];
    k12 = K[i1][i2];
    k22 = K[i2][i2];

    eta = (2*k12) - k11 - k22;
		//cout << "eta  ************* " << eta;
    if(eta < 0){
        a2 = alpha2 - ((y2*(F1 - F2))/eta);
        //cout << " a2 after eta < 0 " << a2 << endl;
        if (a2 < L){
            a2 = L;
        }
        else{
            if(a2 > H){
                a2 = H;
            }
        }
    }
    else{
        Lobj = (0.5*eta*L*L)+(((target[i2]*(fcache[i1]-fcache[i2]))-(eta*alpha2))*L);
        Hobj = (0.5*eta*H*H)+(((target[i2]*(fcache[i1]-fcache[i2]))-(eta*alpha2))*H);
        if (Lobj > Hobj+eps){   //what is eps
            a2 = L;
        }
        else if (Lobj < Hobj-eps){
            a2 = H;
        }
        else{
            a2 = alpha2;
        }
        if(a2 < 0 || a2 > C)
        	cout << "Lobj\n";
    }
    if (fabs(a2 - alpha2) < eps*(a2+alpha2+eps)){
    		//cout << "abs ts return 0" << endl;
        return 0;
    }
    a1 = alpha1 + s*(alpha2 - a2);
    #pragma omp parallel private(i)
    {
	    #pragma omp for
	    for (i = 0; i< N; i++){
		// remove the terms with old alpha values
		fcache[i] = fcache[i] - (alpha1*y1*K[i][i1]) - (alpha2*y2*K[i][i2]);
		// add the terms with new alpha values
		fcache[i] = fcache[i] + (a1*y1*K[i][i1]) + (a2*y2*K[i][i2]);
	    }
    }
	  // store a1 and a2 in alpha array
    alpha[i1] = a1;
    alpha[i2] = a2;
    // Update I0, I1, I2, I3, I4
    // remove i1 and i2 from them
    I0_itr = find(I0.begin(), I0.end(), i1);
    if(I0_itr != I0.end()){     //in I0
        I0.erase(I0_itr);
    }
    else{       //not in I0
        I1_itr = find(I1.begin(), I1.end(), i1);
        if(I1_itr != I1.end()){     //in I1
            I1.erase(I1_itr);
        }
        else{   //not in I0 and I1
            I2_itr = find(I2.begin(), I2.end(), i1);
            if(I2_itr != I2.end()){ //in I2
                I2.erase(I2_itr);
            }
            else{   //not in I0, I1, I2
                I3_itr = find(I3.begin(), I3.end(), i1);
                if(I3_itr != I3.end()){ //in I3
                    I3.erase(I3_itr);
                }
                else{   //not in I0, I1, I2, I3
                    I4_itr = find(I4.begin(), I4.end(), i1);
                    if(I4_itr != I4.end()){ //in I3
                        I4.erase(I4_itr);
                    }
                }
            }

        }
    }
    //remove i2
    I0_itr = find(I0.begin(), I0.end(), i2);
    if(I0_itr != I0.end()){     //in I0
        I0.erase(I0_itr);
    }
    else{       //not in I0
        I1_itr = find(I1.begin(), I1.end(), i2);
        if(I1_itr != I1.end()){     //in I1
            I1.erase(I1_itr);
        }
        else{   //not in I0 and I1
            I2_itr = find(I2.begin(), I2.end(), i2);
            if(I2_itr != I2.end()){ //in I2
                I2.erase(I2_itr);
            }
            else{   //not in I0, I1, I2
                I3_itr = find(I3.begin(), I3.end(), i2);
                if(I3_itr != I3.end()){ //in I3
                    I3.erase(I3_itr);
                }
                else{   //not in I0, I1, I2, I3
                    I4_itr = find(I4.begin(), I4.end(), i2);
                    if(I4_itr != I4.end()){ //in I3
                        I4.erase(I4_itr);
                    }
                }
            }
        }
    }

    //update I0, I1, I2, I3, I4
    if(alpha[i1]>0 && alpha[i1]<C){
        I0.push_back(i1);
    }
    else{
        if(alpha[i1] == 0){
            if(target[i1] == -1){
                I4.push_back(i1);
            }
            else{   //+1 class
                I1.push_back(i1);
            }
        }
        else if(alpha[i1] == C){
            if(target[i1] == -1){
                I2.push_back(i1);
            }
            else{   //+1 class
                I3.push_back(i1);
            }

        }
        else{
            //cout<<"alpha[i1] is not in legal range"<<endl;
        }
    }

    if(alpha[i2]>0 && alpha[i2]<C){
        I0.push_back(i2);
    }
    else{
        if(alpha[i2] == 0){
            if(target[i2] == -1){
                I4.push_back(i2);
            }
            else{   //+1 class
                I1.push_back(i2);
            }
        }
        else if(alpha[i2] == C){
            if(target[i2] == -1){
                I2.push_back(i2);
            }
            else{   //+1 class
                I3.push_back(i2);
            }

        }
        else{
            //cout<<"alpha[i2] is not in legal range"<<endl;
        }
    }


    
    
    //Computation of b_low b_up
    b_low = -1000000.0;
    b_up = 10000000.0;
    
    for(int p=0; p < I0.size(); p++)
    {
    	if(fcache[I0[p]] > b_low)
    	{
    		b_low = fcache[I0[p]];
    		i_low = I0[p];
    	}
    	if(fcache[I0[p]] < b_up)
    	{
    		b_up = fcache[I0[p]];
    		i_up = I0[p];
    	}
    }
    float temp;
    for(int p=0;p<I3.size();p++)
    {
    	temp = fcache[I3[p]];
    	if(temp > b_low)
    	{
    		b_low = temp;
    		i_low = I3[p];
    	}
    }
    for(int p=0;p<I4.size();p++)
    {
    	temp = fcache[I4[p]];
    	if(temp > b_low)
    	{
    		b_low = temp;
    		i_low = I4[p];
    	}
    }
    for(int p=0;p<I1.size();p++)
    {
    	temp = fcache[I1[p]];
    	if(temp < b_up)
    	{
    		b_up = temp;
    		i_up = I1[p];
    	}
    }
    for(int p=0;p<I2.size();p++)
    {
    	temp = fcache[I2[p]];
    	if(temp < b_up)
    	{
    		b_up = temp;
    		i_up = I2[p];
    	}
    }
   

    
    return 1;
}












