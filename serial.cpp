#include <bits/stdc++.h>
#include <fstream>
using namespace std;

vector<vector<int>> do_conv(vector<vector<int>> padded_data) {
    vector<vector<int>> conv_image_data;
    vector<vector<double>> filter;
    filter = {{1.0,2.0,1.0},{2.0,4.0,2.0},{1.0,2.0,1.0}};
    int rows = padded_data.size();
    int cols = padded_data[0].size();


    for (int i=1;i<rows-1;i++) {
        vector<int> convolved_row_data;
        for (int j=1;j<cols-1;j++) {
            double a = double(padded_data[i-1][j-1])*filter[0][0] + double(padded_data[i-1][j])*filter[0][1] + double(padded_data[i-1][j+1])*filter[0][2];
            a += double(padded_data[i][j-1])*filter[1][0] + double(padded_data[i][j])*filter[1][1] + double(padded_data[i][j+1])*filter[1][2];
            a += double(padded_data[i+1][j-1])*filter[2][0] + double(padded_data[i+1][j])*filter[2][1] + double(padded_data[i+1][j+1])*filter[2][2];
            convolved_row_data.push_back(round(a/16.0));
        }
        conv_image_data.push_back(convolved_row_data);
    }

    return conv_image_data;

}

int main(int argc, char** argv ) {
		ifstream Myfile;
		ofstream myfile2;
		string img_str;
		vector<int> v;

		string in_filename = "image_data_k.txt";
		string out_filename = "output_k.txt";
		char c[3] = {'b','g','r'};

		for (int t=0;t<3;t++) {
			vector<vector<int>> pixel_data;
			in_filename[11] = c[t];
			Myfile.open(in_filename);
			//reading image file
			if (Myfile.is_open()) {
				while(getline(Myfile, img_str)) {
					int k=0;
					vector<int> row;
					for (int i=0;i<img_str.length();i++) {
						if (img_str[i]==' ') {
							row.push_back(k);
							k=0;
						} else if (img_str[i]=='\n') cout<<"*";
						else {
							k*=10;
							k+=int(img_str[i]) - 48;
						}
					}
					pixel_data.push_back(row);
				}
			} else {
				cout<<"Error in image input";
				return 0;
			}
			Myfile.close();
			
			vector<vector<int>> conv_data;
			conv_data = do_conv(pixel_data);


			//writing it to output.txt
			out_filename[7] = c[t];
			myfile2.open(out_filename);
			for (int i=0;i<conv_data.size();i++) {
				for (int j=0;j<conv_data[0].size();j++) {
					myfile2 << to_string(conv_data[i][j]) << " ";
				}
				myfile2 << endl;
			}
			myfile2.close();
		}
	   return 0;
}
