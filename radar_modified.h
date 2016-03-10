#include <bits/stdc++.h>
using namespace std;
#ifndef M
#define M 1000000007
#endif
typedef pair<int,int> point;
typedef std::vector<point> vpp;
typedef long long ll;
#ifndef pb
#define pb push_back 
#endif 
int min(int x,int y){return(x<y)?x:y;}
int max(int x,int y){return(x>y)?x:y;}

typedef pair<point,point> line;
typedef struct $$
{
	int x1,x2,x3,y1,y2,y3,visited;
}triangle;	

void sort_edge(line *z);
void swappoint(point *x,point *y);
void sort_triangle(point *x,point *y,point *z);
void make_counter_clockwise(triangle *z);
void printline(line x);
void printtriangle(triangle x);
bool rightof(line a);
double dist(line x,point y);
bool equals(triangle x,triangle y);
void visitedtriangle(line *a,triangle x);
line *points_to_line(point a,point b);
triangle *points_to_triangle(point a,point b,point c);
void delete_triangle(line *x,triangle tt);
void add_triangle(point *a,point *b,point *c);
void delete_add_triangle(triangle tt,point *e);
triangle find_triangle(line z,point y);
std::map<line, std::vector<triangle> > tri;
std::vector<line> clearline;
void sort_edge(line *z)
{
	if(z->first.first > z->second.first || (z->first.first==z->second.first 
		&& z->first.second>z->second.second) )
	{
		int f=z->first.first;
		z->first.first= z->second.first;
		z->second.first=f;
		f= z->first.second;
		z->first.second=z->second.second;
		z->second.second=f;
	}
}//checked
void swappoint(point *x,point *y)
{
	int f=x->first;
	x->first=y->first;
	y->first=f;
	f=x->second;
	x->second=y->second;
	y->second=f;
}//checked
void sort_triangle(point *x,point *y,point *z)
{
	if(x->first>y->first)
		swappoint(x,y);
	else
		if(x->first==y->first&& x->second>y->second)
			swappoint(x,y);
	if(x->first>z->first)
		swappoint(x,z);
	else
		if(x->first==z->first&& x->second>z->second)
			swappoint(x,z);
}//checked
void make_counter_clockwise(triangle *z)
{
	point *x=(point *)malloc(sizeof(point));
	x->first=z->x2-z->x1;
	x->second=z->y2-z->y1;
	point *y=(point *)malloc(sizeof(point)); 
	y->first=z->x3-z->x2;
	y->second=z->y3-z->y2;
	if((x->first*y->second)-(x->second*y->first)<0)
	{
		int f=z->x2;
		z->x2=z->x3;
		z->x3=f;
		f=z->y2;
		z->y2=z->y3;
		z->y3=f;
	}
}//checked
/*
using the vector cross product if the value is + means it lies over the plane
and if its negative it lies down the plane..
*/
void printline(line x)
{
	printf("%d %d %d %d ",x.first.first,x.first.second,x.second.first,x.second.second);
}
void printtriangle(triangle x)
{
	printf("%d %d %d %d %d %d\n",x.x1,x.y1,x.x2,x.y2,x.x3,x.y3);
}
//checked
bool rightof(line a)
{
	return((a.first.first*a.second.second)-(a.first.second*a.second.first)<0);
}
//checked
double dist(line x,point y)
{
	double mx,my,constant,value;
	if(x.first.first==x.second.first)
	{
		mx=1;
		my=0;
		constant=-x.first.first;
		value=1;
	}
	else if(x.first.second==x.second.second)
	{
		my=1;
		mx=0;
		constant=-x.first.second;
		value=1;
	}
	else
	{
		my=-1;
		mx=(x.first.second-x.second.second);
		mx/=(x.first.first-x.second.first);
		constant=(x.first.second-mx*x.first.first);
		value=mx*mx;
		value+=1;
	}
	double z=mx*y.first+my*y.second+constant;
	z/=value;
	return fabs(z);
}
//checked
bool equals(triangle x,triangle y)
{
	return(x.x1==y.x1 && x.x2==y.x2 && x.x3==y.x3 && x.y1==y.y1 && x.y2==y.y2 && x.y3==y.y3);
}
void visitedtriangle(line *a,triangle x)
{
	if(equals(tri[*a][0],x))
		tri[*a][0].visited=1;
	else
		tri[*a][1].visited=1;
}
line *points_to_line(point a,point b)
{
	line *x=(line *)malloc(sizeof(line));
	x->first.first=a.first;
	x->first.second=a.second;
	x->second.first=b.first;
	x->second.second=b.second;
	sort_edge(x);
	return x;
}
//checked
triangle *points_to_triangle(point a,point b,point c)
{
	triangle *x=(triangle *)malloc(sizeof(triangle));
	sort_triangle(&a,&b,&c);
	x->x1=a.first;
	x->y1=a.second;
	x->x2=b.first;
	x->y2=b.second;
	x->x3=c.first;
	x->y3=c.second;
	x->visited=0;
	make_counter_clockwise(x);
	return x;
}
//checked
void delete_triangle(line *x,triangle tt)
{
	if(equals(tri[*x][0],tt))
		tri[*x].erase(tri[*x].begin());
	else 
		tri[*x].erase(tri[*x].begin()+1);
}
void add_triangle(point *a,point *b,point *c)
{
	triangle *t=points_to_triangle(*a,*b,*c);
	line *x=points_to_line(*a,*b);
	tri[*x].pb(*t);
}
void delete_add_triangle(triangle tt,point *e)
{
	point *a=(point *)malloc(sizeof(point));
	point *b=(point *)malloc(sizeof(point));
	point *c=(point *)malloc(sizeof(point));
	a->first=tt.x1;
	a->second=tt.y1;
	b->first=tt.x2;
	b->second=tt.y2;
	c->first=tt.x3;
	c->second=tt.y3;
	//printf("%d %d,%d %d,%d %d,\n",a->first,a->second,b->first,b->second,c->first,c->second);
	delete_triangle(points_to_line(*a,*b),tt);
	delete_triangle(points_to_line(*b,*c),tt);
	delete_triangle(points_to_line(*c,*a),tt);
	//printf("------------------------------------\n");
	//printf("%d %d,%d %d,%d %d,\n",a->first,a->second,b->first,b->second,c->first,c->second);
	add_triangle(a,b,e);
	add_triangle(a,e,b);
	add_triangle(e,b,a);
	//printf("------------------------------------\n");	
	add_triangle(b,c,e);
	add_triangle(c,e,b);
	add_triangle(e,b,c);
	//printf("------------------------------------\n");
	add_triangle(c,a,e);
	add_triangle(a,e,c);
	add_triangle(e,c,a);
	//printf("------------------------------------\n");
}
triangle find_triangle(line z,point y)
{
	//printline(z);
	triangle x;
	//printf("no problem1\n");
	if(tri[z][0].visited==0)
		x=tri[z][0];
	else
		x=tri[z][1];
	//printtriangle(x);
	//printf("no problem2\n");
	//here i have made the line which is clockwise...
	line *a=(line *)malloc(sizeof(line));
	a->first.first=x.x2-x.x1;
	a->first.second=x.y2-x.y1;
	a->second.first=y.first-x.x1;
	a->second.second=y.second-x.y1;
	line *b=(line *)malloc(sizeof(line));
	b->first.first=x.x3-x.x2;
	b->first.second=x.y3-x.y2;
	b->second.first=y.first-x.x2;
	b->second.second=y.second-x.y2;
	line *c=(line *)malloc(sizeof(line));
	c->first.first=x.x1-x.x3;
	c->first.second=x.y1-x.y3;
	c->second.first=y.first-x.x3;
	c->second.second=y.second-x.y3;
	/*
	here i am going to apply vector cross product on a point and a line to find if that point is on 
	the left or on the right of the line
	*/
	//printf("1\n");
	if(y.first==x.x1 && y.second==x.y1)
		return x;
	//printf("2\n");
	if(y.first==x.x2 && y.second==x.y2)
		return x;
	//printf("3\n");
	if(y.first==x.x3 && y.second==x.y3)
		return x;
	//printf("4\n");
	//cout<<rightof(*a)<<"\n"<<rightof(*b)<<"\n"<<rightof(*c)<<"\n"<<"\n";
	if(!rightof(*a) && !rightof(*b) && !rightof(*c))
		return x;
	//printf("5\n");
	int whichop=0;
	if(rightof(*b))
		whichop+=1;
	if(rightof(*c))
		whichop+=2;
	point *aa=(point *)malloc(sizeof(point));
	point *bb=(point *)malloc(sizeof(point));
	point *cc=(point *)malloc(sizeof(point));
	aa->first=x.x1;
	aa->second=x.y1;
	bb->first=x.x2;
	bb->second=x.y2;
	cc->first=x.x3;
	cc->second=x.y3;
	a=points_to_line(*aa,*bb);
	b=points_to_line(*bb,*cc);
	c=points_to_line(*cc,*aa);
	clearline.pb(*a);
	clearline.pb(*b);
	clearline.pb(*c);
	//printf("------1\n");
	visitedtriangle(a,x);
	//printf("------2\n");
	visitedtriangle(b,x);
	//printf("------3\n");
	visitedtriangle(c,x);
	//printf("---------%d %d\n",y.x,y.y );
	//printline(z);
	switch(whichop)
	{
		case 0:
			return find_triangle(*a,y);
		case 1:
			return find_triangle(*b,y);
		case 2:
			return find_triangle(*c,y);
		case 3:
			if(dist(*b,y)<dist(*c,y))
				return find_triangle(*b,y);
			else
				return find_triangle(*c,y);
	}

}