import math

def get_roots(a, b, c):
    result = []
    D = b * b - 4 * a * c
    print(D)
    if D == 0.0:
        root = -b / (2.0 * a)
        if root > 0:
            result.append(math.sqrt(root))
            result.append(-math.sqrt(root))
        elif root == 0:
            result.append(0)
    elif D > 0.0:
        sqD = math.sqrt(D)
        root1 = (-b + sqD) / (2.0 * a)
        root2 = (-b - sqD) / (2.0 * a)
        if root1 > 0:
            result.append(math.sqrt(root1))
            result.append(-math.sqrt(root1))
        elif root1 == 0:
            result.append(root1)
        if root2 > 0:
            result.append(math.sqrt(root2))
            result.append(-math.sqrt(root2))
        elif root2 == 0:
            result.append(math.fabs(root2))
    result = sorted(result)
    return result
