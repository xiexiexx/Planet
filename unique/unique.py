#!/usr/bin/env python2
# -*- coding:utf8 -*-

"""
给出一组数字，对数字进行排重和计数
复杂度 = 排序复杂度 + 排重计数复杂度 = O(nlogn) + O(n) = O(nlogn)
"""

from __future__ import print_function
import random


def gen_num_list(ln):
    """
    生成长度为 ln 的随机数数组
    """
    return [random.randrange(32) for __ in xrange(ln)]


def uniq_and_count(sorted_lst):
    """
    对已排好序的数组元素进行排重和计数输出
    每次打印数组排重后的数字及它出现的次数
    """
    # 不处理空数组
    if not sorted_lst:
        return

    left_value = sorted_lst[0]
    num = 1
    for right_value in sorted_lst[1:]:
        if right_value != left_value:
            print(left_value, num)
            left_value = right_value
            num = 0
        num += 1

    print(right_value, num)


if __name__ == "__main__":
    # 得到随机数组
    lst = gen_num_list(20)

    # 用系统方法对数组排序
    lst.sort()
    print('Sorted list is: %s' % lst)
    # 对排序后的数组元素进行排重和计数  
    uniq_and_count(lst)
