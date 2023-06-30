import random

def gen_random(cnt, frst, last):
    for i in range(cnt):
        number = random.randrange(frst, last)
        yield number

def main():
    data = []
    for elem in gen_random(0, 120, 300):
        data.append(elem)
    print(data)

if __name__ == "__main__":
    main()