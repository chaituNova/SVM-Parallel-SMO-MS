#include "includes/computeL_H.h"
void SMO()
{
	int numChanged = 0;
	int examineAll = 1;
	int i1,i2, y2;
	float alpha2,F2;
	int inner_loop_success = 1;
	//myalpha = new float[myN];
	//myfcache = new float[myN];


	for(int p=0;p<myN;p++)				//fcache, alpha, I_1 and I_4 initialisation
	{
		myalpha[p] = 0.0;
		if(mytarget[p] == 1)
		{
			myfcache[p] = -1.0;
			myI1.push_back(p);
			myi_up = p;
		}
		else
			myfcache[p] = 1.0;
			myI4.push_back(p);
			myi_low = p;
	}
	
	//get b_up and b_low
	//calc_b();
	myb_up = -1.0;
	myb_low = 1.0;

	b_up = -1.0;
	b_low = 1.0;
	//find initial i_up and i_low
	if(myrank == 0){
		
		for (int i = 0; i<N; i++){
			if(target[i] == 1){
				i_up = i;
				//break;
			}
		}
		for (int i = 0; i<N; i++){
			if(target[i] == -1){
				i_low = i;
				//break;
			}
		}
	}
	MPI_Bcast(&i_up, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&i_low, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
			inner_loop_success = 1;
			while((b_up<=b_low-2*tol) && (inner_loop_success != 0))
			{
				if(myrank == 0){
					inner_loop_success = update_alpha(i_up,i_low);
				}
				//braadcast inner_loop_success
				MPI_Bcast(&inner_loop_success, 1, MPI_INT, 0, MPI_COMM_WORLD);
				
				if(inner_loop_success == 1){
					if(myrank == 0){
						alpha_old_new_arr[0] = alpha1_old;
						alpha_old_new_arr[1] = alpha2_old;
						alpha_old_new_arr[2] = alpha1_new;
						alpha_old_new_arr[3] = alpha2_new;
						myt[0] = target[i_up];
						myt[1] = target[i_low];
						for(int i = 0; i<M; i++){	//creating X(i_up) and X(i_low) arrays for broadcast
							myX1[i] = X[i_up][i];
							myX2[i] = X[i_low][i];
						}
					}
					//broadcast alpha1_new, alpha2_new, X(i_up), X(i_low), target(i_up) and target(i_low)
					//these are required to update Fi
					MPI_Bcast(alpha_old_new_arr, 4, MPI_FLOAT, 0, MPI_COMM_WORLD);
					MPI_Bcast(myX1, M, MPI_FLOAT, 0, MPI_COMM_WORLD);
					MPI_Bcast(myX2, M, MPI_FLOAT, 0, MPI_COMM_WORLD);
					MPI_Bcast(myt, 2, MPI_INT, 0, MPI_COMM_WORLD);
					
					update_f();	//updates Fs and I0, I1, I2, I3, I4 in z1 and z2 processes
					calc_b();	//calculates local b_up, b_low, i_up, i_low
					MPI_Gather(&myb_up, 1, MPI_FLOAT, b_up_arr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
					MPI_Gather(&myb_low, 1, MPI_FLOAT, b_low_arr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
					MPI_Gather(&myi_up_g, 1, MPI_INT, &(i_up_arr[0]), 1, MPI_INT, 0, MPI_COMM_WORLD);
					MPI_Gather(&myi_low_g, 1, MPI_INT, &(i_low_arr[0]), 1, MPI_INT, 0, MPI_COMM_WORLD);
					////cout<<myrank<<": Done with gathering of local b_up, b_low, i_up and i_low"<<endl;
					if(myrank == 0){
						b_up = b_up_arr[0];
						i_up = i_up_arr[0];
						b_low = b_low_arr[0];
						i_low = i_low_arr[0];
						for(int i = 1; i<size; i++){
							if(b_up_arr[i]<b_up){
								b_up = b_up_arr[i];
								i_up = i_up_arr[i];
							}
							if(b_low_arr[i]>b_low){
								b_low = b_low_arr[i];
								i_low = i_low_arr[i];
							}	
						}
						b_arr[0] = b_up;
						b_arr[1] = b_low;
						i_arr[0] = i_up;
						i_arr[1] = i_low;
						////cout<<"0: b_up, b_low, i_up, i_low determined is "<<b_up<<" "<<b_low<<" "<<i_up<<" "<<i_low<<endl;
					}
					//broadcast b_up, b_low, i_up, i_low					
					MPI_Bcast(b_arr, 2, MPI_FLOAT, 0, MPI_COMM_WORLD);
					MPI_Bcast(i_arr, 2, MPI_INT, 0, MPI_COMM_WORLD);
					////cout<<myrank<<": Done with broadcast of global b_up, b_low, i_up and i_low to all the processes"<<endl;
					b_up = b_arr[0];
					i_up = i_arr[0];
					b_low = b_arr[1];
					i_low = i_arr[1];
					//cout<<myrank<<": Exiting while loop: global b_up, global b_low, global i_up, global i_low: "<<b_up<<" "<<b_low<<" "<<i_up<<" "<<i_low<<endl;
					
				}
		}
			
	/*if (myrank == 0){
		cout << "Final Bup and blow iup and ilow" << b_up << " " << b_low << " " << i_up <<" " << i_low <<endl;
	}*/
	
}
