import math

# Shenhage-Strassen Algorithm

def karatsuba(a: str, b: str):
    if len(a) == 1 or len(b) == 1:
        return str(int(a) * int(b))
    else:
        n = max(len(a), len(b))
        m = n // 2

        a, b = a.zfill(n), b.zfill(n)
        a0, a1 = a[:m], a[m:]
        b0, b1 = b[:m], b[m:]

        z0 = karatsuba(a0, b0)
        z1 = karatsuba(a1, b1)
        z2 = karatsuba(str(int(a0) + int(a1)), str(int(b0) + int(b1)))

        return str(int(z0) + int(z1) - int(z2)) + '0' * m + '0' * m 