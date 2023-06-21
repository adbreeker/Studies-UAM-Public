#include <iostream>
#include <vector>
#include <algorithm>

struct Order 
{
    int timeToComplete;
    int deadline;
};

bool sortingParamDeadline(Order a, Order b) 
{
    return a.deadline < b.deadline;
}

bool sortingParamTime(Order a, Order b)
{
    return a.timeToComplete < b.timeToComplete;
}

using namespace std;

int main() 
{
    int n;
    std::cin >> n;

    std::vector<Order> orders(n);
    for (int i = 0; i < n; i++) 
    {
        std::cin >> orders[i].timeToComplete >> orders[i].deadline;
    }

    sort(orders.begin(), orders.end(), sortingParamDeadline);

    vector<Order> toDo;
    int currentDoingTime = 0;

    for (Order o : orders)
    {
        toDo.push_back(o);
        currentDoingTime += o.timeToComplete;
        if (currentDoingTime > o.deadline)
        {
            sort(toDo.begin(), toDo.end(), sortingParamTime);
            currentDoingTime -= toDo.back().timeToComplete;
            toDo.pop_back();
        }
    }

    cout << toDo.size();
}
