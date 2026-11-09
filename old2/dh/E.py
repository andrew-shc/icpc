from math import floor,ceil
def main():
    tf = float(input())
    tr = float(input())
    input()
    outputs = [0]
    #i = 0
    while True:
        try:
            #i++
            num = input()
            if num == "":
                raise EOFError
            num = float(num)
            dec = num%1
            if num > 0 and num <= 1:
                outputs.append(1)
                continue
            if dec<tf:
                outputs.append(floor(num))
            elif dec > tr:
                outputs.append(ceil(num))
            else:
                if outputs[-1] < num:
                    outputs.append(floor(num))
                else:
                    outputs.append(ceil(num))
            #print(outputs)
        except EOFError:
            for s in outputs:
                print(s)
            break
if __name__ == "__main__":
    main()
