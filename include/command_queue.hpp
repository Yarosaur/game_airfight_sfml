#ifndef __AIRPLANE_COMMAND_QUEUE_HPP__
#define __AIRPLANE_COMMAND_QUEUE_HPP__

#include "../include/command.hpp"

#include <queue>


class CommandQueue
{
public:
    void Push(const Command& command);
    Command Pop();
    bool IsEmpty() const;

		
private:
    std::queue<Command>	queue_;
};

#endif // __AIRPLANE_COMMAND_QUEUE_HPP__
