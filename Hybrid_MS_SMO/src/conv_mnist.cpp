

#include "includes/computeL_H.h"


int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void read_Mnist(string filename, vector<vector<float> > &vec, bool nn, int numimages)
{
    ifstream file (filename.c_str(), ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = ReverseInt(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = ReverseInt(n_cols);
				if(nn){
								number_of_images=numimages;
				}
        for(int i = 0; i < number_of_images; ++i)
        {
            vector<float> tp;
            for(int r = 0; r < n_rows; ++r)
            {
                for(int c = 0; c < n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    tp.push_back((float)temp);
                }
            }
            vec.push_back(tp);
        }
    }
}


void read_Mnist_Label(string filename, vector<float> &vec, bool nn, int numimages)
{
    ifstream file (filename.c_str(), ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &number_of_images,sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);

				if(nn){
								number_of_images=numimages;
				}
        for(int i = 0; i < number_of_images; ++i)
        {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            //vec[i]=(float)temp;
            vec.push_back((float)temp);
        }
    }
}



void mnist_data_processing(bool usepart)
{

    string tr_filename = "./datasets/mnist/train-images-idx3-ubyte";
    string tr_labelfname = "./datasets/mnist/train-labels-idx1-ubyte";  

    string te_filename = "./datasets/mnist/t10k-images-idx3-ubyte";
    string te_labelfname = "./datasets/mnist/t10k-labels-idx1-ubyte";   
          
    int tr_num_images = 60000;
    int te_num_images = 10000;    
    int image_size = 28 * 28;
	  cl1=1;
		cl2=8;	
		gama=3e-8;	
		//int tr_num_images=20000;
		//int te_num_images=2000;
    //read MNIST training images into float vector
    //vector<vector<float> > vec_tr;
    read_Mnist(tr_filename, vec_tr, usepart,tr_num_images);
    cout<<"Training Vector size: "<<vec_tr.size()<<endl;
    cout<<"Training Vector feature dimension: "<<vec_tr[0].size()<<endl;

    //read MNIST training labels into float vector
    //vector<float> vecl_tr(tr_images);
    //vecl_tr.reserve(tr_images);
    read_Mnist_Label(tr_labelfname, vecl_tr, usepart,tr_num_images);
    cout<<"Training Label Vector size: "<<vecl_tr.size()<<endl;

    //read MNIST test images into float vector
    //vector<vector<float> > vec_te;
    read_Mnist(te_filename, vec_te, usepart,te_num_images);
    cout<<"Test Vector size: "<<vec_te.size()<<endl;
    cout<<"Test Vector feature dimension: "<<vec_te[0].size()<<endl;

    //read MNIST test labels into float vector
    //vector<float> vecl_te(te_images);
    //vecl_te.reserve(te_images);
    read_Mnist_Label(te_labelfname, vecl_te, usepart,te_num_images);
    cout<<"Test Label Vector size: "<< vecl_te.size()<<endl;

}
