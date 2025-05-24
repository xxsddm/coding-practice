public class Trie { // 字典树(处理字符串, 目前仅支持小写字母, 扩大范围则hashmap更适用)(LeetCode 140, 212题测试通过)
    final int numChar;
    final Node root;
    final char benchmark;
    int size;

    public class Node {
        int count = 0;
        String val; // val保存路径起点到终点对应字符串
        Node[] next = new Node[numChar];    // 下一个字符的集合
        Node() {
        }

        Node(String str) {
            val = str;
        }
    }

    public Trie() {
        this(26, 'a');
    }

    public Trie(int num, char letter) {
        numChar = num;
        root = new Node();
        benchmark = letter;
    }

    public boolean contain(String target) { // 检查是否包含目标字符串
        return get(root, target, 0) != null;
    }

    public void add(String target) {    // 将目标字符串放入字典树
        add(root, target, 0);
    }

    public int size() {
        return size;
    }

    public void delete(String target) {
        delete(root, target, 0);    // 不可root=delete (根节点不必要删除)
    }

    String get(Node node, String target, int idx) { // idx为待检查索引
        if (idx == target.length()) {
            return target;
        }
        if (node == null || node.next[target.charAt(idx)] == null) {
            return null;
        }
        return get(node.next[target.charAt(idx)], target, idx + 1);
    }

    Node add(Node node, String target, int idx) { // idx为待检查索引
        if (node == null) {
            node = new Node();
        }
        if (idx == target.length()) {   // 若已扫过整个target字符串
            if (node.val == null) { // 若add前改末尾结点不包含该字符串, 则说明增加了一个字符串
                size++;
            }
            node.val = target;
            return node;
        }
        int i = target.charAt(idx) - benchmark;
        Node temp = add(node.next[i], target, idx + 1);
        if (node.next[i] == null) {
            node.count++;
        }
        node.next[i] = temp;
        return node;
    }

    Node delete(Node node, String target, int idx) {    // idx为待检查索引
        if (node == null) {
            return null;
        }
        if (idx == target.length()) {
            if (node.val != null) { // 存在则变为null
                node.val = null;
                size--;
            }
            return node;
        }
        int i = target.charAt(idx) - benchmark;
        Node temp = delete(node.next[i], target, idx + 1);
        if (temp == null && node.next[i] != null) {
            node.count--;
        }
        node.next[i] = temp;

        // 对子节点进行删除操作后, 检查当前节点是否需要删除
        return (node.val == null && node.count == 0) ? null : node;
    }
}
