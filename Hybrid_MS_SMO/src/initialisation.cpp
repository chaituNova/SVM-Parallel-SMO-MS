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
	
	cout << "Extraction done !, no of training examples (N): " << N << ", no of features (M): " << M << ", no of test examples (N_test): " << N_test << "\n";

}
void memory_init(int N,int N_test){
	alpha = new float[N];
	fcache = new float[N]; 
	
	K = new float*[N];
	for(int s=0;s<N;s++)
		K[s] = new float[N];
	
	K_test = new float*[N_test];
	for(int s=0;s<N_test;s++)
		K_test[s] = new float[N];
	
}
