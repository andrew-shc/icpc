def run():
    n, t = map(int, input().split())

    ways = {0: 1, 1: 1}

    def find_ways(n):
        if n in ways:
            return ways[n]

        count = 0
        if n % 2 == 0:
            k = 0
        else:
            k = 1

        for i in range(k, t + 1, 2):
            if (n - i) // 2 not in ways:
                ways[(n - i) // 2] = find_ways((n - i) // 2)
            count += ways[(n - i) // 2]
            count %= 998_244_353
        return count
    
    print(find_ways(n))

if __name__ == '__main__':
    run()
