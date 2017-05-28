#include "includes/computeL_H.h"
#include <string>
#include <sstream>
/* Global variables
int N, M;          //N = no. of training images, M = length of training images
float fcache[N]; //array of F = Sigma_j(aj yj k(xi, xj)) - yi
int target[N];   //array of classes
float alpha[N];  //array of Lagrange multipliers
float C         //cost
vector<int> I0, I1, I2, I3, I4;
int i_low, i_up;
float X[N][M]; //training data set
float b_up, b_low;*/


float test_on_data(char* test_data){

    std::ifstream test_data_file(test_data);
    std::ofstream test_class_file("test_class.txt");
    string line;
    int x,j;
    float cl;
    float acc;
    float* w = new float[M];
    float b;
		int dummy;
    test_data_file >> N_test;
    test_data_file >> dummy; 
    int *class_pre = new int[N_test];
    int *class_actual = new int[N_test];
    //populate w
    for(int i = 0; i<M; i++){
        w[i] = 0;
        for(int j = 0; j<N; j++){
            w[i] = w[i]+(alpha[j]*target[j]*K[j][i]);
        }
        //w[1] += alpha[i]*target[i]*kernel(i,1)
    }
	cout << b_up << " " << b_low << endl;
    b = (b_up+b_low)/2;
		j=0;
    while(getline(test_data_file, line)){
        istringstream iss(line);
        cl = 0;
        iss >> class_actual[j];
        for(int i = 0; i<M; i++){
            iss>>x;
            cl = cl+(w[i]*x);
        }
        cl = cl-b;
        if(cl>=0){      //class 1
            test_class_file<<1<<endl;
            class_pre[j] = 1;
        }
        else{
            test_class_file<<-1<<endl;
            class_pre[j] = -1;
        }
        j++;
    }
    acc =0.0;
		for(int i=0;i<N_test;i++)
		{
			if(class_pre[i] == class_actual[i])
				acc += 1.0;
		}
		acc = acc/(float)N_test;
		cout << acc << "\n";
		test_class_file << acc << endl;

    test_data_file.close();
    test_class_file.close();
    return acc;

}
