#include "includes/computeL_H.h"

void update_f() // myI1 is i_low myI2 is i_up
{
		yy1 = myt[0];
		yy2 = myt[1];
		vector<int>::iterator myI0_itr, myI1_itr, myI2_itr, myI3_itr, myI4_itr;
		alpha1_old = alpha_old_new_arr[0];
		alpha2_old = alpha_old_new_arr[1];
		alpha1_new = alpha_old_new_arr[2];
		alpha2_new = alpha_old_new_arr[3];
		int z1,z2,i_up1, i_low1;
		for(int i=0;i<myN;i++)
		{
			float kern1= mykernel_calc(i,1);
	        float kern2= mykernel_calc(i,2);
			float myfcache_old = myfcache[i];

			myfcache[i] = myfcache[i] + ((alpha1_new-alpha1_old)*yy1*kern1) + ((alpha2_new-alpha2_old)*yy2*kern2);

		}


		//calculate the process ranks z1 and z2 which have the two alphas, and local i_up and i_low
		if(i_up<(no_of_big_proc*row_big)){ 
			z1 = ((i_up) - ((i_up)%row_big))/row_big;
			i_z1 = ((i_up)%row_big);
		}
		else{
			i_up1 = (i_up) - (no_of_big_proc*row_big);
			z1 = (i_up1 - (i_up1%row_small))/row_small;
			z1 = z1+(no_of_big_proc);
			i_z1 = (i_up1%row_small);
		}
		if(i_low<(no_of_big_proc*row_big)){
			z2 = ((i_low) - ((i_low)%row_big))/row_big;
			i_z2 = ((i_low)%row_big);
		}
		else{
			i_low1 = (i_low) - (no_of_big_proc*row_big);
			z2 = (i_low1 - (i_low1%row_small))/row_small;
			z2 = z2+(no_of_big_proc);
			i_z2 = (i_low1%row_small);
		}

		
		if(myrank == z1){
			//find and remove i_z1
			myI0_itr = find(myI0.begin(), myI0.end(), i_z1);
			if(myI0_itr != myI0.end()){     //in myI0
			myI0.erase(myI0_itr);
			}
			else{       //not in myI0
				myI1_itr = find(myI1.begin(), myI1.end(), i_z1);
				if(myI1_itr != myI1.end()){     //in myI1
				    myI1.erase(myI1_itr);
				}
				else{   //not in myI0 and myI1
				    myI2_itr = find(myI2.begin(), myI2.end(), i_z1);
				    if(myI2_itr != myI2.end()){ //in myI2
					myI2.erase(myI2_itr);
				    }
				    else{   //not in myI0, myI1, myI2
					myI3_itr = find(myI3.begin(), myI3.end(), i_z1);
					if(myI3_itr != myI3.end()){ //in myI3
					    myI3.erase(myI3_itr);
					}
					else{   //not in myI0, myI1, myI2, myI3
					    myI4_itr = find(myI4.begin(), myI4.end(), i_z1);
					    if(myI4_itr != myI4.end()){ //in myI3
						myI4.erase(myI4_itr);
					    }
					}
				    }

				}
			}
			
			//update myI0, myI1, myI2, myI3, myI4
			if(alpha1_new>0 && alpha1_new<C){
			myI0.push_back(i_z1);
			}
			else{
				if(alpha1_new == 0){
				    if(mytarget[i_z1] == -1){
					myI4.push_back(i_z1);
				    }
				    else{   //+1 class
					myI1.push_back(i_z1);
				    }
				}
				else if(alpha1_new == C){
				    if(mytarget[i_z1] == -1){
					myI2.push_back(i_z1);
				    }
				    else{   //+1 class
					myI3.push_back(i_z1);
				    }

				}
				else{
				    //cout<<"alpha1_new is not in legal range"<<endl;
				}
			}
			
		
		}
		if(myrank == z2){
			//find and remove i_z2
			myI0_itr = find(myI0.begin(), myI0.end(), i_z2);
			if(myI0_itr != myI0.end()){     //in myI0
			myI0.erase(myI0_itr);
			}
			else{       //not in myI0
				myI1_itr = find(myI1.begin(), myI1.end(), i_z2);
				if(myI1_itr != myI1.end()){     //in myI1
				    myI1.erase(myI1_itr);
				}
				else{   //not in myI0 and myI1
				    myI2_itr = find(myI2.begin(), myI2.end(), i_z2);
				    if(myI2_itr != myI2.end()){ //in myI2
					myI2.erase(myI2_itr);
				    }
				    else{   //not in myI0, myI1, myI2
					myI3_itr = find(myI3.begin(), myI3.end(), i_z2);
					if(myI3_itr != myI3.end()){ //in myI3
					    myI3.erase(myI3_itr);
					}
					else{   //not in myI0, myI1, myI2, myI3
					    myI4_itr = find(myI4.begin(), myI4.end(), i_z2);
					    if(myI4_itr != myI4.end()){ //in myI3
						myI4.erase(myI4_itr);
					    }
					}
				    }
				}
			}

			//update local I0, I1, I2, I3, I4
			if(alpha2_new>0 && alpha2_new<C){
			myI0.push_back(i_z2);
			}
			else{
				if(alpha2_new == 0){
				    if(mytarget[i_z2] == -1){
					myI4.push_back(i_z2);
				    }
				    else{   //+1 class
					myI1.push_back(i_z2);
				    }
				}
				else if(alpha2_new == C){
				    if(mytarget[i_z2] == -1){
					myI2.push_back(i_z2);
				    }
				    else{   //+1 class
					myI3.push_back(i_z2);
				    }

				}
				else{
				    //cout<<"alpha2_new is not in legal range"<<endl;
				}
			}

		}
   

}
