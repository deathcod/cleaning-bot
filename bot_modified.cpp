#include "radar_modified.h"
void opposite_points(point *a,point *b,point *c,triangle t)
{
	if(a->first!=t.x1 && a->second!=t.y1 && c->first!=t.x1 && c->second!=t.y1)
	{
		b->first=t.x1;
		b->second=t.y1;
	}
	else if(a->first!=t.x2 && a->second!=t.y2 && c->first!=t.x2 && c->second!=t.y2)
	{
		b->first=t.x2;
		b->second=t.y2;
	}
	else
	{
		b->first=t.x3;
		b->second=t.y3;
	}
}
bool isdelaunary(point *a,point *b,point *c,point *d)
{
	int xx=((a->first-c->first)*(a->first-b->first)+
		(a->second-c->second)*(a->second-b->second));
	xx*=((d->first-b->first)*(d->second-c->second)-
		(d->first-c->first)*(d->second-b->second));
	
	int yy=((a->second-c->second)*(a->first-b->first)-
		(a->first-c->first)*(a->second-b->second));
	yy*=((d->first-b->first)*(d->first-c->first)+
		(d->second-c->second)*(d->second-b->second));
	return(xx<yy);
}
void delanuary_triangulation(triangle t,point *d)
{
	point *a=(point *)malloc(sizeof(point));
	point *b=(point *)malloc(sizeof(point));
	point *c=(point *)malloc(sizeof(point));
	a->first=t.x1;
	a->second=t.y1;
	b->first=t.x2;
	b->second=t.y2;
	c->first=t.x3;
	c->second=t.y3;
	queue<line *>q;
	q.push(points_to_line(*a,*b));
	q.push(points_to_line(*b,*c));
	q.push(points_to_line(*c,*a));
	while(!q.empty())
	{
		printf("hello\n");
		line *x=q.front();
		q.pop();
		if(tri[*x].size()==1)
			continue;
		a->first=x->first.first;
		a->second=x->first.second;
		c->first=x->second.first;
		c->second=x->second.second;
		triangle *tt=points_to_triangle(*d,*a,*c);
		if(tt->x2==d->first && tt->y2==d->second)
		{
			int f=tt->x2;
			tt->x2=tt->x1;
			tt->x1=f;
			f=tt->y2;
			tt->y2=tt->y1;
			tt->y1=f;
		}
		else if(tt->x3==d->first && tt->y3==d->second)
		{
			int f=tt->x3;
			tt->x3=tt->x1;
			tt->x1=f;
			f=tt->y3;
			tt->y3=tt->y1;
			tt->y1=f;
		}
		make_counter_clockwise(tt);
		a->first=tt->x2;
		a->second=tt->y2;
		c->first=tt->x3;
		c->second=tt->y3;
		opposite_points(a,b,c,tri[*x][0]);
		if(b->first==d->first && b->second==d->second)
			opposite_points(a,b,c,tri[*x][1]);
		if(isdelaunary(a,b,c,d))
		{
			//printf("%d %d,%d %d,%d %d,%d %d\n",a->first,a->second,b->first,b->second,c->first,c->second,d->first,d->second);
			tt=points_to_triangle(*a,*b,*c);
			//printtriangle(*tt);
			delete_triangle(points_to_line(*a,*b),*tt);
			delete_triangle(points_to_line(*b,*c),*tt);
			delete_triangle(points_to_line(*c,*a),*tt);
			tt=points_to_triangle(*a,*c,*d);
			//printtriangle(*tt);
			delete_triangle(points_to_line(*a,*c),*tt);
			delete_triangle(points_to_line(*c,*d),*tt);
			delete_triangle(points_to_line(*d,*a),*tt);
			add_triangle(c,d,b);
			add_triangle(a,d,b);
			q.push(points_to_line(*c,*b));
			q.push(points_to_line(*a,*b));
		}
	}
}
int main(int argc, char const *argv[])
{
	point *x=(point *)malloc(sizeof(point));
	point *y=(point *)malloc(sizeof(point));
	point *z=(point *)malloc(sizeof(point));
	x->first=1000;
	x->second=1000;
	y->first=-1000;
	y->second=0;
	z->first=1000;
	z->second=0;
	add_triangle(x,y,z);
	add_triangle(y,z,x);
	add_triangle(z,x,y);
	for(std::map<line, std::vector<triangle> > :: iterator it=tri.begin();it!=tri.end();it++)
	{
		for(int j=0;j<tri[it->first].size();j++)
		{
			printline(it->first);
			printtriangle(tri[it->first][j]);
		}
	}
	printf("===============================================================\n");
	line *zz=points_to_line(*x,*y);
	int n;
	scanf("%d",&n);

	for(int i=0;i<n;i++)
	{
		scanf("%d %d",&x->first,&x->second);
		triangle tt=find_triangle(*zz,*x);
		int len=clearline.size();
		for(int j=0;j<len;j++)
		{
			//printline(clearline[i]);
			tri[clearline[j]][0].visited=0;
			if(tri[clearline[j]].size()==2)
				tri[clearline[j]][1].visited=0;
		}
		clearline.clear();
		//printtriangle(tt);
		delete_add_triangle(tt,x);
		/*line *check=(line*)malloc(sizeof(line));
		check->first.first=4;
		check->first.second=1;
		check->second.first=1000;
		check->second.second=0;
		sort_edge(check);
		printtriangle(tri[*check][0]);*/
		for(std::map<line, std::vector<triangle> > :: iterator it=tri.begin();it!=tri.end();it++)
		{
			//if(check->x1==(it->first).x1 && check->y1==(it->first).y1 && check->x2==(it->first).x2 && check->y2==(it->first).y2)
			for(int j=0;j<tri[it->first].size();j++)
			{
				printline(it->first);
				printtriangle(tri[it->first][j]);
				//printf("-------------------\n");
			}
		}
		delanuary_triangulation(tt,x);
		printf("==============================================================================\n");
	}
	return 0;
}