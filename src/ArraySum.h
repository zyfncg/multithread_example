//
// Created by Zhang Yunfei on 2020/4/18.
//

#ifndef MULTITHREAD_EXAMPLE_ARRAYSUM_H
#define MULTITHREAD_EXAMPLE_ARRAYSUM_H

#include <vector>
#include <thread>
#include <numeric>

using namespace std;

void partSum(const vector<int>& data, int N, int tid, vector<int>& result){
    int len = data.size() / N;
    int addi = data.size() % N;
    int start, end;
    if(tid < addi){
        start = tid * (len + 1);
        end = start + len;
    }else{
        start = addi * (len + 1) + (tid - addi) * len;
        end = start + len - 1;
    }
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += data[i];
    }
//    cout<<start<<" "<<end<<": "<<sum<<endl;
    result[tid] = sum;
}

int arraySum(const vector<int>& data){
    const int N = 4;
    vector<thread> threadList;
    threadList.reserve(N);
    vector<int> result(N, 0);
    for (int i = 0; i < N; ++i) {
        threadList.emplace_back(partSum, cref(data), N, i, ref(result));
    }
    for (int i = 0; i < N; ++i) {
        threadList[i].join();
    }
    int ans = accumulate(result.begin(), result.end(), 0);
    return ans;
}

/*
int main(){
    int n = 124;
    int ans = 0;
    vector<int> data(n, 0);
    for (int i = 0; i < n; ++i) {
        data[i] = i+1;
        ans += data[i];
    }
    int sum = arraySum(data);
    cout<<"result: "<<sum<<"  right answer: "<<ans<<endl;
    return 0;
}
*/

#endif //MULTITHREAD_EXAMPLE_ARRAYSUM_H
