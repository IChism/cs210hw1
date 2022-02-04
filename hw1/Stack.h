#pragma once
template <typename Object>
class Stack
{
public:
    bool isEmpty() const
    {
        return true;
    }
    const Object& top() const
    {
        return 0;
    }
    void push(const Object& x)
    {
    }
    Object& pop()
    {
        return *theList.begin();
    }
private:
    List<Object> theList;
};