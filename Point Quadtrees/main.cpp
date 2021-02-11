#include <iostream>
#include "quadtree.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
int main()
{
	//open cities file
	quadtree city_tree;
	ifstream input;
	string filename="cities.txt";
	input.open(filename.c_str());
	string line1;
	int max_x,max_y;
	getline(input,line1);
	istringstream s1(line1);
	s1>>max_x >>max_y;	
	if ( max_x <0 || max_y<0)
	{
		cout<< "Incorrect file.Contains negative values for coordinates"<<endl;
	}
	else
	{
		
		string line, city_name,xi,yi;
		bool check = false;
		while (getline(input,line))
		{ 
			istringstream ss(line);
			ss>>city_name>>xi>>yi;
			int x = stoi(xi);
			int y = stoi(yi);

			if( x<0 || y<0)
			{
				cout<<"Incorrect file format.City(s) has negative values for coordinates"<<endl;
				break;
			}
			else if ( x<max_x+1 && y<max_y+1)
			{
				check = true;
				city_tree.insert(x,y,city_name);
			}
			else
			{
				//cout <<city_name<<" is no where on the map."<<endl;
			}
		}
		if (check == true)
		{city_tree.pretty_print();
		 /*int tree_size= city_tree.tree_size();
		 cout<<"\n"<< "tree size = "<<tree_size<<endl;*/
		}
	}
	cout<<endl;

	ifstream input2;
	string filename2="queries.txt";
	input2.open(filename2.c_str());

	string line2;
	string xf,yf,rf;

	while(getline(input2,line2))
	{
		vector<string>visited;
        vector<string>result;
		istringstream s2(line2);
		s2>>xf>>yf>>rf;

		int xcord = stoi(xf);
		int ycord = stoi(yf);
		int radius = stoi(rf);
		//cout <<xcord<<" "<<ycord<<" "<<radius<<endl;
		city_tree.find(xcord,ycord,radius,result,visited);
		
		if ( result.size() == 0)
		{
			cout <<"<None>"<<endl;
		}

		else
		{
			for (int i = 0; i < result.size(); i++)
			{
				if( i == result.size()-1)
				{
					cout<< result[i]<<endl;
				}
				else
				{
					cout<< result[i]<<",";
				}
			}
		}

		for (int i = 0; i < visited.size(); i++)
			{
				if( i == visited.size()-1)
				{
					cout<< visited[i]<<endl;
				}
				else
				{
					cout<< visited[i]<<",";
				}
			}
		cout<<endl;
		result.clear();
		visited.clear();
		
	}
	return 0;
}