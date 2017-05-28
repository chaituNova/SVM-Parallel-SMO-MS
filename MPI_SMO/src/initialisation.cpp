#include "includes/computeL_H.h"

void initialisation(int class1, int class2)
{

	for(int i=0;i<vecl_tr.size();i++)
	{
		if(vecl_tr[i] == class1 || vecl_tr[i] == class2)
		{
			if(vecl_tr[i] == class1)
				target.push_back(1);
			else
				target.push_back(-1);
			vector<float> tp;
			for(int j=0;j<vec_tr[i].size();j++)
			{
				tp.push_back(vec_tr[i][j]);
			}
			X.push_back(tp);
			
		}
	}
	N = target.size();
	M = X[0].size();
	X_arr = new float[N*M];
	for(int i = 0; i<N; i++){
		for(int j = 0; j<M; j++){
			X_arr[(i*M)+j] = X[i][j];
		}
	}

	for(int i=0;i<vecl_te.size();i++)
	{
		if(vecl_te[i] == class1 || vecl_te[i] == class2)
		{
			if(vecl_te[i] == class1)
				target_test.push_back(1);
			else
				target_test.push_back(-1);
			vector<float> tp;
			for(int j=0;j<vec_te[i].size();j++)
			{
				tp.push_back(vec_te[i][j]);
			}
			X_test.push_back(tp);
		}
	}
	N_test = X_test.size();
	K_test = new float*[N_test];

	for(int i = 0; i<N_test; i++){
		K_test[i] = new float[N];
	}
	cout << "Extraction done !, no of training examples (N): " << N << ", no of features (M): " << M << ", no of test examples (N_test): " << N_test << "\n";
	alpha = new float[N];
	for(int i=0;i<N;i++)
		alpha[i] = 0.0;
}

void initialisation_1()
{ 
	//int mystart_index;
	N = misc_arr[0];
	M = misc_arr[1];
	row_small = (N - (N%size))/size;	//no. of rows in X to be sent to other processors
	row_big = row_small + 1;		//no. of rows in X to be sent to other processors
	no_of_big_proc = N%size;
	if(myrank < no_of_big_proc){
		myT_size = row_big;
		myN = row_big;
		mystart_index = myrank*row_big;
	}
	else{
		myT_size = row_small;
		myN = row_small;
		mystart_index = (no_of_big_proc*row_big)+((myrank - no_of_big_proc)*row_small);
	}

	myalpha = new float[myN];
	myfcache = new float[myN]; 
		
	

	mytarget = new int[myN];
	myX = new float*[myN];
	for(int i = 0; i<myN; i++){
		myX[i] = new float[M];
	}
	myX_size = myN*M;
	myX_arr = new float[myX_size];
	myX1 = new float[M];
	myX2 = new float[M];
	alpha_old_new_arr = new float[4];
	myt = new int[2];
	i_arr = new int[2];
	b_arr = new float[2];
	
	b_up_arr = new float[size];
	b_low_arr = new float[size];
	i_up_arr = new int[size];
	i_low_arr = new int[size];
	cout<<myrank<<": mystart_index: "<<mystart_index<<endl;

}

