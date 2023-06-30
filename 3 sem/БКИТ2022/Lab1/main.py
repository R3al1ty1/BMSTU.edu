import math

def isNumber(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

def getCoef(output):
    exText = 'Попробуйте ввести заново: '
    print(output)
    flag = True
    curr = input()
    if isNumber(curr):
        return float(curr)
    else:
        flag = False
        while not flag:
            print(exText)
            curr = input()
            if isNumber(curr):
                return float(curr)

def getRoots(a,b,c):
    roots = []
    flag = True
    D = pow(b,2) - 4*a*c
    if a == 0:
        flag = False
        return 'не является биквадратным'
    if flag:
        if D == 0.0:
            if (-b/(2*a)) >= 0:
                roots.append(math.sqrt((-b/(2*a))))
                roots.append(-math.sqrt((-b/(2 * a))))
        elif D > 0:
            firstRoot = (-b - math.sqrt(D))/(2*a)
            secondRoot = (-b + math.sqrt(D))/(2*a)
            if secondRoot >= 0:
                roots.append(math.sqrt(secondRoot))
                roots.append(-math.sqrt(secondRoot))
            if firstRoot >= 0:
                roots.append(-math.sqrt(firstRoot))
                roots.append(math.sqrt(firstRoot))
        if len(roots) == 0:
            return 'нет корней'
        else:
            return roots

def main():
    a = getCoef('Введите коэффициент А:')
    b = getCoef('Введите коэффициент B:')
    c = getCoef('Введите коэффициент C:')
    roots = getRoots(a, b, c)
    print(roots)

if __name__ == '__main__':
    main()