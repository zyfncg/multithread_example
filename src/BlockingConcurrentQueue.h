//
// Created by Zhang Yunfei on 2020/4/14.
//

#ifndef MULTITHREAD_EXAMPLE_BLOCKINGCONCURRENTQUEUE_H
#define MULTITHREAD_EXAMPLE_BLOCKINGCONCURRENTQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

/**
 * Blocked ConcurrentQueue
 */
template <typename T>
class BlockingConcurrentQueue{
private:
    std::queue<T> que;
    int capacity;

    std::mutex mtxIn, mtxOut;
    std::condition_variable condIn, condOut;
public:
    explicit BlockingConcurrentQueue(int capacity) : capacity(capacity){}

    T poll(){
        std::unique_lock<std::mutex> outLock(mtxOut);
        while(que.empty()){
            condIn.notify_all();
            condOut.wait(outLock);
        }
        auto ret = que.front();
        que.pop();
        condIn.notify_one();
        return ret;
    }

    void push(T t){
        std::unique_lock<std::mutex> inLock(mtxIn);
        while(que.size() == capacity){
            condOut.notify_all();
            condIn.wait(inLock);
        }
        que.push(t);
        condOut.notify_one();
    }
};

/*
int main(){
    BlockingConcurrentQueue<int> que(10);
    auto producter = [&que](){
        for (int i = 0; i < 10; ++i) {
            que.push(i);
        }};

    auto consumer = [&que](){
        for (int i = 0; i < 5; ++i) {
            std::cout<<que.poll()<<std::endl;
        }};

    int n = 8;
    std::vector<std::thread> threads;
    threads.reserve(n);
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(producter);
    }
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(consumer);
    }
    for(auto& t : threads){
        t.join();
    }
    return 0;
}
*/

#endif //MULTITHREAD_EXAMPLE_BLOCKINGCONCURRENTQUEUE_H
