
#include "includes/computeL_H.h"

void createHeartVecs(string filename, vector<vector<float> > &vec, vector<float> &vecl){
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



void heart_data_processing()
{

    string tr_filename = "./datasets/heart/req_heart_scale.train";

    string te_filename = "./datasets/heart/req_heart_scale.test";
          


    createHeartVecs(tr_filename, vec_tr,vecl_tr);
    cout<<vec_tr.size()<<endl;
    cout<<vec_tr[0].size()<<endl;
    cout<<vecl_tr.size()<<endl;


    createHeartVecs(te_filename, vec_te,vecl_te);
    cout<<vec_te.size()<<endl;
    cout<<vec_te[0].size()<<endl;
    cout<<vecl_te.size()<<endl;
}

