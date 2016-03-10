#include <bits/stdc++.h>
#include<radar.h>
using namespace std;
#ifndef M
#define M 1000000007
#endif
typedef pair<int,int>pp;
typedef std::vector<pp> vpp;
typedef long long ll;
#ifndef pb
#define pb push_back 
#endif 
int min(int x,int y){return(x<y)?x:y;}
int max(int x,int y){return(x>y)?x:y;}

typedef struct $$$
{
	int x,y;	
}point;								//this will store a point for pont to triangle

typedef struct $
{
	int x1,y1,x2,y2;
	bool operator<(struct $ const &a)const
	{
		if(x1<a.x1)
			return true;
		else
			if(x1==a.x1 && y1<a.y1)
				return true;
			else
				if(y1==a.y1 && x2<a.x2)
					return true;
				else
					return(x2==a.x2 && y2<a.y2);
	}
	/*
	this operator is used to make the edges sort acccordingly here I have not
	mentioned any kind of sorting for the edges leaving for later..
	I just made it so that input can be stored in the map as it was showing error as of the 
	operator in map cannot sort the struct values.. thats it..!!
	*/
}line;								//this will store the line used for side to triangle

typedef struct $$
{
	int x1,x2,x3,y1,y2,y3,visited;
}triangle;	

line points_to_line(point a,point b)
{
	line x=(line *)malloc(sizeof(line));
	x.x1=a.x;
	x.y1=a.y;
	x.x2=b.x;
	x.y2=b.y;
	return x;
}

triangle points_to_triangle(point a,point b,point c)
{
	triangle x=(triangle *)malloc(sizeof(triangle));
	x.x1=a.x;
	x.y1=a.y;
	x.x2=b.x;
	x.y2=b.y;
	x.x3=c.x;
	x.y3=c.y;
	return x;
}
int main(int argc, char const *argv[])
{
	std::map<point, std::vector<point> > P2P;//point to point adjacent matrix
									  //this will store all the connections 

	std::map<line,pair<triangle,triangle> > S2T;//side to triangle adjacent matrix
	std::map<point, std::vector<triangle> > P2T;//point to triangle adjacent matrix

	point x=(point *)malloc(sizeof(point));
	x.x=1000;
	x.y=1000;
	point y=(point *)malloc(sizeof(point));
	y.x=-1000;
	y.y=0;
	point z=(point *)malloc(sizeof(point));
	y.x=1000;
	y.y=0;
	P2P[x].pb(y);
	P2P[x].pb(z);
	P2P[y].pb(z);
	P2P[y].pb(x);
	P2P[z].pb(y);
	P2P[z].pb(x);
	//point to point first three points done
	//-------------------------------------------------------------------------------


	S2T[points_to_line(x,y)].first=points_to_triangle(x,y,z);
	S2T[points_to_line(y,z)].first=points_to_triangle(x,y,z);
	S2T[points_to_line(z,x)].first=points_to_triangle(x,y,z);

	//line to triangles done
	//------------------------------------------------------------------------------

	P2T[x].pb(points_to_triangle(x,y,z));
	P2T[y].pb(points_to_triangle(x,y,z));
	p2t[z].pb(points_to_triangle(x,y,z));

	//points to triangle done
	//-----------------------------------------------------------------------------
	//==================FIRST TASK COMPLETED=======================================



	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d %d",&x,&y);
		triangle x=radar()
	}
	return 0;
}