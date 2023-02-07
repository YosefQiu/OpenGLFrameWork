#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>

#ifdef __GNUC__

errno_t ctime_s(char* buf, rsize_t bufsz, const time_t* timer)
{
    errno_t ret = 0;
    buf = ctime(timer);
    if (sizeof(buf) < bufsz)
    {
        ret = errno;
    }
    return ret;
}
#endif

class Task
{
public:
    virtual void doIt()
    {
        std::cout << "handle a task..." << std::endl;
    }
    Task() {}
    virtual ~Task()
    {
        // in order to see the destruction of a task, the ~Task() can be added here
        std::cout << "[FINISHED]:: a task destructed..." << std::endl;
    }
};


class GetTime : public Task
{
public:
    int num;
    GetTime() {}
    GetTime(int i) { num = i; }
    virtual void doIt()
    {
        auto timenow =
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        char str[26];
        ctime_s(str, sizeof(str), &timenow);
        str[strlen(str) - 1] = 0;
        std::cout <<  num << " current time [ " << str << " ]" << std::endl;
    }
};

class TaskPool final
{
public:
    TaskPool();
    ~TaskPool();
    TaskPool(const TaskPool& rhs) = delete;
    TaskPool& operator=(const TaskPool& rhs) = delete;

public:
    void init(int threadNum = 5);
    void stop();

    void addTask(Task* task);
    void removeAllTasks();

private:
    void threadFunc();

private:
    std::list<std::shared_ptr<Task>>            m_taskList;
    std::mutex                                  m_mutexList;
    std::condition_variable                     m_cv;
    bool                                        m_bRunning;
    std::vector<std::shared_ptr<std::thread>>   m_threads;
};
