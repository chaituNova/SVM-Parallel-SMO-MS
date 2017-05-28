
#include "includes/computeL_H.h"

void createA9aVecs(string filename, vector<vector<float> > &vec, vector<float> &vecl, bool nn, int numex){
	ifstream file (filename.c_str());
	if (file.is_open())
	{
		string str="";
		int cnt=0;	
		while(getline(file,str)){
						cnt++;
			stringstream ss(str);
			float fp;
			ss >> fp;
			vecl.push_back(fp);
			if(ss.peek() == ','){
				ss.ignore();
			}
			vector<float> tp;
			while (ss >> fp)
    			{
    					
			        tp.push_back(fp);
			        if (ss.peek() == ',')
			            ss.ignore();
		    	}
			vec.push_back(tp);
			if(nn && (cnt >=numex)){
				break;
			}
		}
	}	
}



void a9a_data_processing()
{

    string tr_filename = "./datasets/a9a/req_a9a.train";

    string te_filename = "./datasets/a9a/req_a9a.test";
          

		int tr_exs=10;
		int te_exs=10;
		bool bnn=false;						
		cl1=+1;
		cl2=-1;
		gama=3e-2;
    createA9aVecs(tr_filename, vec_tr,vecl_tr,bnn,tr_exs);
    cout<<vec_tr.size()<<endl;
    cout<<vec_tr[0].size()<<endl;
    cout<<vecl_tr.size()<<endl;


    createA9aVecs(te_filename, vec_te,vecl_te,bnn,te_exs);
    cout<<vec_te.size()<<endl;
    cout<<vec_te[0].size()<<endl;
    cout<<vecl_te.size()<<endl;
}

