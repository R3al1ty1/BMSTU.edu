from print_result import print_result
from field import field
from unique import Unique
from gen_random import gen_random
from cm_timer import cm_timer_1
import json

with open('data_light.json', encoding='utf-8') as f:
    data = json.load(f)

@print_result
def f1(arg):
    return sorted(list(Unique(field(arg, 'job-name'), ignore_case=True)), key=str.lower)

@print_result
def f2(arg):
    return list(filter(lambda x: str.startswith(str.lower(x), 'программист'), arg))

@print_result
def f3(arg):
    return list(map(lambda x: x + " с опытом Python", arg))


@print_result
def f4(arg):
    return dict(zip(arg, list(f'зарплата {val} руб.' for val in gen_random(len(arg), 1000000, 2000000))))

if __name__ == '__main__':
    with cm_timer_1():
        f4(f3(f2(f1(data))))