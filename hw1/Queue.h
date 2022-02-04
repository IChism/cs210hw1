#pragma once
template <typename Object>
class Queue
{
public:
    bool isEmpty() const
    {
        return true;
    }
    const Object& getFront() const
    {
        return 0;
    }
    void enqueue(const Object& x)
    {
    }
    Object& dequeue()
    {
        return *theList.begin();
    }
private:
    List<Object> theList;
};
