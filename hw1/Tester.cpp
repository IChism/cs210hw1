#include "List.h"
#include "Stack.h"
#include "Queue.h"

#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

void recordStatus(bool status, int *successes) {
    if (status) {
        cout << "success" << endl;
        (*successes)++;
    }
    else {
        cout << "fail" << endl;
    }
}

int main()
{
    const int N = 100000;
    std::vector<int> testVals(N);
    List<int> classToTest;


    int successes = 0;
    clock_t start = clock();
    for (int i = N - 1; i > 0; --i)
    {
        classToTest.push_front(i);
    }
    clock_t end = clock();
    clock_t time = (end - start);
    cout << "Push front time: " << time << endl;

    recordStatus(time < clock_t(25) && time > clock_t(5), &successes);

    int front = classToTest.front();
    cout << "front: " << front << endl;
    recordStatus(front == 1, &successes);

    int back = classToTest.back();
    cout << "back: " << back << endl;
    recordStatus(back == N - 1, &successes);

    int sizeFull = classToTest.size();
    classToTest.pop_front();
    int sizeMinusOne = classToTest.size();
    cout << "size: " << sizeMinusOne << endl;
    recordStatus(sizeFull == N - 1 && sizeMinusOne == N - 2, &successes);

    classToTest.clear();
    bool isEmpty = classToTest.empty();
    cout << "empty: " << isEmpty << endl;
    recordStatus(isEmpty, &successes);

    start = clock();
    for (int i = N - 1; i > 0; --i)
    {
        classToTest.push_back(i);
    }
    end = clock();
    time = (end - start);
    cout << "Push back time: " << time << endl;

    recordStatus(time < clock_t(25) && time > clock_t(5), &successes);

    front = classToTest.front();
    cout << "front: " << front << endl;
    recordStatus(front == N - 1, &successes);

    back = classToTest.back();
    cout << "back: " << back << endl;
    recordStatus(back == 1, &successes);

    classToTest.pop_front();
    front = classToTest.front();
    cout << "front after pop: " << front << endl;
    recordStatus(front == N - 2, &successes);

    classToTest.pop_back();
    back = classToTest.back();
    cout << "back after pop: " << back << endl;
    recordStatus(back == 2, &successes);

    int index = classToTest.find(18);
    cout << "Index of element: " << index << endl;
    recordStatus(index == 99980, &successes);

    //Test Stack
    cout << "******TESTING STACK******" << endl;
    Stack<int> stack;
    start = clock();
    for (int i = N - 1; i > 0; --i)
    {
        stack.push(i);
    }
    end = clock();
    time = (end - start);
    cout << "Push time: " << time << endl;
    recordStatus(time < clock_t(25) && time > clock_t(5), &successes);

    int top = stack.top();
    cout << "top: " << top << endl;
    recordStatus(top == 1, &successes);

    start = clock();
    bool validOrder = true;
    for (int i = 1; i < N; i++)
    {
        if (stack.isEmpty()) {
            validOrder = false;
            break;
        }
        int x = stack.pop();
        if (x != i)
            validOrder = false;
    }
    end = clock();
    time = (end - start);
    cout << "Pop time: " << time << endl;
    recordStatus(time < clock_t(35) && time > clock_t(5), &successes);

    cout << "valid order: " << validOrder << endl;
    recordStatus(validOrder, &successes);

    cout << "is empty: " << stack.isEmpty() << endl;
    recordStatus(stack.isEmpty(), &successes);


    //Test Queue
    cout << "******TESTING QUEUE******" << endl;
    Queue<int> queue;
    start = clock();
    for (int i = N - 1; i > 0; --i)
    {
        queue.enqueue(i);
    }
    end = clock();
    time = (end - start);
    cout << "enqueue time: " << time << endl;
    recordStatus(time < clock_t(25), &successes);

    front = stack.top();
    cout << "front: " << front << endl;
    recordStatus(front == N - 1, &successes);

    start = clock();
    validOrder = true;
    for (int i = N - 1; i > 0; --i)
    {
        if (queue.isEmpty()) {
            validOrder = false;
            break;
        }
        int x = queue.dequeue();
        if (x != i)
            validOrder = false;
    }
    end = clock();
    time = (end - start);
    cout << "dequeue time: " << time << endl;
    recordStatus(time < clock_t(35), &successes);

    cout << "valid order: " << validOrder << endl;
    recordStatus(validOrder, &successes);

    cout << "is empty: " << queue.isEmpty() << endl;
    recordStatus(queue.isEmpty(), &successes);

    cout << "Passing Tests: " << successes << " out of 20" << endl;

    return 0;
}
