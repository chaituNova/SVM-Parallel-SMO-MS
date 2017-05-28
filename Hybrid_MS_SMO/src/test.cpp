#include "includes/computeL_H.h"
float test()
{
	//std::ofstream test_class_file("test_class.txt");
	float b,cl;
	float acc = 0;
  float* w = new float[M];
  int *class_pre = new int[N_test];
  int i,j;

  b = (b_up+b_low)/2;
  #pragma omp parallel
  {
    #pragma omp for private(i,j,cl) reduction(+:acc)
    for(j=0;j<N_test;j++)
    {
    	cl = 0;
      for(i = 0; i<N; i++){
          //cl = cl+(w[i]*X_test[j][i]);
  				cl = cl+(alpha[i]*target[i]*K_test[j][i]);
      }
    	cl = cl-b;
      if(cl>=0){      //class 1
          //test_class_file<<1<<endl;
          class_pre[j] = 1;
      }
      else{
          //test_class_file<<-1<<endl;
          class_pre[j] = -1;
      }
      if(class_pre[j] == target_test[j])
      	acc += 1.0;
    }
  }
  acc = acc/(float)N_test;
  //cout << acc << "\n";
  //test_class_file << acc << endl;
  //test_class_file.close();
  return acc;
}
