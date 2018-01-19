#!/usr/bin/env python2
# -*- encoding:utf-8 -*-

"""
使用 Python 计算 Fibonacci 数：0, 1, 1, 2, 3, 5, ...

1. fibonacci_simple, 最简单的写法，直接利用递归调用
2. fibonacci_list，使用列表缓存中间结果
3. fibonacci_formula，使用公式推导
"""

from __future__ import print_function
import signal
import time


def signle_handler(signal_n, frame):
    """
    利用信号处理实现简单的定时器
    :param signal_n:
    :param frame:
    """
    raise Exception('end of time')


def timer(func):
    """
    计时器修饰器
    :param func:
    """
    def wrapper(*args, **kwargs):
        _start = time.time()
        _result = func(*args, **kwargs)
        print("%s's result is %s, time cost: %s" % (func, _result, time.time() - _start))
        return _result
    return wrapper


def fibonacci_simple(n):
    """
    利用递归调用德方式计算，f_{n} = f_{n-1} + f_{n-2}
    :param n: n>0
    :return
    """
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    return fibonacci_simple(n - 1) + fibonacci_simple(n - 2)


@timer
def fibonacci_list(n):
    """
    用列表缓存中间的计算结果
    :param n: n>0
    :return
    """
    lst = [0, 1, 1]
    while len(lst) < n + 1:
        ln = len(lst)
        lst.append(lst[ln - 1] + lst[ln - 2])
    return lst[0] if n < 0 else lst[n]


def fibonacci_formula(n):
    """
    利用公式推导，纯数学计算
    f_{2m + 1} = f_{m} ** 2 + f_{m+1} ** 2
    f_{2m} = (f_{m-1} + f_{m+1}) * f_{m} = (2 * f_{m + 1} - f_{m}) * f_{m}
    奇数情况 n == 2m + 1:
        (f_{n}, f_{n+1})
         = (f_{2m+1}, f_{2m+2})
         = (f_{m} ** 2 + f_{m+1} ** 2, (f_{m} + f_{m+2}) * f_{m+1})
         = (f_{m} ** 2 + f_{m+1} ** 2, (2 * f_{m} + f_{m+1}) * f_{m+1})
    偶数情况 n == 2m:
        (f_{n}, f_{n+1})
         = (f_{2m}, f_{2m+1})
         = ((2 * f_{m+1} - f_{m}) * f_{m}, f_{m} ** 2 + f_{m+1} ** 2)
    比如，n = 1, m = 0:
        fibonacci_formula(1)
         = (f_{0} ** 2 + f_{1} ** 2, (2 * f_{0} + f_{1}) * f_{1})
         = (0 + 1, (0 + 1) * 1)
         = (1, 1)
    比如，n = 2, m = 1:
        fibonacci_formula(2)
         = ((2 * f_{2} - f_{1}) * f_{1}， f_{1} ** 2 + f_{2} ** 2)
         = ((2 * 1 - 1）* 1, 1 + 1)
         = (1, 2)
    :param n: n>0
    :return (f_{n}, f_{n+1})
    """
    if n <= 0:
        return (0, 1)
    # m = n / 2, fibonacci_formula(m) get (f_{m}, f_{m+1})
    f_m, f_m1 = fibonacci_formula(n / 2)
    if n % 2:
        return f_m ** 2 + f_m1 ** 2, (2 * f_m + f_m1) * f_m1
    return (2 * f_m1 - f_m) * f_m, f_m ** 2 + f_m1 ** 2


if __name__ == '__main__':
    signal.signal(signal.SIGALRM, signle_handler)
    signal.alarm(10)
    # 1. fibonacci_simple 计算第 30 个 Fibonacci 数，用时：0.852499961853
    # start = time.time()
    # result = fibonacci_simple(30)
    # print("%s's result is %s, time cost: %s" % ("fibonacci_simple", result, time.time() - start))
    # 2. fibonacci_list 计算第 200 个 Fibonacci 数，用时：0.000149011611938
    # fibonacci_list(200)
    # 3. fibonacci_formula 计算第 200 个 Fibonacci 数，0.000126123428345
    start = time.time()
    result = fibonacci_formula(200)
    print("%s's result is %s, time cost: %s" % ("fibonacci_formula", result, time.time() - start))
