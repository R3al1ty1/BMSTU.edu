import unittest
from tasks import task_1, task_2, task_3

task_1_result = [('Zenbook', 'Intel Core i5', 'Intel'), ('Zenbook', 'Intel Core i7', 'Intel'), ('MacBook', 'Intel Core i9', 'Intel'), ('Latitude', 'Intel Core i3', 'Intel')]
task_2_result = [('Zenbook', '2014.50'), ('MacBook', '2015.75'), ('Latitude', '2017.14'), ('Inspiron', '2017.17'), ('ThinkPad', '2017.50'), ('ProBook', '2017.50')]
task_3_result = ('Zenbook', ['Intel Core i5', 'Intel Core i9', 'AMD Ryzen 9'])

class TasksTestCase(unittest.TestCase):
    def test_task_1(self):
        self.assertEqual(task_1_result, task_1())
    def test_task_2(self):
        self.assertEqual(task_2_result, task_2())
    def test_task_3(self):
        self.assertEqual(task_3_result, task_3())