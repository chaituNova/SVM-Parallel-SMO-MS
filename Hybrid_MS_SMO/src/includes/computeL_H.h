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
using namespace std;
float compute_L(int i1,int i2,float C);
float compute_H(int i1, int i2, float C);
void computeL_H(int i1, int i2);
float compute_F(int i);
int examineExample(int i2);
int takeStep(int i1, int i2);
float test_on_data(char* test_data);

void mnist_data_processing(bool usepart);
void splice_data_processing();
void notMNIST_data_processing();
void a9a_data_processing();
void ijcnn1_data_processing();
void codrna_data_processing();

void file_init(char* filename);
void initialisation(int class1, int class2);
void memory_init(int N,int N_test);

void SMO(void);
float test(void);
//Globals
extern float b_up,b_low,tol,C,gama;
extern float *alpha, *fcache;
extern float **K, **K_exp;
extern float **K_test;
extern float L,H;
extern vector<vector<float> > vec_tr;
extern vector<float> vecl_tr;
extern vector<vector<float> > vec_te;
extern vector<float> vecl_te;
extern vector<vector<float> > X;
extern vector<vector<float> > X_test;
extern vector<float> target;
extern vector<float> target_test;
extern int i_up, i_low, N, M, N_test;
extern vector<int> I0, I1,I2,I3,I4;
extern int cl1,cl2;
#endif
