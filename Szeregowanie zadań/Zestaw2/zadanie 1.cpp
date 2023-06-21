#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct request
{
	int time;
	int pages;
	int id;
};

bool sortingParam(const request& a, const request& b)
{
	return a.time < b.time;
}

int main() 
{
	int n;
	cin >> n;
	vector<request> requests;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		request r;
		r.time = a;
		r.pages = b;
		r.id = i;
		requests.push_back(r);
	}

	sort(requests.begin(), requests.end(), sortingParam);

	int currentTime = 0;
	vector<int> results(n);
	for (request r : requests)
	{
		if (r.time > currentTime)
		{
			currentTime = r.time;
		}
		currentTime += r.pages;
		results[r.id] = currentTime;
	}

	for (int result : results)
	{
		cout << result << endl;
	}
	cout << currentTime;

}