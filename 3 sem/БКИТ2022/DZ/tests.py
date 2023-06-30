import unittest
from fibonacci import fib
from time import time

class fibonacci(unittest.TestCase):
    def test_fib5(self):
        a = [i for i in fib(5)]
        expected = [0, 1, 1, 2, 3]
        self.assertEqual(a, expected)

    def test_fib15(self):
        a = [i for i in fib(15)]
        expected = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377]
        self.assertEqual(a, expected)

    def test_fib0(self):
        a = [i for i in fib(0)]
        expected = []
        self.assertEqual(a, expected)

    def test_fib_time1(self):
        start_time = time()
        a = fib(100000)
        end_time = time() - start_time
        self.assertLess(end_time, 0.5)

    def test_fib_time2(self):
        start_time = time()
        a = [i for i in fib(100000)]
        end_time = time() - start_time
        self.assertLess(end_time, 0.5)

if __name__ == '__main__':
    unittest.main()