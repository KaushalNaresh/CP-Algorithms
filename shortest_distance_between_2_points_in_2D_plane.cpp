#include<bits/stdc++.h>
using namespace std;

class point{

    public:
    int x, y;
    point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

bool compareX(point p1, point p2){
        return p1.x != p2.x ? p1.x < p2.x : p1.y < p2.y;
}

bool compareY(point p1, point p2){
        return p1.y <= p2.y;
}

float distance(point p1, point p2){

    float dist = sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
    return dist;
}

vector<point> merge(vector<point> left, vector<point> right){

    int lptr1 = 0, lptr2 = 0, rptr1 = left.size()-1, rptr2 = right.size()-1;
    vector<point> sortedY;

    while(lptr1 <= rptr1 && lptr2 <= rptr2){
        if(left[lptr1].y <= right[rptr1].y){
            sortedY.push_back(left[lptr1]);
            lptr1++;
        }
        else{
            sortedY.push_back(right[lptr2]);
            lptr2++;
        }
    }

    while(lptr1 <= rptr1){
        sortedY.push_back(left[lptr1]);
        lptr1++;
    }

    while(lptr2 <= rptr2){
        sortedY.push_back(right[lptr2]);
        lptr2++;
    }

    return sortedY;
}

// Sorting Y on the go using merge function

pair<float, vector<point>> shortestDist(vector<point> pointsX, int lb, int ub){

    if(lb == ub)
        return {FLT_MAX, {pointsX[lb]}};

    if(ub-lb+1 == 2){
        if(pointsX[lb].y <= pointsX[ub].y)
            return {distance(pointsX[lb], pointsX[ub]), {pointsX[lb], pointsX[ub]}};
        else
            return {distance(pointsX[lb], pointsX[ub]), {pointsX[ub], pointsX[lb]}};
    }

    int mid = (lb + ub)/2;
    int midx = pointsX[mid].x;
    int midy = pointsX[mid].y;

    pair<float, vector<point>> left = shortestDist(pointsX, lb, mid);
    pair<float, vector<point>> right = shortestDist(pointsX, mid+1, ub);

    float d = min(left.first, right.first);

    vector<point> sortedY = merge(left.second, right.second);

    vector<point> strip;

    for(int i = 0; i < sortedY.size(); i++){
        if(abs(sortedY[i].x-midx) < d)
            strip.push_back(sortedY[i]);
    }

    for(int i = 0; i < strip.size(); i++){
        for(int j = 1; j <= 7; j++){
            if(i+j >= strip.size())
                break;
            float dist = distance(strip[i], strip[i+j]);
            if(dist < d)
                d = dist;
        }
    }

    return {d, sortedY};

}

// Passing already sorted Y but be careful while splitting Y based on divider

float shortestDist2(vector<point> pointsX, vector<point> pointsY, int lb, int ub){

    if(lb == ub)
        return FLT_MAX;

    if(ub-lb+1 == 2)
        return distance(pointsX[lb], pointsX[ub]);

    int mid = (lb + ub)/2;
    int midx = pointsX[mid].x;
    int midy = pointsX[mid].y;

    vector<point> left, right;

    for(int i = 0; i < pointsY.size(); i++){
        if(pointsY[i].x == midx){
            if(pointsY[i].y <= midy)
                left.push_back(pointsY[i]);
            else
                right.push_back(pointsY[i]);
        }
        else if(pointsY[i].x < midx)
            left.push_back(pointsY[i]);
        else
            right.push_back(pointsY[i]);
    }

    float d1 = shortestDist2(pointsX, left, lb, mid);
    float d2 = shortestDist2(pointsX, right, mid+1, ub);

    float d = min(d1, d2);

    vector<point> strip;

    for(int i = 0; i < pointsY.size(); i++){
        if(abs(pointsY[i].x-midx) < d)
            strip.push_back(pointsY[i]);
    }

    for(int i = 0; i < strip.size(); i++){
        for(int j = 1; j <= 7; j++){
            if(i+j >= strip.size())
                break;
            float dist = distance(strip[i], strip[i+j]);
            if(dist < d)
                d = dist;
        }
    }

    return d;

}

int main(){

    int n, x, y;
    vector<point> pointsX, pointsY;

    cin>>n;

    for(int i = 0; i < n; i++){
        cin>>x>>y;
        point* pt = new point(x, y);
        pointsX.push_back(*pt);
        pointsY.push_back(*pt);
    }

    sort(pointsX.begin(), pointsX.end(), compareX);
    sort(pointsY.begin(), pointsY.end(), compareY);

    int lb = 0, ub = pointsX.size()-1;

    float dist = shortestDist2(pointsX, pointsY, lb, ub);
    cout<< "Shortest Distance is: "<<(dist != FLT_MAX ? dist : 0);
    cout<<endl;
    pair<float, vector<point>> ans = shortestDist(pointsX, lb, ub);
    cout<< "Shortest Distance is: "<<(ans.first != FLT_MAX ? ans.first : 0);
}