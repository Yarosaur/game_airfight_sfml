#ifndef __AIRPLANE_PARALLEL_TASK_HPP__
#define __AIRPLANE_PARALLEL_TASK_HPP__

#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>


class ParallelTask
{
public:
    ParallelTask();
    void Execute();
    bool IsFinished();
    float GetCompletion();

private:
    void RunTask();

private:
    sf::Thread thread_;
    bool finished_;
    sf::Clock elapsed_time_;
    sf::Mutex mutex_;
};

#endif // __AIRPLANE_PARALLEL_TASK_HPP__
