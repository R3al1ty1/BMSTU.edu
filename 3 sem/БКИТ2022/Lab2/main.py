from BKIT2022 import Rectangle
from BKIT2022 import Circle
from BKIT2022 import Square
import requests


def main():
    r = Rectangle("синего", 3, 2)
    c = Circle("зеленого", 5)
    s = Square("красного", 5)
    print(r)
    print(c)
    print(s)

if __name__ == "__main__":
    print(requests.get('https://www.youtube.com'))
    main()