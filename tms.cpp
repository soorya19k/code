#include<bits/stdc++.h>
using namespace std;
#define maxn 100005

int solve(int n,int k,vector<vector<int> > segments){
    vector<int>v[maxn];
    //this array of vector will store '1+index' of the segments
    //li represents starting point of segment
    //ri represents represents ending point of segment
    //append 'i+1' to the vector v[li] that says us that in the point li the i-th segment is opened/started
    //append '-(i+1)' to the vector v[ri+1] that says us that in the point 'ri+1' the i-th segment is closed/ended that means ith segment has ended at 'ri'
    //we have appended ending point at '1+ri' so that we get to know that ith segment is of no use now , any point covered by ith segment is checked and processed to contain at most k segments
    //we have appended positive or negative value of '1+index' so that we get to know difference b/w starting and ending of the segment
    //we have appended 1+indexed values i because +0 and −0 are the same thing actually.



    //appending segment's starting and ending point
    for(int i=0;i<n;i++){
        int x=segments[i][0],y=segments[i][1];
        v[x].push_back((i+1));
        v[y+1].push_back(-(i+1));
    }


    // this variable will maintain count of number of segments removed
    int cnt=0;


    //this set will conatins segments that covers current point
    set<pair<int,int> > cur;
    for(int i=1;i<maxn;i++){
        for(int itr:v[i]){

            //if 'itr' is positive then it means segment is starting at current point
            //we will append '-ri' of the segment
            //so that set will contain segment whose ending point is maximum at top because set keeps element in sorted order
            //whenever we have to remove segment our greedy approach says remove longest segment
            if(itr>0){
                cur.insert({-segments[itr-1][1],itr});
            }
            //if itr is negative that means segment is closed at current point
            // so we will remove that segment from the set
            else{
                cur.erase({-segments[abs(itr)-1][1],-itr});
            }
        }
        //if set contains more that k segments we will remove segments at top one by one untill current point k segments
        while(cur.size()>k){
            cnt++;
            auto itr = cur.begin();
            cur.erase(itr);
        }
    }

    //return number of segments removed
    return cnt;
}

