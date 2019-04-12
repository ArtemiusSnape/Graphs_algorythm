#include <fstream>
#include <vector>
#include<queue>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct dvizh {
	int x, y;

};


int main()
{
	

	int n, m;
	fin >> n >> m;

	vector<vector<int>>G(n);
	for (int i = 0; i < n; i++)
		G[i].resize(m);
	int i;
	int k = 0, e = 0;
	while (fin >> i)
	{
		G[k][e] = i;
		e++;
		if (e == m)
		{
			k++;
			e = 0;
		}
	}

	dvizh hod[4] = {
		{0,-1},{-1,0},{0,1},{1,0}
	};


	vector<vector<char>>used(n);
	for (int j = 0; j < n; j++)
		used[j].resize(m);

	int answer = 0;

	for (int j = 0; j < n; j++)
	{
		for (int r = 0; r < m; r++)
		{
			if (G[j][r] != -1)
			{
				if (!used[j][r])
				{
					answer++;
					queue<dvizh>q;
					dvizh start;
					start.x = j;
					start.y = r;
					q.push(start);
					while (!q.empty())
					{
						dvizh U = q.front();
						q.pop();
						for (int i = 0; i < 4; i++)
						{
							dvizh pt;
							pt.x = U.x + hod[i].x;
							if (pt.x > n - 1 || pt.x < 0)
								continue;
							pt.y = U.y + hod[i].y;
							if (pt.y > m - 1 || pt.y < 0)
								continue;

							if (G[pt.x][pt.y] == -1)
							{
								used[pt.x][pt.y] = true;
								continue;
							}

							if (!used[pt.x][pt.y])
							{
								used[pt.x][pt.y] = true;
								q.push(pt);

							}
						}
					}
				}
			}
		}

	}

	fout << answer;

	return 0;
}