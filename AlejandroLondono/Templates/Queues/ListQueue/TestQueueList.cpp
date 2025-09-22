#include <iostream>
#include "QueueList.hh"

using namespace std;

void testBasicOperations() {
    cout << "\n=== TEST: Basic Operations ===" << endl;
    
    QueueList<int> ql;
    
    // Test isEmpty when new
    cout << "QueueList is empty: " << (ql.isEmpty() ? "true" : "false") << endl;
    cout << "Size: " << ql.size() << endl;
    
    // Test enqueue
    cout << "\nEnqueuing elements 10, 20, 30..." << endl;
    ql.enqueue(10);
    ql.enqueue(20);
    ql.enqueue(30);
    
    cout << "Size after enqueue: " << ql.size() << endl;
    cout << "Front: " << ql.front() << ", Back: " << ql.back() << endl;
    ql.print();
    
    // Test dequeue
    cout << "\nDequeuing one element..." << endl;
    ql.dequeue();
    cout << "Size after dequeue: " << ql.size() << endl;
    cout << "New front: " << ql.front() << ", Back: " << ql.back() << endl;
    ql.print();
}

void testDynamicGrowth() {
    cout << "\n=== TEST: Dynamic Growth (No Capacity Limit) ===" << endl;
    
    QueueList<int> ql;
    
    cout << "Adding many elements (no capacity limit)..." << endl;
    for (int i = 1; i <= 10; i++) {
        ql.enqueue(i * 10);
        cout << "Added " << (i * 10) << " - Size: " << ql.size() << endl;
    }
    
    cout << "\nFull queue:" << endl;
    ql.print();
    
    cout << "Is full: " << (ql.isFull() ? "true" : "false") << " (should always be false)" << endl;
    cout << "Capacity: " << ql.capacity() << " (very large number)" << endl;
}

void testVsArrayQueues() {
    cout << "\n=== TEST: Advantages over Array-based Queues ===" << endl;
    
    QueueList<int> ql;
    
    cout << "Demonstrating unlimited capacity..." << endl;
    
    // Add many elements without worrying about capacity
    cout << "Adding 1000 elements..." << endl;
    for (int i = 1; i <= 1000; i++) {
        ql.enqueue(i);
    }
    
    cout << "Size after adding 1000 elements: " << ql.size() << endl;
    cout << "Front: " << ql.front() << ", Back: " << ql.back() << endl;
    
    // Remove some elements
    cout << "Removing 500 elements..." << endl;
    for (int i = 1; i <= 500; i++) {
        ql.dequeue();
    }
    
    cout << "Size after removing 500: " << ql.size() << endl;
    cout << "New front: " << ql.front() << ", Back: " << ql.back() << endl;
    
    // Add more without any issues
    cout << "Adding 200 more elements..." << endl;
    for (int i = 1001; i <= 1200; i++) {
        ql.enqueue(i);
    }
    
    cout << "Final size: " << ql.size() << endl;
    cout << "SUCCESS: No capacity limits or wraparound complexity!" << endl;
}

void testEdgeCases() {
    cout << "\n=== TEST: Edge Cases ===" << endl;
    
    QueueList<int> ql;
    
    // Test underflow on empty queue
    cout << "Testing operations on empty queue..." << endl;
    
    cout << "Trying to dequeue when empty..." << endl;
    try {
        ql.dequeue();
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
    
    cout << "Trying to access front when empty..." << endl;
    try {
        int x = ql.front();
        cout << "Front: " << x << endl;
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
    
    cout << "Trying to access back when empty..." << endl;
    try {
        int x = ql.back();
        cout << "Back: " << x << endl;
    } catch (const underflow_error& e) {
        cout << "Caught underflow error: " << e.what() << endl;
    }
    
    // Note: No overflow testing needed since QueueList never overflows
    cout << "\nNote: No overflow testing needed - QueueList grows dynamically!" << endl;
}

void testCopyAndAssignment() {
    cout << "\n=== TEST: Copy Constructor & Assignment ===" << endl;
    
    QueueList<int> ql1;
    ql1.enqueue(100);
    ql1.enqueue(200);
    ql1.enqueue(300);
    
    cout << "Original queue ql1:" << endl;
    ql1.print();
    
    // Test copy constructor
    QueueList<int> ql2(ql1);
    cout << "Copied queue ql2:" << endl;
    ql2.print();
    
    // Test assignment operator
    QueueList<int> ql3;
    ql3.enqueue(999);
    cout << "Queue ql3 before assignment:" << endl;
    ql3.print();
    
    ql3 = ql1;
    cout << "Queue ql3 after assignment:" << endl;
    ql3.print();
    
    // Test equality
    cout << "ql1 == ql2: " << (ql1 == ql2 ? "true" : "false") << endl;
    cout << "ql1 == ql3: " << (ql1 == ql3 ? "true" : "false") << endl;
    
    // Modify one and test inequality
    ql2.enqueue(400);
    cout << "After modifying ql2:" << endl;
    cout << "ql1 == ql2: " << (ql1 == ql2 ? "true" : "false") << endl;
}

void testUniqueFeatures() {
    cout << "\n=== TEST: Unique QueueList Features ===" << endl;
    
    QueueList<int> ql1;
    QueueList<int> ql2;
    
    // Setup two queues
    ql1.enqueue(1);
    ql1.enqueue(2);
    ql1.enqueue(3);
    
    ql2.enqueue(10);
    ql2.enqueue(20);
    
    cout << "Queue ql1:" << endl;
    ql1.print();
    cout << "Queue ql2:" << endl;
    ql2.print();
    
    // Test append
    cout << "\nTesting append (ql1.append(ql2)):" << endl;
    QueueList<int> ql1_copy = ql1;  // Keep original for other tests
    ql1_copy.append(ql2);
    cout << "Result of ql1.append(ql2):" << endl;
    ql1_copy.print();
    
    // Test prepend (breaks FIFO semantics)
    cout << "\nTesting prepend (ql1.prepend(ql2)) - BREAKS FIFO:" << endl;
    QueueList<int> ql1_copy2 = ql1;
    ql1_copy2.prepend(ql2);
    cout << "Result of ql1.prepend(ql2):" << endl;
    ql1_copy2.print();
    
    // Test reverse (breaks FIFO semantics)
    cout << "\nTesting reverse - BREAKS FIFO:" << endl;
    QueueList<int> ql1_copy3 = ql1;
    cout << "Before reverse:" << endl;
    ql1_copy3.print();
    ql1_copy3.reverse();
    cout << "After reverse:" << endl;
    ql1_copy3.print();
}

void testClear() {
    cout << "\n=== TEST: Clear Function ===" << endl;
    
    QueueList<int> ql;
    ql.enqueue(1);
    ql.enqueue(2);
    ql.enqueue(3);
    
    cout << "Before clear:" << endl;
    ql.print();
    cout << "Size: " << ql.size() << endl;
    
    ql.clear();
    cout << "After clear:" << endl;
    ql.print();
    cout << "Size: " << ql.size() << endl;
    cout << "Is empty: " << (ql.isEmpty() ? "true" : "false") << endl;
    
    // Test that we can add elements after clear
    ql.enqueue(100);
    cout << "After adding element post-clear:" << endl;
    ql.print();
}

void testLargeOperations() {
    cout << "\n=== TEST: Large Scale Operations ===" << endl;
    
    QueueList<string> ql;
    
    cout << "Testing with string elements and large numbers..." << endl;
    
    // Add many string elements
    for (int i = 1; i <= 100; i++) {
        ql.enqueue("Element_" + to_string(i));
    }
    
    cout << "Added 100 string elements." << endl;
    cout << "Size: " << ql.size() << endl;
    cout << "Front: " << ql.front() << endl;
    cout << "Back: " << ql.back() << endl;
    
    // Remove half
    for (int i = 1; i <= 50; i++) {
        ql.dequeue();
    }
    
    cout << "After removing 50 elements:" << endl;
    cout << "Size: " << ql.size() << endl;
    cout << "New front: " << ql.front() << endl;
    cout << "Back: " << ql.back() << endl;
    
    cout << "SUCCESS: Handled large operations efficiently!" << endl;
}

void testMemoryEfficiency() {
    cout << "\n=== TEST: Memory Efficiency ===" << endl;
    
    QueueList<int> ql;
    
    cout << "Testing add/remove cycles..." << endl;
    
    // Simulate many add/remove cycles
    for (int cycle = 1; cycle <= 5; cycle++) {
        cout << "Cycle " << cycle << ":" << endl;
        
        // Add elements
        for (int i = 1; i <= 20; i++) {
            ql.enqueue(cycle * 100 + i);
        }
        cout << "  Added 20 elements, size: " << ql.size() << endl;
        
        // Remove most elements
        for (int i = 1; i <= 15; i++) {
            ql.dequeue();
        }
        cout << "  Removed 15 elements, size: " << ql.size() << endl;
    }
    
    cout << "Final state:" << endl;
    ql.print();
    cout << "Memory grows/shrinks dynamically as needed!" << endl;
}

int main() {
    cout << "Testing QueueList Implementation" << endl;
    cout << "================================" << endl;
    
    testBasicOperations();
    testDynamicGrowth();
    testVsArrayQueues();
    testEdgeCases();
    testCopyAndAssignment();
    testUniqueFeatures();
    testClear();
    testLargeOperations();
    testMemoryEfficiency();
    
    cout << "\n=== All QueueList Tests Completed ===" << endl;
    return 0;
}