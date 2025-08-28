def check(x):
    #checks if x has the digits 0-9 appear exactly once
    return len(x) == 10 and all(str(digit) in x for digit in range(10))

def findPrimes():
    #finds all primes less than sqrt(9876543210)
    primes = []
    limit = int(9876543210**0.5) + 1
    sieve = [1] * (limit + 1)
    for i in range(2, limit + 1):
        if sieve[i] == 1:
            primes.append(i)
            for j in range(i * i, limit + 1, i):
                sieve[j] = 0
    return primes

def main():
    primes = findPrimes()
    cnt = 0
    for p in primes:
        a = p * p
        if a > 9876543210:
            break
        for q in primes:
            b = q * q * q
            if a + b > 9876543210:
                break
            if check(str(a + b)):
                cnt += 1
    print(cnt)

if __name__ == "__main__":
    main()
