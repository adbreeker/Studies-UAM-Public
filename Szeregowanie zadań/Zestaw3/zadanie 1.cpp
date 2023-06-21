#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct task
{
	int id;
	int gotowosc;
	int czasTrwania;
	vector<int> poprzedniki;

	int r;
};

bool sortingParam(const task& a, const task& b)
{
	return a.r < b.r;
}

int main()
{
	int n;
	cin >> n;
	vector<task> tasks;
	for (int i = 1; i <= n; i++)
	{
		task t;
		t.id = i;
		cin >> t.gotowosc >> t.czasTrwania;
		tasks.push_back(t);
	}

	int e;
	cin >> e;

	for (int i = 0; i < e; i++)
	{
		int poprzednik, nastepnik;
		cin >> poprzednik >> nastepnik;
		tasks[nastepnik - 1].poprzedniki.push_back(poprzednik);
	}

	vector<int> topologicznie;

	while ((int)topologicznie.size() != n)
	{
		for (task t : tasks)
		{
			if (t.poprzedniki.size() == 0)
			{
				if (find(topologicznie.begin(), topologicznie.end(), t.id) == topologicznie.end())
				{
					topologicznie.push_back(t.id);
				}
			}
			else
			{
				bool poprzednikiZrobione = true;
				for (int poprzednik : t.poprzedniki)
				{
					if (find(topologicznie.begin(), topologicznie.end(), poprzednik) == topologicznie.end())
					{
						poprzednikiZrobione = false;
						break;
					}
				}
				if (poprzednikiZrobione)
				{
					if (find(topologicznie.begin(), topologicznie.end(), t.id) == topologicznie.end())
					{
						topologicznie.push_back(t.id);
					}
				}
			}
		}
	}

	for (int idTopo : topologicznie)
	{
		task t = tasks[idTopo - 1];
		vector<int> ri;
		ri.push_back(t.gotowosc);
		for (int idPoprzednika : t.poprzedniki)
		{
			task poprzednik = tasks[idPoprzednika - 1];
			ri.push_back(poprzednik.r + poprzednik.czasTrwania);
		}

		tasks[idTopo - 1].r = *max_element(ri.begin(), ri.end());
	}

	sort(tasks.begin(), tasks.end(), sortingParam);

	int currentTime = 0;
	for (task t : tasks)
	{
		currentTime = max(currentTime, t.gotowosc);
		currentTime += t.czasTrwania;
	}

	cout << currentTime << endl;
}