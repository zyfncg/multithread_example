//
// Created by Zhang Yunfei on 2020/4/26.
//

#ifndef MULTITHREAD_EXAMPLE_READWRITELOCK_H
#define MULTITHREAD_EXAMPLE_READWRITELOCK_H

#include <mutex>
#include <condition_variable>
#include <thread>

/**
 * A Fair ReadWriteLock
 */
class ReadWriteLock{
private:
    std::mutex mtx;
    std::condition_variable cond;
    int readerNum;
    bool hasWriter;
public:
    ReadWriteLock() : readerNum(0), hasWriter(false){}

    void readLock();

    void readUnlock();

    void writeLock();

    void writeUnlock();
};

void ReadWriteLock::readLock() {
    std::unique_lock<std::mutex> locker(mtx);
    while(hasWriter){
        cond.wait(locker);
    }
    readerNum++;
}

void ReadWriteLock::readUnlock() {
    std::unique_lock<std::mutex> locker(mtx);
    readerNum--;
    if(readerNum == 0 && hasWriter) {
        cond.notify_all();
    }
}

void ReadWriteLock::writeLock() {
    std::unique_lock<std::mutex> locker(mtx);
    while(hasWriter){
        cond.wait(locker);
    }
    hasWriter = true;
    while(readerNum > 0){
        cond.wait(locker);
    }
}

void ReadWriteLock::writeUnlock() {
    std::unique_lock<std::mutex> locker(mtx);
    hasWriter = false;
    cond.notify_all();
}

// ############## Test case ###############
/*
ReadWriteLock rwLock;
int data = 0;
int getData(){
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    rwLock.readLock();
    int ret = data;
    std::cout<<ret<<std::endl;
    rwLock.readUnlock();
    return ret;
}
void increaseData(int x){
//    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    rwLock.writeLock();
    data += x;
    std::cout<<"write "<<data<<std::endl;
    rwLock.writeUnlock();
}

int main(){
     int readerNum = 50;
     int writerNum = 10;
     vector<std::thread> threadList;
     threadList.reserve(readerNum + writerNum);
     for(int i=0; i<readerNum; ++i){
         threadList.emplace_back(getData);
     }
     for(int i=0; i<writerNum; ++i){
         threadList.emplace_back(increaseData, 1);
     }
     for(auto& t : threadList){
         t.join();
     }
     return 0;
}
*/

#endif //MULTITHREAD_EXAMPLE_READWRITELOCK_H
