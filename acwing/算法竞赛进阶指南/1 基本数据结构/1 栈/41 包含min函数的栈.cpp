// https://www.acwing.com/problem/content/90/

class MinStack {
public:
	stack<int> nums, minNum;

	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		nums.push(x);
		if (minNum.empty() || x <= minNum.top()) {
			minNum.push(x);
		}
	}

	void pop() {
		if (nums.empty()) {
			return;
		}
		if (nums.top() == minNum.top()) {
			minNum.pop();
		}
		nums.pop();
	}

	int top() {
		return nums.top();
	}

	int getMin() {
		return minNum.top();
	}
};
