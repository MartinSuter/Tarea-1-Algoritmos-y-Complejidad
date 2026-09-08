#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct PileNode {

    int valor;
    size_t pileIndex;

    bool operator>(const PileNode& other) const{
        return valor > other.valor;
    }  
};

vector<int> patienceSort(vector<int>& arr) {

    if(arr.size() <= 1) return arr;
    vector<vector<int>> piles;
    vector<int> pileTops;

    for(int x : arr){ 

        auto it = lower_bound(pileTops.begin(), pileTops.end(), x);
        if(it == pileTops.end()){

            piles.push_back({x});
            pileTops.push_back(x);

        } else {

            size_t idx = distance(pileTops.begin(), it);
            piles[idx].push_back(x);
            pileTops[idx] = x;
        }
    }

    priority_queue<PileNode, vector<PileNode>, greater<PileNode>> minHeap;

    for(size_t i = 0; i < piles.size(); i++){

        minHeap.push({piles[i].back(), i});

    }

    vector<int> result;
    result.reserve(arr.size());

    while(!minHeap.empty()){

        PileNode top = minHeap.top();
        minHeap.pop();
        result.push_back(top.valor);
        piles[top.pileIndex].pop_back();

        if(!piles[top.pileIndex].empty()){

            minHeap.push({piles[top.pileIndex].back(), top.pileIndex});

        }
    }

    arr = result;
    return arr;
}