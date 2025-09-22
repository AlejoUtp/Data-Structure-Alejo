#include <iostream>
#include "CircularQueue.hh"

using namespace std;

void testBasicOperations() {
    cout << "\n=== TEST: Basic Operations ===" << endl;
    
    CircularQueue<int> cq(5);  // CircularQueue con capacidad 5
    
    // Test isEmpty when new
    cout << "CircularQueue is empty: " << (cq.isEmpty() ? "true" : "false") << endl;
    cout << "Size: " << cq.size() << ", Capacity: " << cq.capacity() << endl;
    
    // Test enqueue
    cout << "\nEnqueuing elements 10, 20, 30..." << endl;
    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    
    cout << "Size after enqueue: " << cq.size() << endl;
    cout << "Front: " << cq.front() << ", Back: " << cq.back() << endl;
    cq.print();
    
    // Test dequeue
    cout << "\nDequeuing one element..." << endl;
    cq.dequeue();
    cout << "Size after dequeue: " << cq.size() << endl;
    cout << "New front: " << cq.front() << ", Back: " << cq.back() << endl;
    cq.print();
}

void testCircularBehavior() {
    cout << "\n=== TEST: Circular Behavior (Key Feature) ===" << endl;
    
    CircularQueue<char> cq(4);  // Small queue to demonstrate wraparound
    
    // Fill to capacity
    cout << "Filling queue to capacity with A, B, C, D..." << endl;
    cq.enqueue('A');
    cq.enqueue('B');
    cq.enqueue('C');
    cq.enqueue('D');
    
    cout << "Full queue:" << endl;
    cq.print();
    cout << "Is full: " << (cq.isFull() ? "true" : "false") << endl;
    
    // Remove some elements
    cout << "\nRemoving 2 elements (A, B)..." << endl;
    cq.dequeue();  // Remove A
    cq.dequeue();  // Remove B
    
    cout << "After removing 2 elements:" << endl;
    cq.print();
    cout << "Front: " << cq.front() << ", Back: " << cq.back() << endl;
    
    // Add new elements - this is where circular behavior shines
    cout << "\nAdding new elements E, F (should wraparound)..." << endl;
    cq.enqueue('E');
    cq.enqueue('F');
    
    cout << "After adding E, F (notice wraparound):" << endl;
    cq.print();
    cout << "Front: " << cq.front() << ", Back: " << cq.back() << endl;
    cout << "Size: " << cq.size() << endl;
}

void testFullCircularCycle() {
    cout << "\n=== TEST: Full Circular Cycle ===" << endl;
    
    CircularQueue<int> cq(3);  // Very small queue
    
    cout << "Demonstrating complete circular usage..." << endl;
    
    // Fill initially
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    cout << "Initial fill: ";
    cq.print();
    
    // Simulate many operations to show wraparound
    for (int i = 4; i <= 10; i++) {
        cout << "\nStep " << (i-3) << ":" << endl;
        cq.dequeue();  // Remove front
        cout << "After dequeue: ";
        cq.print();
        
        cq.enqueue(i);  // Add new element
        cout << "After enqueue(" << i << "): ";
        cq.print();
        cout << "Front: " << cq.front() << ", Back: " << cq.back() << endl;
    }
}

void testBackFunction() {
    cout << "\n=== TEST: Back Function with Wraparound ===" << endl;
    
    CircularQueue<int> cq(4);
    
    // Test back function in various scenarios
    cq.enqueue(100);
    cout << "After enqueue(100) - Back: " << cq.back() << endl;
    cq.print();
    
    cq.enqueue(200);
    cq.enqueue(300);
    cq.enqueue(400);  // Queue full at positions [100,200,300,400]
    cout << "Full queue - Back: " << cq.back() << endl;
    cq.print();
    
    // Remove some and add to test wraparound of back()
    cq.dequeue(); // Remove 100
    cq.dequeue(); // Remove 200
    cout << "After 2 dequeues - Back: " << cq.back() << endl;
    cq.print();
    
    cq.enqueue(500); // Should go to position 0
    cout << "After enqueue(500) - Back: " << cq.back() << endl;
    cq.print();
    
    cq.enqueue(600); // Should go to position 1  
    cout << "After enqueue(600) - Back: " << cq.back() << endl;
    cq.print();
}

void testEdgeCases() {
    cout << "\n=== TEST: Edge Cases ===" << endl;
    
    CircularQueue<int> cq(3);
    
    // Test overflow
    cout << "Filling to capacity..." << endl;
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    cout << "Is full: " << (cq.isFull() ? "true" : "false") << endl;
    
    cout << "Trying to enqueue when full..." << endl;
    try {
        cq.enqueue(4);
    } catch (const overflow_error& e) {
        cout << "Caught overflow error: " << e.what() << endl;
    }
    
    // Test underflow
    cout << "\nEmptying queue completely..." << endl;
    cq.dequeue();
    cq.dequeue();
    cq.dequeue();
    
    cout << "Is empty: " << (cq.isEmpty() ? "true" : "false") << endl;
    cout << "Trying to dequeue when empty..." << endl;
    try {
        cq.dequeue();
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
    
    cout << "Trying to access front when empty..." << endl;
    try {
        int x = cq.front();
        cout << "Front: " << x << endl;
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
    
    cout << "Trying to access back when empty..." << endl;
    try {
        int x = cq.back();
        cout << "Back: " << x << endl;
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
}

void testVsRegularQueue() {
    cout << "\n=== TEST: Advantage over Regular Queue ===" << endl;
    
    cout << "Demonstrating why circular queue is better..." << endl;
    
    CircularQueue<int> cq(4);
    
    // Simulate scenario where regular queue would fail
    cout << "\nScenario: Add 4, remove 2, try to add 3 more" << endl;
    
    // Add 4 elements
    cout << "Adding 4 elements..." << endl;
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    cq.enqueue(4);
    cq.print();
    
    // Remove 2 elements  
    cout << "Removing 2 elements..." << endl;
    cq.dequeue();
    cq.dequeue();
    cq.print();
    
    // Try to add 2 more (regular queue couldn't do this efficiently)
    cout << "Adding 2 more elements (5, 6)..." << endl;
    cq.enqueue(5);
    cq.enqueue(6);
    cq.print();
    
    cout << "SUCCESS: Circular queue reused space efficiently!" << endl;
    cout << "Regular queue would need shifting or be 'broken' at this point." << endl;
}

void testCopyAndAssignment() {
    cout << "\n=== TEST: Copy Constructor & Assignment ===" << endl;
    
    CircularQueue<int> cq1(4);
    
    // Create a circular state
    cq1.enqueue(10);
    cq1.enqueue(20);
    cq1.enqueue(30);
    cq1.enqueue(40);
    cq1.dequeue();
    cq1.dequeue();
    cq1.enqueue(50);
    cq1.enqueue(60);  // Now in wrapped state
    
    cout << "Original circular queue cq1:" << endl;
    cq1.print();
    
    // Test copy constructor
    CircularQueue<int> cq2(cq1);
    cout << "Copied queue cq2:" << endl;
    cq2.print();
    
    // Test assignment
    CircularQueue<int> cq3(4);
    cq3 = cq1;
    cout << "Assigned queue cq3:" << endl;
    cq3.print();
    
    // Test equality
    cout << "cq1 == cq2: " << (cq1 == cq2 ? "true" : "false") << endl;
    cout << "cq1 == cq3: " << (cq1 == cq3 ? "true" : "false") << endl;
}

void testClear() {
    cout << "\n=== TEST: Clear Function ===" << endl;
    
    CircularQueue<int> cq(4);
    
    // Create wrapped state
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    cq.dequeue();
    cq.enqueue(4);
    cq.enqueue(5);  // Wrapped state
    
    cout << "Before clear (wrapped state):" << endl;
    cq.print();
    
    cq.clear();
    cout << "After clear:" << endl;
    cq.print();
    cout << "Is empty: " << (cq.isEmpty() ? "true" : "false") << endl;
    
    // Test that it works normally after clear
    cq.enqueue(100);
    cq.enqueue(200);
    cout << "After adding elements post-clear:" << endl;
    cq.print();
}

int main() {
    cout << "Testing CircularQueue Implementation" << endl;
    cout << "====================================" << endl;
    
    testBasicOperations();
    testCircularBehavior();
    testFullCircularCycle();
    testBackFunction();
    testEdgeCases();
    testVsRegularQueue();
    testCopyAndAssignment();
    testClear();
    
    cout << "\n=== All CircularQueue Tests Completed ===" << endl;
    return 0;
}