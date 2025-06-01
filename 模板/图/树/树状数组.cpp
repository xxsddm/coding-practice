#include <vector>

using namespace std;

template <typename T>
class BinaryIndexedTree {
public:
    vector<T> tree{};
    int size{};

    explicit BinaryIndexedTree(int size): size(size) {
        tree.resize(size + 1);
    }

    void change(int loc, T delta) {
        while (loc <= size) {
            tree[loc] += delta;
            loc += loc & -loc;
        }
    }

    T query(int loc) {
        T ans{};
        while (loc) {
            ans += tree[loc];
            loc ^= loc & -loc;
        }
        return ans;
    }
};