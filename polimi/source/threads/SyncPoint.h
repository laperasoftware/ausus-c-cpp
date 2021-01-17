//
// Created by famiglia on 17/01/21.
//

#ifndef SOURCE_SYNCPOINT_H
#define SOURCE_SYNCPOINT_H

//
// Created by famiglia on 17/01/21.
//

/*Implement a C++ template class named SyncPoint with two member functions:
 *
void addData(T data)
std::list<T> getData().

The first member functions must be
callable by one or more threads and should put the data item in an ordered queue.

 The second member function must also be callable by multiple threads and shall return the
first three data items that have been put in the queue. If the queue contains less than
three data items, the function shall wait. */

#include <list>
#include <thread>

#include <mutex>
#include <condition_variable>

//Put here include needed
template<typename T>
class SyncPoint {
public:

    void addData(T data) {

        { //lock scope
            std::unique_lock<std::mutex> uLock(mutex1); //takes the lock
            queue.push_back(data);
            std::cout << "added point: " << (float)data << ". " << std::endl;
            //notify only if there if it's possible to pick items
            if (queue.size() >= MIN_FILL) cv.notify_one();

        }

    }

    std::list<T> getData() {

        //while pattern to prevent spurious wakeups, lock to access CV and queue
        std::unique_lock<std::mutex> uReadLock(mutex1);
        while (queue.size() < MIN_FILL) {
            cv.wait(uReadLock);
        }
        std::list<T> firstThreeValues;
        std::cout << "RETRIEVING... " << std::endl;
        for (int i = 0; i < MIN_FILL; i++) {
            firstThreeValues.push_back(queue.front());
            std::cout << "retrieved " << firstThreeValues.back() << std::endl;
            queue.pop_front();
        }

        return firstThreeValues;

    }

private:
    std::list<T> queue;
    std::mutex mutex1;
    std::condition_variable cv;
    const int MIN_FILL = 3;

};

#endif //SOURCE_SYNCPOINT_H
