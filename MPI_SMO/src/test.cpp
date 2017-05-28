#include "includes/computeL_H.h"
float test()
{
	float b,cl;
	float acc = 0;
  float* w = new float[M];
  int *class_pre = new int[N_test];
	
  b = (b_up+b_low)/2;
  
  for(int j=0;j<N_test;j++)
  {
  	cl = 0;
    for(int i = 0; i<N; i++){
        //cl = cl+(w[i]*X_test[j][i]);
				cl = cl+(alpha[i]*target[i]*K_test[j][i]);
    }
  	cl = cl-b;
    if(cl>=0){      //class 1
        class_pre[j] = 1;
    }
    else{
        class_pre[j] = -1;
    }
    if(class_pre[j] == target_test[j])
    	acc += 1.0;
  }
  acc = acc/(float)N_test;
  cout << acc << "\n";
  return acc;
}
