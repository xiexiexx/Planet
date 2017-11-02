import java.math.BigInteger;

public class Fibonacci {
    //Fibonacci compute O(lg n)
    public static BigInteger[] Fib(BigInteger n) {
        if (n.equals(BigInteger.ZERO)) return new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};
        BigInteger[] tmp = Fib(n.divide(BigInteger.valueOf(2)));
        if (n.and(BigInteger.ONE).equals(BigInteger.ONE)) {
            return new BigInteger[]{tmp[0].multiply(tmp[0]).add(tmp[1].multiply(tmp[1])),
                    tmp[0].multiply(BigInteger.valueOf(2)).add(tmp[1]).multiply(tmp[1])};
        }
        else {
            return new BigInteger[]{tmp[1].multiply(BigInteger.valueOf(2)).subtract(tmp[0]).multiply(tmp[0]),
                    tmp[0].multiply(tmp[0]).add(tmp[1].multiply(tmp[1]))};
        }
    }

    public static void main(String[] args) {
        BigInteger n = BigInteger.valueOf(10);
        BigInteger result = Fib(n)[0];
        System.out.println(result);
    }
}
