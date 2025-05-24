import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class PrimeFactorization {
    public static List<Integer> decompose(int num) {
        LinkedList<Integer> container = new LinkedList<>();
        // 若原始n的因数divisor不是质数, 则n一定由较小的质数prime(prime是divisor的因数)除到无法继续除
        for (int divisor = 2; divisor <= num / divisor; divisor++) {
            while (num % divisor == 0) {
                container.add(divisor);
                num /= divisor;
            }
        }
        // 考虑最后无法继续分解的质数
        if (num > 1) {
            container.add(num);
        }
        return container;
    }

    public static void main(String[] args) {    // 测试(LeetCode 650题测试通过)
        Scanner input = new Scanner(System.in);
        System.out.println("输入待分解的正整数(大于1)");
        int num = input.nextInt();
        if (num <= 1) {
            throw new IllegalArgumentException("必须是大于1的正整数");
        }
        System.out.println(PrimeFactorization.decompose(num));
    }
}
