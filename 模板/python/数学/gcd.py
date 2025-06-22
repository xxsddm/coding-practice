def gcd(a, b):  # 辗转相除法
    while b:
        a, b = b, a % b
    return a