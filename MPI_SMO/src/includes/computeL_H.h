#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits> 
#include <fstream>
#include <sstream>
#include <mpi.h>
using namespace std;
float compute_L(int i1,int i2,float C);
float compute_H(int i1, int i2, float C);
void computeL_H(int i1, int i2);
float compute_F(int i);
int examineExample(int i2);
int takeStep(int i1, int i2);
float test_on_data(char* test_data);

void mnist_data_processing();
void splice_data_processing();
void notMNIST_data_processing();
void a9a_data_processing();
void ijcnn1_data_processing();
void codrna_data_processing();
void covtype_data_processing();

void file_init(char* filename);
void initialisation(int class1, int class2);
void initialisation_1();
void SMO(void);
float test(void);
float mykernel_calc(int i1, int i2);
int update_alpha(int i1,int i2);
void update_f();
void calc_b();
float kernel_calc(int i1, int i2);
//Globals
extern float b_up,b_low,tol,C,gama;
extern float *myalpha, *myfcache;
extern float **K, **K_exp, **myK;
extern float **K_test, **myK_test;
extern float L,H;
extern vector<vector<float> > vec_tr;
extern vector<float> vecl_tr;
extern vector<vector<float> > vec_te;
extern vector<float> vecl_te;
extern vector<vector<float> > X;
extern vector<vector<float> > X_test;
extern vector<int> target;
extern vector<int> target_test;
extern int i_up, i_low, N, M, N_test;
extern float *alpha, *fcache, *myX_arr, *alpha_old_new_arr, *myX1,*myX2, *b_up_arr, *b_low_arr,*b_arr;
extern int *myt, *i_arr, *i_up_arr, *i_low_arr;
extern int myX_size,myN,myi_up,myi_low,myi_up_g, myi_low_g,myrank,mystart_index,size,row_big,row_small,no_of_big_proc;
extern float myb_up,myb_low;
extern float **myX;
extern vector<int> myI0, myI1,myI2,myI3,myI4;
extern int misc_arr[2];		//row_small, N, no_of_big_proc
extern int* t_send_counts;	//arrays used when we scatter and gather test arrays and X arrays 
extern int* t_send_disp;	//disp => displacement 
extern int* send_counts;
extern int* send_disp;
extern int* mytarget; 	//target array chunk with a process
extern int myT_size;	///targer array chunk size with a process
extern float* X_arr; 
extern int myX_size; 	//X array chunk size
extern int myN;		//N for a process
extern float alpha1_new, alpha2_new, alpha1_old, alpha2_old;
extern int yy1, yy2;
extern int i_z1, i_z2;
extern int cl1,cl2;
extern float *my_b_arr;
extern int *my_i_g;
extern float *b_up_low_arr;
extern int *i_up_low_arr;
#endif
