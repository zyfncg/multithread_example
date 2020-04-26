#include <iostream>
#include <thread>
#include "BlockingConcurrentQueue.h"
#include "ArraySum.h"
#include "ReadWriteLock.h"

using namespace std;

//int main(){
//    BlockingConcurrentQueue<int> que(10);
//    auto producter = [&que](){
//        for (int i = 0; i < 10; ++i) {
//            que.push(i);
//        }};
//
//    auto consumer = [&que](){
//        for (int i = 0; i < 5; ++i) {
//            std::cout<<que.poll()<<std::endl;
//        }};
//
//    int n = 8;
//    std::vector<std::thread> threads;
//    threads.reserve(n);
//    for (int i = 0; i < 2; ++i) {
//        threads.emplace_back(producter);
//    }
//    for (int i = 0; i < 4; ++i) {
//        threads.emplace_back(consumer);
//    }
//    for(auto& t : threads){
//        t.join();
//    }
//    return 0;
//}