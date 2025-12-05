#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
using namespace std;

template <typename Priority, typename Value>
class Heap
{
private:
    vector<pair<Priority, Value>> heap;

   unsigned int left(unsigned int i) const { return 2 * i + 1; }
   unsigned int right(unsigned int i) const { return 2 * i + 2; }
   unsigned int parent(unsigned int i) const { return (i - 1) / 2; }
   
    int size() const { return heap.size(); }

    void heapifyUp(int i)
    {
        while (i > 0 && heap[i].first > heap[parent(i)].first)
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i)
    {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < size() && heap[l].first > heap[largest].first)
            largest = l;
        if (r < size() && heap[r].first > heap[largest].first)
            largest = r;

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:

    Heap() {}

    void insert(const Priority &p, const Value &v)
    {
        heap.push_back({p, v});
        heapifyUp(size() - 1);
    }

    pair<Priority, Value> extractMax()
    {
        if (size() == 0)
            throw runtime_error("Heap is empty");

        pair<Priority, Value> maxElem = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (size() > 0)
            heapifyDown(0);

        return maxElem;
    }

    void printHeap() const
    {
        for (auto &p : heap)
            cout << "(" << p.first << ", " << p.second << ") ";
        cout << "\n";
    }

    const pair<Priority, Value>& getMax() const {
    if (heap.empty())
        throw runtime_error("Heap is empty");
    return heap[0];
}

};

int main()
{
    Heap<int, int> heap;

    heap.insert(10, 1);
    heap.insert(4, 2);
    heap.insert(15, 3);
    heap.insert(7, 4);
    heap.insert(20, 5);
    heap.insert(11, 2);


    cout << "Heap actual: ";
    heap.printHeap();

    cout << "Extraer máximo: ";
    auto maxElem = heap.extractMax();
    cout << "(" << maxElem.first << ", " << maxElem.second << ")\n";

    cout << "Heap luego de extraer: ";
    heap.printHeap();

    return 0;
}