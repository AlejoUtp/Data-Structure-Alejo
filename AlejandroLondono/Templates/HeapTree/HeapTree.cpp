#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
using namespace std;

template <typename Priority, typename Value>
class HeapTree
{
private:
    vector<pair<Priority, Value>> heap;

   unsigned int left(unigned int i) const { return 2 * i + 1; }
   unsigned int right(unsigned int i) const { return 2 * i + 2; }
   unsigned int parent(unsigned int i) const { return (i - 1) / 2; }

    int size() const { return (int)heap.size(); }

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
    HeapTree() {}

    void insert(const Priority &p, const Value &v)
    {
        heap.push_back({p, v});
        heapifyUp(size() - 1);
    }

    pair<Priority, Value> extractMax()
    {
        if (size() == 0)
            throw runtime_error("HeapTree is empty");

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
};

int main()
{
    HeapTree<int, string> heap;

    heap.insert(10, "A");
    heap.insert(4, "B");
    heap.insert(15, "C");
    heap.insert(7, "D");

    cout << "Heap actual: ";
    heap.printHeap();

    cout << "Extraer máximo: ";
    auto maxElem = heap.extractMax();
    cout << "(" << maxElem.first << ", " << maxElem.second << ")\n";

    cout << "Heap luego de extraer: ";
    heap.printHeap();

    return 0;
}