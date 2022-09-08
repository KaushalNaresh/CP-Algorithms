/*

There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes,
where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number
of students will pass the exam. You are also given an integer extraStudents. There are another extraStudents brilliant students that
are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in 
a way that maximizes the average pass ratio across all the classes. The pass ratio of a class is equal to the number of students of the
class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of
all the classes divided by the number of the classes. Return the maximum possible average pass ratio after assigning the extraStudents 
students. Answers within 10-5 of the actual answer will be accepted.

Constraints:

1 <= classes.length <= 105
classes[i].length == 2
1 <= passi <= totali <= 105
1 <= extraStudents <= 105

*/

#include<bits/stdc++.h>
using namespace std;

double getProfit(int pass, int total){

    double newAvg = (pass+1)/((double)(total+1));
    double oldAvg = pass/((double)(total));

    return newAvg-oldAvg;
}

int main(){

    int extraStud, n, pass, total;
    double ans = 0, avg, profit, newProfit;
    cin>>n;
    vector<pair<int, int>> pass_total;
    for(int i = 0; i < n; i++){
        cin>>pass>>total;
        pass_total.push_back({pass, total});
    }
    cin>>extraStud;

    priority_queue<pair<double, pair<int, int>>> pq;

    for(int i = 0; i < n; i++){
        pass = pass_total[i].first;
        total = pass_total[i].second;
        avg = pass/((double)total);
        pq.push({getProfit(pass, total), {pass, total}});
        ans += avg;
    }

    while(extraStud){
        profit = pq.top().first;
        pass = pq.top().second.first;
        total = pq.top().second.second;
        pq.pop();
        ans += profit;
        newProfit = getProfit(pass+1, total+1);
        pq.push({newProfit, {pass+1, total+1}});

        extraStud--;
    }

    cout<<ans/n;
}