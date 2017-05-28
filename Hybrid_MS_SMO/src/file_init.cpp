#include "includes/computeL_H.h"

void file_init(char* filename)
{
	std::ifstream infile(filename);
	infile >> N >> M;
	alpha = new float[N];
	fcache = new float[N]; 

	K = new float*[N];
	for(int s=0;s<N;s++)
		K[s] = new float[N];
		
		K_exp = new float*[N];
	for(int s=0;s<N;s++)
		K_exp[s] = new float[N];
	cout << " " << N << " " << M << endl;
	
	float temp;
	
	for(int p=0; p<N; p++)
	{
		vector<float> tp;
		infile >> temp;
		target.push_back(temp);
		for(int l=0;l<M;l++)
		{
			infile >> temp;
			tp.push_back(temp);
		}
		X.push_back(tp);
	}
	if(infile)
		cout << "\n File copying is not complete\n";

	for(int p=0;p<N;p++)				//fcache initialisation
	{
		if(target[p] == 1)
		{
			fcache[p] = -1.0;
		}
		else
			fcache[p] = 1.0;
	}




}
