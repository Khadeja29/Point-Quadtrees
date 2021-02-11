#include <string>
#include <vector> 
using namespace std;
struct node{
node* north_west;
node* north_east; 
node* south_west;
node* south_east;
int x;
int y;
string city_name;
};class quadtree{
private:
	node*root;
	void insert(const int&x, const int&y , const string&city_name, node*&t)const;
	void makeEmpty(node* &t)const;
	void pretty_print(node *t)const;
	void find(const int&xcord, const int&ycord, const int &radius,node*t,vector<string> & result,vector<string> & visited);
	int tree_size(node*t)const;

public:
	quadtree();
	~quadtree();
	void insert(const int&x,const int&y , const string&city_name);
	void makeEmpty();
	void pretty_print()const;
	void find(const int&xcord, const int&ycord, const int& radius,vector<string>& result, vector<string>& visited);
	//int tree_size();
	
};