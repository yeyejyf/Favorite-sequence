//
//  main.cpp
//  Favorite sequence
//
//  Created by Yunfan Jin on 3/15/15.
//  Copyright (c) 2015 yunfan.jin. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <utility>
using namespace std;

class MyGraph{
    unordered_map<long, pair<int, set<long>>> DirectedGraph;
    
public:
    void newNode(long value){
        auto search = DirectedGraph.find(value);
        if (search == DirectedGraph.end()) {
            DirectedGraph[value] = make_pair(0, set<long>());
        }
    }
    void connect(long parent, long child){
        if (DirectedGraph[parent].second.find(child) == DirectedGraph[parent].second.end()){
            DirectedGraph[parent].second.insert(child);
            DirectedGraph[child].first++;
        }
    }
    void handleList(const vector<long> &list, int N){
        newNode(list[0]);
        for (int i = 1; i<N; i++) {
            newNode(list[i]);
            connect(list[i - 1], list[i]);
        }
    }
    set<long> noParentNode(){
        set<long> output;
        for (auto const &item : DirectedGraph){
            if (item.second.first == 0) {
                output.insert(item.first);
            }
        }
        return output;
    }
    vector<long> run(){
        vector<long> output;
        set<long> sorted = noParentNode();
        while (!sorted.empty()) {
            auto iter = sorted.begin();
            long value = *iter;
            sorted.erase(iter);
            output.push_back(value);
            //cout << "value: " << value << endl << "next: ";
            for (long next : DirectedGraph[value].second){
                DirectedGraph[next].first--;
                if (DirectedGraph[next].first == 0) {
                    sorted.insert(next);
                }
                //cout << next << " ";
            }
            //cout << endl;
        }
        return output;
    }
};

int main(int argc, const char * argv[]) {
    int N, K;
    cin >> N;
    MyGraph graph;
    for (int i = 0; i<N; i++) {
        cin >> K;
        long tmp;
        vector<long> list;
        for (int j = 0; j<K; j++) {
            cin >> tmp;
            list.push_back(tmp);
        }
        graph.handleList(list, K);
    }
    vector<long> result = graph.run();
    cout << result[0];
    for (int i = 1; i<result.size(); i++) {
        cout << " " << result[i];
    }
    cout << endl;
    
    
    return 0;
}

