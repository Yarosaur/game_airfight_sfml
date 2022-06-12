#include "../include/command_queue.hpp"
#include "../include/scene_node.hpp"


void CommandQueue::Push(const Command& command)
{
    queue_.push(command);
}


Command CommandQueue::Pop()
{
    Command command {queue_.front()};
    queue_.pop();
    return command;
}


bool CommandQueue::IsEmpty() const
{
    return queue_.empty();
}
