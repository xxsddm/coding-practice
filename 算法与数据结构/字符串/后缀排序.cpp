#include <cstring>
#include <iostream>

char word[1000001];
int *rank, *rank2idx, *container, *counter, *pre;
int length;

void countSort() {
    int counterTemp[130];
    memset(counterTemp, 0, sizeof(counterTemp));
    for (int i = 0; i < length; i++) {
        counterTemp[word[i] + 1]++;
    }
    for (int i = 48; i < 124; i++) {
        counterTemp[i] += counterTemp[i - 1];
    }
    for (int i = 0; i < length; i++) {
        rank[i] = counterTemp[word[i]] + 1;
    }
}

bool radixSort(int step) {
    memcpy(container + step, rank + step, sizeof(int) * (length - step));
    memset(pre, -1, sizeof(int) * (length + 1));

    // counter辅助基数排序
    memset(counter, 0, sizeof(int) * (length + 1));
    counter[1] = step;
    for (int i = step; i < length; i++) {
        counter[rank[i] + 1]++;
    }
    for (int i = 1; i <= length; i++) {
        counter[i] += counter[i - 1];
    }
    for (int i = length - step; i < length; i++) {
        rank2idx[counter[0]++] = i;
    }
    for (int i = step; i < length; i++) {
        rank2idx[counter[rank[i]]++] = i - step;
    }

    memset(counter, 0, sizeof(int) * (length + 2));
    for (int i = 0; i < length; i++) {
        counter[rank[i] + 1]++;
    }
    bool ans = false;
    for (int i = 1; i <= length; i++) {
        counter[i] += counter[i - 1];
        if (counter[i] != i - 1) {
            ans = true;
        }
    }
    if (!ans) {
        return ans;
    }
    // rank[rank2idx[i]]保存按第二关键字排序后, 排序i的元素的初始rank
    for (int i = 0, j, k; i < length; i++) {
        j = rank[rank2idx[i]];
        k = (rank2idx[i] + step < length) ? container[rank2idx[i] + step] : 0;
        rank[rank2idx[i]] = (k == pre[j]) ? counter[j] : ++counter[j];
        pre[j] = k;
    }
    return true;
}

int main() {  // 洛谷P3809测试通过
    scanf("%s", word);
    length = (int)strlen(word);
    rank = new int[length], rank2idx = new int[length + 1];
    container = new int[length + 1], counter = new int[length + 2];
    pre = new int[length + 1];
    countSort();
    for (int step = 1; step < length; step <<= 1) {
        if (!radixSort(step)) {
            break;
        }
    }
    for (int i = 0; i < length; i++) {
        rank2idx[rank[i]] = i + 1;
    }
    for (int i = 1; i <= length; i++) {
        printf("%d ", rank2idx[i]);
    }
    return 0;
}
