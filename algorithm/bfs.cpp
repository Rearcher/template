/*
HDU 1241
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#define MAXN 200
using namespace std;

char map[MAXN][MAXN];
int vis[MAXN][MAXN];
int dir[8][2]={{0,-1},{1,0},{0,1},{-1,0},{1,-1},{1,1},{-1,-1},{-1,1}};
int n,m;

struct node
{
	int x, y;

	node()
	{
		x = 0;
		y = 0;
	}
	node(int a, int b)
	{
		x = a;
		y = b;
	}
};


void bfs(int i, int j)
{	
	queue<node> q;
	vis[i][j] = 1;
	struct node temp(i,j);
	q.push(temp);
	while(!q.empty())
	{
		struct node u = q.front();
		q.pop();
		for(int k = 0; k < 8; k++)
		{
			int x = u.x + dir[k][0];
			int y = u.y + dir[k][1];
			if(x>=0 && x<n && y>=0 && y<m)
				if(map[x][y]=='@' && !vis[x][y])
				{
					struct node tmp(x,y);
					vis[x][y] = 1;
					q.push(tmp);
				}
		}
	}
}

int main()
{
	int ans;
	while(scanf("%d%d",&n,&m), n!=0&&m!=0)
	{
		memset(vis, 0, sizeof(vis));
		memset(map, 0, sizeof(map));
		ans = 0;
		for(int i = 0; i < n; i++)
			scanf("%s", map[i]);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(map[i][j]=='@' && !vis[i][j])
				{
					bfs(i,j);
					ans++;
				}
			}		
		}
		printf("%d\n",ans);
	}
}

/*bfs算法
void BFS(Graph G, Status (*visit)(int v))
{
	for(v = 0; v < G.vexnum; v++)
		visited[v] = false;
	InitQueue(Q);	//置空队列
	for(v = 0; v < G.vexnum; v++)
	{
		if(!visited[v])
		{
			Q.push(v);
			visited[v] = 1;
			Visit(v);
			while(!Q.empty)
			{
				u = Q.front;
				Q.pop();
				for(w = FirstAdjVex(G,u); w >= 0; w = NextAdjVex(G,u,w))
				{	//w为u的邻接点
					if(!visited[w])
					{
						visited[w] = true;
						Visit(w);
						Q.push(w);
					}
				}
			}
		}
	}
}
*/
