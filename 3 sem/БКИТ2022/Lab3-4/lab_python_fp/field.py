def field(items, *args):
    assert len(args) > 0 #аргументы должны быть
    if len(args) == 1: #длина кортежа равна 1
        for dct in items:
            curr = dct.get(args[0]) #получаем значение по ключу
            if curr is not None: #если значение не None
                yield curr #возвращаем значение
    else:
        for elem in items:
            dct = dict()
            for arg in args:
                curr = elem.get(arg)
                if curr is not None:
                    dct[arg] = curr
            if len(dct) != 0:
                yield dct

if __name__ == '__main__':
    goods = [
        {'title': 'Ковер', 'price': 3000, 'color': 'black'},
        {'title': 'Диван для отдыха', 'price': 10000, 'color': 'grey'},
        {'title': 'Стул', 'price': 1000, 'color': 'white'},
        {'title': None, 'price': None, 'color': 'red'}
    ]
    lst1 = []
    lst2 = []

    for elem in field(goods, 'title'):
        lst1.append(elem)

    for elem in field(goods, 'title', 'price','color'):
        lst2.append(elem)

    print(lst1)
    print(lst2)
