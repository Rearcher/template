import time

import numpy as np


def run_time(func):
    """用于记录程序运行时间的装饰器"""
    def wrapper(*args, **kw):
        begin_time = time.time()
        res = func(*args, **kw)
        print(f'{func.__name__} run time is {time.time() - begin_time:.2f}s')
        return res
    return wrapper

def euclidean_distance(a, b):
    """计算样本之间的欧几里得距离"""
    return np.linalg.norm(a - b)
