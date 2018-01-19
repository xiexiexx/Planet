#!/usr/bin/env python2
# -*- coding:utf8 -*-

"""
给出一组数字，对数字进行递归归并排序
"""

from __future__ import print_function
import random
import time


def gen_num_list(ln):
    """
    生成长度为 ln 的随机数数组
    """
    return [int(random.random() * 33) for __ in xrange(ln)]


def merge_simple(left_lst, right_lst):
    ln_left = len(left_lst)
    ln_right = len(right_lst)
    n_lst = [0, ] * (ln_left + ln_right)
    left_idx = right_idx = 0
    while (left_idx < ln_left) and (right_idx < ln_right):
        if left_lst[left_idx] < right_lst[right_idx]:
            n_lst[left_idx + right_idx] = left_lst[left_idx]
            left_idx += 1
        else:
            n_lst[left_idx + right_idx] = right_lst[right_idx]
            right_idx += 1
    if left_idx < ln_left:
        n_lst[left_idx + right_idx:] = left_lst[left_idx:]
    else:
        n_lst[left_idx + right_idx:] = right_lst[right_idx:]
    return n_lst

def merge_sort_simple(lst):
    """
    使用分治法，归并排序
    10000000，耗时：146.345419884，系统排序：2.12158203125
    1000000，耗时：13.3469378948，系统排序：0.190033912659
    分：从数组长度的中间分为两部分，递归获取排序结果
    治：两个排好序的数组，取最左边元素进行比较放到新的数组里
    """
    ln = len(lst)
    if ln > 1:
        mid = ln / 2
        left_lst = merge_sort_simple(lst[:mid])
        right_lst = merge_sort_simple(lst[mid:])
        return merge_simple(left_lst, right_lst)
    return lst


def merge_dust(lst, left, mid, right):
    ln_left = mid - left + 1
    ln_right = right - mid
    n_lst = [0, ] * (right - left + 1)
    left_idx, right_idx = left, mid + 1
    while (left_idx <= mid) and (right_idx <= right):
        if lst[left_idx] < lst[right_idx]:
            n_lst[left_idx - left + right_idx - mid - 1] = lst[left_idx]
            left_idx += 1
        else:
            n_lst[left_idx - left + right_idx - mid - 1] = lst[right_idx]
            right_idx += 1
    if left_idx <= mid:
        n_lst[-(mid+1-left_idx):] = lst[left_idx:mid+1]
    else:
        n_lst[-(right+1-right_idx):] = lst[right_idx:right+1]
    # print(lst, left, mid, right, n_lst, 'before')
    lst[left:right+1] = n_lst
    # print(lst, left, mid, right, n_lst, 'after')


def merge_sort_dust(lst, left, right):
    """
    使用下表方式
    效率没有提升
    """
    if left < right:
        mid = (left + right) / 2

        merge_sort_dust(lst, left, mid)
        merge_sort_dust(lst, mid + 1, right)
        merge_dust(lst, left, mid, right)


if __name__ == "__main__":
    lst = gen_num_list(1000000)
    print('start')
    start = time.time()
    sorted(lst)
    print("%s's result, time cost: %s" % ("system_sort", time.time() - start))

    start = time.time()
    merge_sort_simple(lst)
    print("%s's result, time cost: %s" % ("merge_sort_simple", time.time() - start))

    # print(lst)
    start = time.time()
    merge_sort_dust(lst, 0, len(lst) - 1)
    # print(lst)
    print("%s's result, time cost: %s" % ("merge_sort_dust", time.time() - start))
    
    # lst = [0, 4, 7, 26, 31, 3, 5, 27, 6, 6]
    # merge_dust(lst, 5, 7, 9)
    # print(lst)
