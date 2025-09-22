#include <iostream>
#include "Queue.hh"

using namespace std;

void testBasicOperations() {
    cout << "\n=== TEST: Basic Operations ===" << endl;
    
    Queue<int> q(5);  // Queue con capacidad 5
    
    // Test isEmpty when new
    cout << "Queue is empty: " << (q.isEmpty() ? "true" : "false") << endl;
    cout << "Size: " << q.size() << ", Capacity: " << q.capacity() << endl;
    
    // Test enqueue
    cout << "\nEnqueuing elements 10, 20, 30..." << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    cout << "Size after enqueue: " << q.size() << endl;
    cout << "Front: " << q.front() << ", Back: " << q.back() << endl;
    q.print();
    
    // Test dequeue
    cout << "\nDequeuing one element..." << endl;
    q.dequeue();
    cout << "Size after dequeue: " << q.size() << endl;
    cout << "New front: " << q.front() << ", Back: " << q.back() << endl;
    q.print();
}

void testEdgeCases() {
    cout << "\n=== TEST: Edge Cases ===" << endl;
    
    Queue<int> q(3);  // Queue pequeña para probar límites
    
    // Test fill to capacity
    cout << "Filling queue to capacity..." << endl;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    
    cout << "Is full: " << (q.isFull() ? "true" : "false") << endl;
    q.print();
    
    // Test overflow
    cout << "\nTrying to enqueue when full..." << endl;
    try {
        q.enqueue(4);
    } catch (const overflow_error& e) {
        cout << "Caught overflow error: " << e.what() << endl;
    }
    
    // Test empty queue
    cout << "\nEmptying queue completely..." << endl;
    q.dequeue(); // Remove 1
    q.dequeue(); // Remove 2  
    q.dequeue(); // Remove 3
    
    cout << "Is empty: " << (q.isEmpty() ? "true" : "false") << endl;
    cout << "Size: " << q.size() << endl;
    
    // Test underflow
    cout << "Trying to dequeue when empty..." << endl;
    try {
        q.dequeue();
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
    
    // Test front/back on empty
    cout << "Trying to access front when empty..." << endl;
    try {
        int x = q.front();
        cout << "Front: " << x << endl;
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
}

void testCopyAndAssignment() {
    cout << "\n=== TEST: Copy Constructor & Assignment ===" << endl;
    
    Queue<int> q1(4);
    q1.enqueue(100);
    q1.enqueue(200);
    q1.enqueue(300);
    
    cout << "Original queue q1:" << endl;
    q1.print();
    
    // Test copy constructor
    Queue<int> q2(q1);
    cout << "Copied queue q2:" << endl;
    q2.print();
    
    // Test assignment operator
    Queue<int> q3(4);  // Same capacity required
    q3.enqueue(999);
    cout << "Queue q3 before assignment:" << endl;
    q3.print();
    
    q3 = q1;
    cout << "Queue q3 after assignment:" << endl;
    q3.print();
    
    // Test equality
    cout << "q1 == q2: " << (q1 == q2 ? "true" : "false") << endl;
    cout << "q1 == q3: " << (q1 == q3 ? "true" : "false") << endl;
    
    // Test assignment with different capacity
    cout << "\nTrying assignment with different capacity..." << endl;
    Queue<int> q4(3);  // Different capacity
    try {
        q4 = q1;
    } catch (const invalid_argument& e) {
        cout << "Caught invalid_argument: " << e.what() << endl;
    }
}

void testQueueReset() {
    cout << "\n=== TEST: Queue Reset Feature ===" << endl;
    
    Queue<int> q(5);
    
    // Fill partially, then empty completely
    cout << "Adding and removing elements to test reset..." << endl;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    
    cout << "Before dequeue operations:" << endl;
    q.print();
    
    q.dequeue();
    q.dequeue();
    cout << "After 2 dequeues (should have 1 element):" << endl;
    q.print();
    
    q.dequeue();  // This should trigger reset
    cout << "After final dequeue (should be empty and reset):" << endl;
    q.print();
    
    // Add elements again to see if it starts from beginning
    cout << "Adding elements after reset:" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.print();
}

void testClear() {
    cout << "\n=== TEST: Clear Function ===" << endl;
    
    Queue<int> q(4);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    
    cout << "Before clear:" << endl;
    q.print();
    cout << "Size: " << q.size() << endl;
    
    q.clear();
    cout << "After clear:" << endl;
    q.print();
    cout << "Size: " << q.size() << endl;
    cout << "Is empty: " << (q.isEmpty() ? "true" : "false") << endl;
    
    // Test that we can add elements after clear
    q.enqueue(100);
    cout << "After adding element post-clear:" << endl;
    q.print();
}

int main() {
    cout << "Testing Queue Implementation" << endl;
    cout << "============================" << endl;
    
    testBasicOperations();
    testEdgeCases();
    testCopyAndAssignment();
    testQueueReset();
    testClear();
    
    cout << "\n=== All Tests Completed ===" << endl;
    return 0;
}