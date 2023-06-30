def print_result(function):
    def wrapper(*args, **kwargs):
        finRes = function(*args, **kwargs) #вызываем функцию
        print(function.__name__) #выводим имя функции
        if type(finRes) == list:
            for i in finRes:
                print(i)
        if type(finRes) == dict:
            for key, value in finRes.items():
                print(key, ' = ', value)
        else:
            print(finRes)
        return finRes
    return wrapper


@print_result
def test_1():
    return 1

@print_result
def test_2():
    return 'iu5'

@print_result
def test_3():
    return {'a': 1, 'b': 2}

@print_result
def test_4():
    return [1, 2]

if __name__ == '__main__':
    test_1()
    test_2()
    test_3()
    test_4()