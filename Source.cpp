#include <iostream>
#include <fstream>
#include<map>
#include<set>
#include <vector>
#include <queue>
#include<iomanip>
using namespace std;

int main()
{

	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n, m;

	fin >> n >> m;
	if (m == 0 || n == 1)
	{
		fout << 0;
		return 0;
	}
	int x1,x2,ves;
	vector<map<int, int>>G(n);
	while (fin >> x1)
	{
		fin >> x2 >> ves;
		if (x1 == x2)
			continue;

		auto it = G[x1 - 1].find(x2 - 1);
		if (it == G[x1 - 1].end())
		{
			G[x1 - 1].insert(make_pair(x2 - 1, ves));
			G[x2 - 1].insert(make_pair(x1 - 1, ves));
		}
		else
		{
			if ((*it).second > ves)
			{
				(*it).second = ves;
				auto it1 = G[x2 - 1].find(x1 - 1);
				(*it1).second = ves;
			}
		}
	
	}
	unsigned int INF = 4000000000;
	vector<unsigned int> d(n, INF);
	d[0] = 0;
	
	set < pair<unsigned int, unsigned int> > q;
	q.insert(make_pair(d[0], 0));
	while (!q.empty()) 
	{
		unsigned int v = q.begin()->second;
		q.erase(q.begin());

		for (auto j = G[v].begin(); j != G[v].end(); ++j) {
			int to = (*j).first;
			unsigned int	len = (*j).second;
			if (d[v] + len < d[to]) {
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + len;
				q.insert(make_pair(d[to], to));
			}
		}
	}
	fout << setprecision(25) << d[n - 1];
	return 0;
}