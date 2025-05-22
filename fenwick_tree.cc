#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class FenwickTree {
public:
    /**
     * Constructs a Fenwick Tree of the given size.
     * @param size The number of elements in the array represented by the Fenwick Tree.
     *
     * @note The space complexity is O(n), where n is the size of the tree.
     */
    FenwickTree(int size) : size_(size), tree_(size + 1, 0) {}

    /**
     * Updates the value at the given index in the Fenwick Tree.
     * @param index The 0-based index to update.
     * @param delta The value to add to the element at the given index.
     *
     * @note The time complexity of this operation is O(log n).
     */
    void update(int index, int delta) {
        index++; // 1-based indexing
        while (index <= size_) {
            tree_[index] += delta;
            index += index & (-index);
        }
    }

    /**
     * Queries the sum of elements from the beginning up to the given index (inclusive).
     * @param index The 0-based index up to which the sum is calculated.
     * @return The sum of elements from index 0 to the given index.
     *
     * @note The time complexity of this operation is O(log n).
     */
    int query(int index) {
        index++; // 1-based indexing
        int sum = 0;
        while (index > 0) {
            sum += tree_[index];
            index -= index & (-index);
        }
        return sum;
    }

private:
    /**
     * The size of the original array (number of elements).
     */
    int size_;

    /**
     * The internal tree representation of the Fenwick Tree.
     * `tree_[i]` stores the sum of elements from index `i - (i & -i) + 1` to `i` (inclusive).
     * `(i & -i)` is the lowest set bit of `i`.
     */
    vector<int> tree_;
};

void testFenwickTree() {
    // Test case 1: Basic functionality
    FenwickTree ft1(5);
    ft1.update(0, 1);
    assert(ft1.query(0) == 1);
    assert(ft1.query(1) == 1);
    assert(ft1.query(2) == 1);
    ft1.update(1, 2);
    assert(ft1.query(0) == 1);
    assert(ft1.query(1) == 3);
    assert(ft1.query(2) == 3);
    ft1.update(2, 3);
    assert(ft1.query(0) == 1);
    assert(ft1.query(1) == 3);
    assert(ft1.query(2) == 6);
    ft1.update(3, 4);
    ft1.update(4, 5);
    assert(ft1.query(0) == 1);
    assert(ft1.query(1) == 3);
    assert(ft1.query(2) == 6);
    assert(ft1.query(3) == 10);
    assert(ft1.query(4) == 15);

    // Test case 2: Updates to existing elements
    FenwickTree ft2(3);
    ft2.update(0, 10);
    assert(ft2.query(0) == 10);
    assert(ft2.query(1) == 10);
    assert(ft2.query(2) == 10);
    ft2.update(1, 20);
    assert(ft2.query(0) == 10);
    assert(ft2.query(1) == 30);
    assert(ft2.query(2) == 30);
    ft2.update(0, 5);
    assert(ft2.query(0) == 15);
    assert(ft2.query(1) == 35);
    assert(ft2.query(2) == 35);

    // Test case 3: Querying individual elements (difference of queries)
    FenwickTree ft3(4);
    ft3.update(2, 7);
    assert(ft3.query(0) == 0);
    assert(ft3.query(1) == 0);
    assert(ft3.query(2) == 7);
}


void runFenwickTreeSample() {
    FenwickTree ft(10);

    ft.update(0, 10);
    ft.update(2, 5);
    cout << "Sum up to index 0: " << ft.query(0) << endl;
    cout << "Sum up to index 1: " << ft.query(1) << endl;
    cout << "Sum up to index 2: " << ft.query(2) << endl;
    ft.update(5, 7);
    ft.update(9, 3);
    cout << "Sum up to index 4: " << ft.query(4) << endl;
    cout << "Sum up to index 5: " << ft.query(5) << endl;
    cout << "Sum up to index 9: " << ft.query(9) << endl;
}

int main() {
    testFenwickTree();
    runFenwickTreeSample();
    return 0;
}
