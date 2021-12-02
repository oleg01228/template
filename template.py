def dec_to_base(n, base):
    a = []
    w = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    while n > 0:
        if n % base > 9:
            a.append(w[(n % base) - 10])
        else:
            a.append(str(n % base))
        n //= base
    a.reverse()
    return ''.join(a)
