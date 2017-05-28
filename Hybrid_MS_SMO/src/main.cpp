//Globals : N, K, i_up, i_low, b_up, b_low, tol, alpha, target, fcache, gamma_values

#include "includes/computeL_H.h"
#include <mpi.h>
#include <omp.h>
#define MSG_TAG 51
float b_up,b_low,tol,C,gama,L,H;
float *alpha, *fcache;
vector<vector<float> > vec_tr;
vector<float> vecl_tr;
vector<vector<float> > vec_te;
vector<float> vecl_te;
vector<vector<float> > X;
vector<vector<float> > X_test;
vector<float> target_test;
float **K, **K_exp;
float **K_test;
vector<float> target;
int i_up, i_low, N, M, N_test;
vector<int> I0, I1,I2,I3,I4;
vector<float> gamma_values, C_values;
float gamma_values_min,C_min,acc_max=0;
int feature_size,target_size,target_test_size;
vector<int> gamma_indices;
int G,W,load_per_processor,tag=MSG_TAG;
int cl1,cl2;
//Initialise N 
//Initialize tol,C
void resizeVec( std::vector<std::vector<float> > &vec , int ROWS , int COLUMNS )
{
    vec.resize( ROWS );
    for( std::vector<int>::size_type ind = 0; ind != vec.size() ; ind++)
    {
        vec[ind].resize( COLUMNS );
    }
}

int main(int argc, char* argv[])
{
	omp_set_num_threads(1);
	cout << "Setting number of threads to: " << atoi(argv[2]) << endl;
	omp_set_num_threads(atoi(argv[2]));
	int s, t, l;
    //Initialisation    
    if(argc != 3 ){
                    cout << "argc: " <<argc<<endl;
                    cout << "Please give three arguments , \narg1: dataset (0-mnist, 1-splice, 2-not mnist, 3-a9a, 4-ijcnn1, 5-codrna)\narg2,arg3: req class 1 , class 2 labels resp.," <<endl; 
                    return 0;
    }  	
	float acc,temp;

	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if(myrank==0){
		switch (argv[1][0]){
					case '0':
						mnist_data_processing(true);
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

		}
	
		initialisation(cl1,cl2);

		feature_size=X[1].size();
		target_size=target.size();
		target_test_size=target_test.size();
		memory_init(target_size,target_test_size);

		if(world_size>1){
			MPI_Bcast(&feature_size, 4, MPI_INT, 0, MPI_COMM_WORLD);
			MPI_Bcast(&target_size, 4, MPI_INT, 0, MPI_COMM_WORLD);
			MPI_Bcast(&target_test_size, 4, MPI_INT, 0, MPI_COMM_WORLD);
			
			MPI_Bcast(&target[0], (target_size), MPI_FLOAT, 0, MPI_COMM_WORLD);
			MPI_Bcast(&target_test[0], (target_test_size), MPI_FLOAT, 0, MPI_COMM_WORLD);
			for(int i1=0;i1<target_size;i1++){
				MPI_Bcast(&X[i1][0], feature_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
			}
			for(int i1=0;i1<target_test_size;i1++){
				MPI_Bcast(&X_test[i1][0], (feature_size), MPI_FLOAT, 0, MPI_COMM_WORLD);
			}
			
		}
	}
	else{
		MPI_Bcast(&feature_size, 4, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&target_size, 4, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&target_test_size, 4, MPI_INT, 0, MPI_COMM_WORLD);

		resizeVec(X,target_size,feature_size);
		resizeVec(X_test,target_test_size,feature_size);
		target.resize(target_size);
		target_test.resize(target_test_size);

		MPI_Bcast(&target[0], (target_size), MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&target_test[0], (target_test_size), MPI_FLOAT, 0, MPI_COMM_WORLD);
		for(int i1=0;i1<target_size;i1++){
			MPI_Bcast(&X[i1][0], feature_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
		}
		for(int i1=0;i1<target_test_size;i1++){
			MPI_Bcast(&X_test[i1][0], (feature_size), MPI_FLOAT, 0, MPI_COMM_WORLD);
		}
		memory_init(target_size,target_test_size);
	}

	M=feature_size;
	N=target_size;
	N_test=target_test_size;
	

	for(float p1=-9;p1<=0;p1=p1+0.3){
		gamma_values.push_back(pow(10,p1));
	}
	for(float p1=-9;p1<=0;p1=p1+0.3){
		C_values.push_back(pow(10,p1));
	}
	MPI_Barrier(MPI_COMM_WORLD);
	tol = 0.001;
	C = 1;

	//creation of kernel matrix
	//std::ofstream K_file("Kernel matrix");
	if(myrank==0){
		cout<<"Total number of gamma values: " << gamma_values.size() << endl;
		cout<<"Total number of C values: " << C_values.size() << endl;
	}
	G=gamma_values.size();
	W=world_size;
	load_per_processor=G/W;
	for(int i2=myrank*(load_per_processor);i2<(myrank+1)*load_per_processor;i2++){
		gamma_indices.push_back(i2);
	}
	if(myrank<G%W){
		gamma_indices.push_back(myrank+(W*load_per_processor));
	}
	cout<<"Number of gamma values in node " << myrank << ": " << gamma_indices.size() << endl;
	MPI_Barrier(MPI_COMM_WORLD);

	for(std::vector<int>::size_type ind = 0; ind != gamma_indices.size() ; ind++){
		//cout << "Computeation started for node: " << myrank << endl;
		gama=gamma_values[gamma_indices[ind]];
		#pragma omp parallel 
		{ 
			#pragma omp for private(s, t, l, temp)
			for(s=0;s<N;s++)
			{
				//cout << s << "\n";
				for(t=0;t<N;t++)
				{
					temp = 0.0;
					for(l=0; l<M; l++)
					{
						temp = temp+((X[s][l]-X[t][l])*(X[s][l]-X[t][l]));
					}
					temp = -1.0*gama*temp;
					K[s][t] = exp(temp);			//radial basis function
					//K_file<<K[s][t]<<" ";
				}
				//K_file<<endl;
			}
		}
		/*std::ofstream outfx("X");
		for(int p=0;p<N;p++){
			for(int k=0;k<M;k++)
				outfx << X[p][k] << " ";
			outfx << endl;
		}*/
		#pragma omp parallel 
		{
			#pragma omp for private(s, t, l, temp)
			for(s=0;s<N_test;s++)
			{
				//cout << s << "\n";
				for(t=0;t<N;t++)
				{
					temp = 0.0;
					for(l=0; l<M; l++)
					{
						temp += pow(X_test[s][l]-X[t][l],2);
					}
					temp = -1.0*gama*temp;
					K_test[s][t] = exp(temp);			//radial basis function
				
				}
			}
	    }
		//print K matrix to a file
		/*std::ofstream K_file("Kernel matrix");
		for(s=0;s<N;s++)
		{
			//cout << s << "\n";
			for(t=0;t<N;t++)
			{
				//temp = 0.0;
				//temp = -1.0*gama*temp;
				//K[s][t] = exp(temp);			//radial basis function
				K_file<<K[s][t]<<" ";
			}
			K_file<<endl;
		}*/
		
		//cout << myrank << "Kernel computations for train and test vectors completed! \n";
		
		for(std::vector<int>::size_type Cind = 0; Cind != C_values.size(); Cind++){
			C=C_values[Cind];
			//cout<<"Gamma : " << gama << " C entered : "<< C << endl;
			SMO();
			/*std::ofstream outf("alpha.out");
			for(int p=0;p<N;p++)
				cout << alpha[p] << "\t";
			//cout<<"SMO completed for "<< myrank << endl;*/
			acc = test();
			if(acc>acc_max){
				acc_max=acc;
				C_min=C;
				gamma_values_min=gama;
				cout << "New optimum model found in process " << myrank << "!!" << "gamma_values: " << gamma_values_min << "C: " << C_min << "Best Accuracy: " << acc_max << "\n";
			}
			I0.clear();I1.clear();I2.clear();I3.clear();I4.clear();	//clearing out the vectors for next iteration of C
		}
	}
	cout << "Optimum values for node " << myrank << "!!" << " gamma_values: " << gamma_values_min << " C: " << C_min << " Best Accuracy: " << acc_max << "\n";
	MPI_Barrier(MPI_COMM_WORLD);
	if(myrank!=0){
		MPI_Send(&gamma_values_min, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
		MPI_Send(&C_min, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
		MPI_Send(&acc_max, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
	}
	else if(myrank==0){
		float *final_gamma=new float[world_size];
		float *final_C=new float[world_size];
		float *final_acc=new float[world_size];

		final_gamma[0]=gamma_values_min;
		final_C[0]=C_min;
		final_acc[0]=acc_max;
		
		for(int i=1;i<world_size && world_size>1;i++){
			MPI_Recv(final_gamma+i,1,MPI_FLOAT, i, tag, MPI_COMM_WORLD,&status);
			MPI_Recv(final_C+i,1,MPI_FLOAT, i, tag, MPI_COMM_WORLD,&status);
			MPI_Recv(final_acc+i,1,MPI_FLOAT, i, tag, MPI_COMM_WORLD,&status);
		}
		int best_index = max_element(final_acc, final_acc + world_size) - final_acc;
		cout << "Best Model Parameters: Gamma = "<<final_gamma[best_index] << " C = " << final_C[best_index] << " Accuracy = "<< final_acc[best_index] << endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
	//outf.close();
	//acc = test_on_data(testfile);
	return 0;
}
