#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

const int INFINIT = 10000000;
const int INF2 = 1000000000;

int main()
{

	ifstream fin("input.txt");
	ofstream fout("output.txt");


	int n;
	fin >> n;

	vector<vector<int>>a(n + 1);
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < n + 1; j++)
		{
			a[i].push_back(-1);
		}

	int ki;
	int count = 1;
	while (fin >> ki)
	{
		if (ki == 0)
		{
			fout << -1;
			return 0;
		}
		for (int j = 0; j < ki; j++)
		{
			int day, risk;
			fin >> day;
			fin >> risk;
			a[count][day] = risk;
		}
		count++;
	}

	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++)
		{
			if (a[i][j] == -1)
				a[i][j] = INFINIT;
		}


	vector<int> u(n + 1);//для строк
	vector<int>v(n + 1);//для столбцов
	vector<int>p(n + 1);//для паросочетаний,номера строк
	vector<int>way(n + 1);//минимумы для потенциала

	for (int i = 1; i < n + 1; ++i)
	{
		p[0] = i;//то что смотрим в 0
		int j0 = 0;//посетил 0 столб
		vector<int> minv;
		minv.assign(n + 1, INF2);

		vector<char> used;
		used.assign(n + 1, false);

		do {
			used[j0] = true;
			int i0 = p[j0];
			int delta = INF2;
			int j1;

			for (int j = 1; j < n + 1; ++j)
				if (!used[j])
				{
					int razh = a[i0][j] - u[i0] - v[j];

					if (razh < minv[j])
						minv[j] = razh, way[j] = j0;

					if (minv[j] < delta)
						delta = minv[j], j1 = j;
				}

			for (int j = 0; j <= n; ++j)
				if (used[j])
					u[p[j]] += delta, v[j] -= delta;
				else
					minv[j] -= delta;

			j0 = j1;

		} while (p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}

	if (-v[0] > INFINIT)
		fout << -1;
	else
		fout << -v[0];


	return 0;
}