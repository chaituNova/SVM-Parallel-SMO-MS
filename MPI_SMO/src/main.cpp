//Globals : N, K, i_up, i_low, b_up, b_low, tol, alpha, target, fcache, gamma

#include "includes/computeL_H.h"

float b_up,b_low,tol,C,gama;
float *myalpha, *myfcache;
float **K, **K_exp, **myK;
float **K_test, **myK_test;
float L,H;
vector<vector<float> > vec_tr;
vector<float> vecl_tr;
vector<vector<float> > vec_te;
vector<float> vecl_te;
vector<vector<float> > X;
vector<vector<float> > X_test;
vector<int> target;
vector<int> target_test;
int i_up, i_low, N, M, N_test;
vector<int> myI0, myI1,myI2,myI3,myI4;
float *alpha, *fcache, *myX_arr, *alpha_old_new_arr,*myX1,*myX2,*b_arr,*b_low_arr,*b_up_arr;
int *mytarget, *myt, *i_arr, *i_up_arr, *i_low_arr;
float myb_up,myb_low;
int myX_size, myT_size,myN,myi_up,myi_low,myi_up_g, myi_low_g,myrank,mystart_index,row_big,row_small,no_of_big_proc,size;
int misc_arr[2];		//row_small, N, no_of_big_proc
int* t_send_counts;	//arrays used when we scatter and gather test arrays and X arrays 
int* t_send_disp;	//disp => displacement 
int* send_counts;
int* send_disp;
float** myX; 
int myN_test;		//N and N_test for a process
float* X_arr;
float alpha1_new, alpha2_new, alpha1_old, alpha2_old;
int yy1, yy2;
int i_z1, i_z2;
int cl1,cl2;
float *my_b_arr;
int *my_i_g;
float *b_up_low_arr;
int *i_up_low_arr;


//Initialise N this is from 
//Initialize tol,C

int main(int argc, char* argv[])
{
	float acc,temp;
	MPI_Init(&argc, &argv);
    	//printf("hihihi\n");
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	//cout << size << endl;
	//cout << myrank << endl;
	
	send_counts = new int[size];
	send_disp = new int[size];
	t_send_counts = new int[size];
	t_send_disp = new int[size];

	if(myrank == 0){	//process 0
		//preprocessing of data
		if(argc != 2 ){
			cout << "argc: " <<argc<<endl;
			cout << "Please give one argument , \narg1: dataset (0-mn    ist, 1-splice, 2-not mnist, 3-a9a, 4-ijcnn1, 5-codrna, 6-covtype)" <<endl;
			return 0;
		}	
		switch (argv[1][0]){
			case '0':
				mnist_data_processing();
				break;
			case '1':
				splice_data_processing();
				break;
			case '2':
				notMNIST_data_processing();
				break;
			case '3':
				a9a_data_processing();
				break;
			case '4':
				ijcnn1_data_processing();
				break;
			case '5':
				codrna_data_processing();
				break;
			case '6':
				covtype_data_processing();
				break;
		}
		//initialization
		initialisation(cl1,cl2);	//got N and M
		misc_arr[0] = N;
		misc_arr[1] = M;
	}
	switch (argv[1][0]){
			case '0':
				gama = 3e-8; 	//mnist
				break;
			case '1':
				gama = 3e-2; 	//splice
				break;
			case '2':
				gama = 3e-8; 	//notmnist
				break;
			case '3':
				gama = 3e-2; 	//a9a
				break;
			case '4':
				gama = 3e-2; 	//ijcnn1
				break;
			case '5':
				gama = 3e-2; 	//cod-rna
				break;
			case '6':
				gama = 3e-2; 	//covtype
				break;

	}
	//1. broadcast N and M to all the processes
	MPI_Bcast(misc_arr, 2, MPI_INT, 0, MPI_COMM_WORLD);
	
	//cout << myrank << ": "<< "Reached barrier after broadcast" <<endl;
	initialisation_1();
	

	//2. send chunks of X and target to the processes

	for(int i = 0; i<size; i++){
		if(i < no_of_big_proc){
			send_counts[i] = M*row_big;
			send_disp[i] = i*M*row_big;
			t_send_counts[i] = row_big;
			t_send_disp[i] = i*row_big;
		}
		else{
			send_counts[i] = M*row_small;
			send_disp[i] = (no_of_big_proc*M*row_big)+((i-no_of_big_proc)*M*row_small);
			t_send_counts[i] = row_small;
			t_send_disp[i] = (no_of_big_proc*row_big)+((i-no_of_big_proc)*row_small);
		}
	}
	
	MPI_Scatterv(&(target[0]), t_send_counts, t_send_disp, MPI_INT, &(mytarget[0]), myT_size, MPI_INT, 0, MPI_COMM_WORLD);



	MPI_Scatterv(X_arr, send_counts, send_disp, MPI_FLOAT, myX_arr, myX_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < myN; i++) {
		for(int j = 0; j<M; j++){
			myX[i][j] = myX_arr[(i*M)+j];
		}
		
	}
	cout<<myrank<<": gama value: "<<gama<<endl;
	tol = 0.001;
	C = 1;
	// The following section should be uncommented if testing is needed
	/*if(myrank == 0){
		for(int s=0;s<N_test;s++)
		{
			//cout << s << "\n";
			for(int t=0;t<N;t++)
			{
				temp = 0.0;
				for(int l=0; l<M; l++)
				{
					temp += pow(X_test[s][l]-X[t][l],2);
				}
				temp = -1.0*gama*temp;
				K_test[s][t] = exp(temp);			//radial basis function
			
			}
		}
		cout << "Kernel computations for train vectors completed! \n";
	}*/
	
	SMO();
	cout<<myrank<<": Returned from SMO"<<endl;
	// The following section should be uncommented if alphas need to be stored and testing is needed		
	/*if(myrank == 0)
	{	
		cout<<myrank<<": b_up and b_low: "<<b_up<<" "<<b_low<<endl;
		std::ofstream outf("alpha.out");
		for(int p=0;p<N;p++)
			outf << alpha[p] << "\n";
		acc = test();
	}*/
	
	MPI_Finalize();
	return 0;
}
