//my first working bot 
// loved to make it :p


#include <bits/stdc++.h>
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
typedef struct $
{
	int x,y,dis;	
}ss;
int x,y;
bool cmpfun(ss a,ss b)
{
	if(a.dis==b.dis)
	{
		return(!((a.x==x && a.y==y)||(a.y==x && a.x==y)));
	}
	return(a.dis<b.dis);
}
int find(int disjoint[],int x)
{
    if(disjoint[x]==x)
        return x;
    else 
        disjoint[x]=find(disjoint,disjoint[x]);
    return disjoint[x];
}
void unio(int disjoint[],int rank[],int x,int y)
{
    int val1=find(disjoint,x);
    int val2=find(disjoint,y);
    if(val1==val2)return;
    if(rank[val1]>rank[val2])
    {
        disjoint[val2]=val1;
        rank[val1]++;
    }
    else
    {
        disjoint[val1]=val2;
        rank[val2]++;
    }
}
int a[2501][2501]={0};
int main(int argc, char const *argv[])
{
	int m,n;
	scanf("%d %d",&n,&m);
	scanf("%d %d",&x,&y);
	vpp v;
	v.pb(pp(x,y));
	getchar();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			char ch=getchar();
			if(ch=='d')
			{
				//printf("%d %d\n",i,j );
				if(i==x && j==y)
				{
					printf("CLEAN\n");
					return 0;
				}
				v.pb(pp(i,j));
			}
			//printf("%c ",ch );
		}
		getchar();
		//printf("\n");
	}
	int len=v.size();
	std::vector< ss >save;
	for(int i=0;i<len-1;i++)
	{
		for(int j=i+1;j<len;j++)
		{
			int dis=fabs(v[i].first-v[j].first)+fabs(v[i].second-v[j].second);
			ss h;
			h.x=i;
			h.y=j;
			h.dis=dis;
			save.pb(h);
			//printf("%d ",dis);
		}
		//printf("\n");
	}
	sort(save.begin(),save.end(),cmpfun);
	int len2=save.size();
	int disjoint[2501]={0},rank[2501]={0};
	for(int i=0;i<=2501;i++)
		disjoint[i]=i;
	for(int i=0;i<len2;i++)
	{
		if(find(disjoint,save[i].x)!=find(disjoint,save[i].y))
		{
			unio(disjoint,rank,save[i].x,save[i].y);
			a[save[i].x][save[i].y]=save[i].dis;
			a[save[i].y][save[i].x]=save[i].dis;
		}
	}
	/*for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
			printf("%d ",a[i][j] );
		printf("\n");
	}*/
	int visited[2501]={0};
	queue<int>q;
	q.push(0);
	visited[0]=1;
	std::vector<int> leaf;
	while(!q.empty())
	{
		int f=q.front();
		q.pop();
		int g=0;
		for(int i=0;i<=(n*m)-1;i++)
		{
			if(a[f][i]!=0 && visited[i]==0)
			{
				q.push(i);
				visited[i]=f+1;
				g++;
			}
		}
		if(g==0)
			leaf.pb(f);
	}
	int len4=leaf.size();
	for(int i=0;i<len4;i++)
	{
		int s=0;
		for(int j=leaf[i];j>=0;j=visited[j]-1)
		{
			s+=a[j][visited[j]-1];
			a[j][visited[j]-1]=s;
			a[visited[j]-1][j]=s;
			if(j==0)
				break;
		}
	}
	/*printf("----------------------------------------------------\n");
	for(int i=0;i<25;i++)
	{
		for(int  j=0;j<25;j++)
			printf("%d ",a[i][j] );
		printf("\n");
	}*/
	x=1e9;
	int index=-1;
	for(int i=1;i<=(n*m)-1;i++)
	{
		if(a[0][i]!=0 && a[0][i]<x)
		{
			index=i;
			x=a[0][i];
		}
	}
	pp xx,yy;
	xx=v[0];
	yy=v[index];
	//printf("%d %d\n",yy.first,yy.second );
	if(xx.first<yy.first)
		printf("DOWN\n");
	else if(xx.first>yy.first)
		printf("UP\n");
	else
	{
		if(yy.second>xx.second)
			printf("RIGHT\n");
		else
			printf("LEFT\n");
	}
}
