from contextlib import contextmanager
import time

@contextmanager
def cm_timer_1():
    start = time.time()
    yield
    print(time.time() - start)

class cm_timer_2:
    def __enter__(self):
        self.start = time.time()
    def __exit__(self, type, val, traceback):
        print(time.time() - self.start)

with cm_timer_1():
    time.sleep(5.5)
with cm_timer_2():
    time.sleep(5.5)