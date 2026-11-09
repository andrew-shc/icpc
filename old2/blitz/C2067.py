t = int(input())

for _ in range(t):
    n = "0" + input()
    ones_digit = (int(n[-1]) - 7) % 10
    best_digit = 10
    for i in range(len(n) - 2, -1, -1):
        this_digit = (7 - int(n[i])) % 10
        if int(n[i + 1 :]) - this_digit < 0:
            if n[i] == "8":
                this_digit = int(n[-1]) + 1
            else:
                this_digit += 1

        best_digit = min(best_digit, this_digit)

    print(min(best_digit, ones_digit))
