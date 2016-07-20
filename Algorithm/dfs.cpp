/*
 HDU 2586
*/
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

struct node
{
	int dir;
	int length;
};

vector<struct node> map[40010];
int vis[40010];
int begin, end;
int n, m, flag;

void dfs(int s, int res)
{
	if(flag || vis[s])
		return;
	if(s == end)
	{
		printf("%d\n", res);
		flag = 1;
		return;
	}
	if(map[s].empty())
		return;
	else
	{
		vis[s] = 1;
		for(unsigned int i = 0; i < map[s].size(); i++)
			dfs(map[s][i].dir, res+map[s][i].length);
		vis[s] = 0;
	}
}

int main()
{
	int cas;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d %d",&n,&m);
		for(int i = 0; i < n-1; i++)
		{
			struct node temp;
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			temp.dir = b;
			temp.length = c;
			map[a].push_back(temp);
			temp.dir = a;
			temp.length = c;
			map[b].push_back(temp);
		}
		for(int i = 0; i < m; i++)
		{
			memset(vis, 0, sizeof(vis));
			scanf("%d %d", &begin,&end);
			flag = 0;
			dfs(begin, 0);
		}
		for(int i = 0; i < n; i++)
			map[i].clear();
	}
}
