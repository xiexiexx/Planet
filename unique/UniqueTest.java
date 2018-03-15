import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * @author zhengxin
 * @date 2018-03-15 19:51:42
 */
public class UniqueTest {


    public static void main(String[] a){

        Integer[] ints = new Integer[]{7, 9, 3, 9, 2, 1, 7, 2};

        System.out.print(uniqueRight(ints));


    }

    /**
     * 左边界控制
     * @author zhengxin
     * @date   18/3/15 下午8:00
     */
    public static Map<Comparable, Integer> uniqueLeft(Comparable[] s){

        Arrays.sort(s);

        Map<Comparable, Integer> map = new HashMap<>();

        int l = 0;
        int r;
        for (; l<s.length; l=r){

            for (r=l+1; r<s.length; ++r)
                if (s[r] != s[l]) break;

            map.put(s[l], r-l);


        }

        return map;

    }

    /**
     * 右边界控制
     * @author zhengxin
     * @date   18/3/15 下午8:00
     */
    public static Map<Comparable, Integer> uniqueRight(Comparable[] s){

        Arrays.sort(s);

        Map<Comparable, Integer> map = new HashMap<>();

        int l=0,r=0;

        for (; r<s.length; ++r)
            if (s[r] != s[l]){
                map.put(s[l], r-l);
                l = r;
            }

        map.put(s[l], r-l);

        return map;

    }



}
