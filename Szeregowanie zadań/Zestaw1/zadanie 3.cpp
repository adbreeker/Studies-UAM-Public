#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct task
{
	int id;
	int readyToStart;
	int timeToEnd;
};


bool sortingParam(const task& a, const task& b)
{
	if (a.timeToEnd != b.timeToEnd)
	{
		return a.timeToEnd < b.timeToEnd;
	}
	else
	{
		return a.id < b.id;
	}
}

int main() 
{
	int n;
	cin >> n;
	vector<task> tasks(n);
	for (int i = 0; i < n; i++)
	{
		tasks[i].id = i;
		cin >> tasks[i].readyToStart >> tasks[i].timeToEnd;
	}

	int readyTasks = 0;
	int currentTime = 0;

	vector<task> tasksReadyToDo;
	vector<int> finishedTasks(n);
	while (readyTasks != n)
	{
		if (tasks.size() > 0)
		{
			for (task t : tasks)
			{
				if (t.readyToStart <= currentTime)
				{
					tasksReadyToDo.push_back(t);
					tasks.erase(tasks.begin());
				}
			}
		}

		if (tasksReadyToDo.size() > 0)
		{
			sort(tasksReadyToDo.begin(), tasksReadyToDo.end(), sortingParam);
			tasksReadyToDo[0].timeToEnd--;
			if (tasksReadyToDo[0].timeToEnd == 0)
			{
				finishedTasks[tasksReadyToDo[0].id] = currentTime + 1;
				tasksReadyToDo.erase(tasksReadyToDo.begin());
				readyTasks++;
			}
		}
		
		currentTime++;
	}

	for (int t : finishedTasks)
	{
		cout << t << endl;
	}
}