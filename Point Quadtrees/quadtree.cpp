#include <iostream>
#include "quadtree.h"
#include <string>
#include <vector> 
#include <cmath>
using namespace std;

quadtree:: quadtree()
{
	root=nullptr;
}

/* Public Insert functions: takes name of city 
   and coordinates from the user and calls the 
   private insert function
*/
void quadtree:: insert(const int&x, const int&y , const string&city_name)
{
	insert(x,y,city_name,root);
}


void quadtree:: insert(const int& x, const int& y , const string&city_name, node* &t)const
{
	if (t== nullptr) //empty tree or the perfect position found to insert the new citiy
	{
		t=new node;
		t->city_name= city_name;
		t->x=x;
		t->y=y;
		t->north_west= nullptr;
		t->north_east= nullptr;
		t->south_west= nullptr;
		t->south_east= nullptr;

	}
	else if (x < t->x) 
	{
		if( y < t->y)
		{
			insert(x,y,city_name,t->south_west);
		}
		else if( y > t->y)
		{
			insert(x,y,city_name,t->north_west);
			
		}
		else
		{
			insert(x,y,city_name,t->north_west);
			
		}
	}
	else if (x >t->x) // x of current root or node is equal to x of inserted node
	{
		if( y < t->y)
		{
			insert(x,y,city_name,t->south_east);}
			
		else if( y > t->y)
		{
			insert(x,y,city_name,t->north_east);
			
		}
		else
		{
			insert(x,y,city_name,t->north_east);
			
		}
	}
	else if (x == t->x) // x of current rrot or node is equal to x of inserted node
	{
		if ( y < t->y)
		{
			insert(x,y,city_name,t->south_east);
		}
			
		else if ( y > t->y)
		{
			insert(x,y,city_name,t->north_east);
			
		}
		else if ( y == t->y) //both cities are equal, no duplicates do nothing
		{
			;
		}
	}
}

void quadtree:: makeEmpty()
{
	makeEmpty(root);
}

void quadtree :: makeEmpty(node* &t) const
{
	if(t!= nullptr)
	{
		makeEmpty(t->north_west);
		makeEmpty(t->north_east);
		makeEmpty(t->south_west);
		makeEmpty(t->south_east);
		delete t;
	}
	t= nullptr;
}

quadtree:: ~quadtree()
{
	makeEmpty();
}

//PUBLIC PRETTY PRINT
void quadtree:: pretty_print()const 
{ 
	if( root !=nullptr)
	{
		pretty_print(root);
	}

}
//PRIVATE PRETTY PRINT
void quadtree :: pretty_print (node*t)const
{
	if (t!= nullptr)
	{
		cout<< t->city_name<<endl;
		pretty_print(t->south_east);
		pretty_print(t->south_west);
		pretty_print(t->north_east);
		pretty_print(t->north_west);
	}
}

void quadtree :: find(const int&xcord, const int&ycord, const int&radius,vector<string> & result,vector<string> & visited)
{
	find(xcord,ycord,radius,root,result,visited);
}

void quadtree :: find(const int&xcord, const int&ycord, const int&radius, node*t,vector<string> & result,vector<string> & visited)
{
	if (root != nullptr) 
	{
		
		if (t == nullptr) { return;}
		//case 13 : LIES WITHIN THE CIRCLE 
		double dist = sqrt(pow((xcord-t->x),2)+pow((ycord-t->y),2));
		visited.push_back(t->city_name);
		if( dist <= radius)
		{
			result.push_back(t->city_name);
			
			find(xcord,ycord,radius,t->south_east,result,visited);
			find(xcord,ycord,radius,t->south_west,result,visited);
			find(xcord,ycord,radius,t->north_east,result,visited);
			find(xcord,ycord,radius,t->north_west,result,visited);
		}
		//case 1
		else if ((t->y > (ycord+radius)) && (t->x < (xcord-radius)))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_east,result,visited);
		}
		//case 3
		else if (t->y > (ycord+radius) &&(t->x > (xcord+radius)))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_west,result,visited);
		}
		//case 6
		else if(t->y < (ycord-radius) && t->x < (xcord-radius))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->north_east,result,visited);
		}
		//case 8
		else if( t->x > (xcord+radius) && t->y < (ycord-radius))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->north_west,result,visited);
		}
		//case 2
		else if( t->x > (xcord-radius) && t->x < (xcord+radius) && t->y > (ycord+radius))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_east,result,visited);
			find(xcord,ycord,radius,t->south_west,result,visited);
		}
		//case 4
		else if (t->y < (ycord+radius) && t->y >(ycord-radius) && t->x <(xcord-radius))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_east,result,visited);
			find(xcord,ycord,radius,t->north_east,result,visited);
		}
		//case 5
		else if(t->y < (ycord+radius) && t->y >( ycord-radius) && t->x > (xcord+radius))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_west,result,visited);
			find(xcord,ycord,radius,t->north_west,result,visited);
		}
		//case 7
		else if (t->x >( xcord-radius) && t->x < (xcord+radius) && t->y < (ycord-radius))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->north_east,result,visited);
			find(xcord,ycord,radius,t->north_west,result,visited);
		}
		//case 9
		else if (t->x > (xcord-radius) && t->y < (ycord+radius) && t->y >(ycord) && t->x <(xcord))
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_east,result,visited);
			find(xcord,ycord,radius,t->south_west,result,visited);
			find(xcord,ycord,radius,t->north_east,result,visited);
		}
		//case 10
		else if (t->x < (xcord+radius) && t->y < (ycord+radius) && t->y > ycord && t->x > xcord)
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_east,result,visited);
			find(xcord,ycord,radius,t->south_west,result,visited);
			find(xcord,ycord,radius,t->north_west,result,visited);
		}
		//case 11
		else if (t->x > (xcord-radius) && t->y >(ycord-radius) && t->x <xcord && t->y <ycord )
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_east,result,visited);
			find(xcord,ycord,radius,t->north_east,result,visited);
			find(xcord,ycord,radius,t->north_west,result,visited);
		}
		//case 12
		else if (t->x < (xcord+radius) && t->y > (ycord-radius) && t->y < ycord && t->x > xcord)
		{
			//visited.push_back(t->city_name);
			find(xcord,ycord,radius,t->south_west,result,visited);
			find(xcord,ycord,radius,t->north_east,result,visited);
			find(xcord,ycord,radius,t->north_west,result,visited);
		}
		
	}
	
}






  