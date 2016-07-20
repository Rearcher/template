#include <iostream>
#include <algorithm>
using namespace std;

const int maxn=1010;
int fa[maxn];
//int G[maxn][maxn];

struct node
{
	int u, v, w;
	node(){};
	node(int uu, int vv, int ww)
	{
		u = uu; v = vv; w = ww;
	}
	bool operator < (const node &p)const
	{
		return w < p.w;
	}
}edge[100010];

int find(int x)
{
	return x==fa[x]?x:(fa[x]=find(fa[x]));
}

int main()
{
	int n, a, b, c;
	int ans=0;
	cin >> n;

	for(int i = 1; i <= n; i++)
		fa[i] = i;
	for(int i = 0; i < n; i++)
	{
		cin>>a>>b>>c;
		edge[i] = node(a,b,c);
	}
	sort(edge, edge+n);

	for(int i = 0; i < n; i++)
	{
		int u, v, w, fu, fv;
		u = edge[i].u;
		v = edge[i].v;
		w = edge[i].w;
		fu = find(u); fv = find(v);
		if(fu != fv)
		{
			ans += w;
			fa[fu] = fv;
		}
	}

	cout << ans << endl;
}

