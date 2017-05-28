
#include "includes/computeL_H.h"

void createSpliceVecs(string filename, vector<vector<float> > &vec, vector<float> &vecl){
	ifstream file (filename.c_str());
	if (file.is_open())
	{
		string str="";
		
		while(getline(file,str)){
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
		}
	}	
}



void splice_data_processing()
{

    string tr_filename = "./datasets/splice/req_splice_tr.data";

    string te_filename = "./datasets/splice/req_splice_te.data";
          
		gama=3e-2;
		cl1=1;cl2=2;
    createSpliceVecs(tr_filename, vec_tr,vecl_tr);
    cout<<vec_tr.size()<<endl;
    cout<<vec_tr[0].size()<<endl;
    cout<<vecl_tr.size()<<endl;


    createSpliceVecs(te_filename, vec_te,vecl_te);
    cout<<vec_te.size()<<endl;
    cout<<vec_te[0].size()<<endl;
    cout<<vecl_te.size()<<endl;
}

