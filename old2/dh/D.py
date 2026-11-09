def main():
    input_list = {}
    while True:
        line = input()
        if line == "":
            break
        for fact in (line.split(')')):
            if (fact.strip() == ""):
                continue
            #print(fact)
            fact_name, args = fact.split('(')
            fact_name = fact_name.strip()
            args_list = args.split(',')
            parsed_args = []
            for arg in args_list:
                parsed_args.append(arg.strip())
            argc = len(parsed_args)
            #print(fact_name, argc)
            if (fact_name, argc) in input_list:
                input_list[(fact_name, argc)].append(parsed_args)
            else:
                input_list[(fact_name, argc)] = [parsed_args]
    #print(input_list)
    while True:
        try:
            query = input()
            if query == "":
                break
            q_name, args = query.split('(')
            args = args.split(')')[0]
            q_name = q_name.strip()
            parsed_qargs = []
            for arg in args.split(','):
                parsed_qargs.append(arg.strip())
            #print(parsed_qargs)
            key = (q_name, len(parsed_qargs))
            #print(key)
            if key not in input_list:
                print(0)
                continue
            else:
                matches = 0
                for entry in input_list[key]:
                    variables = {}
                    match = True
                    for i, arg in enumerate(entry):
                        #print(args)
                        current = parsed_qargs[i]
                        if current == '_':
                            continue
                        elif current[0] == '_':
                            if current in variables:
                                if variables[current] == arg:
                                    continue
                                else:
                                    match = False
                                    break
                            else:
                                variables[current] = arg
                                continue
                        else:
                            if current == arg:
                                continue
                            else:
                                match = False
                                break
                    if match:
                        matches += 1
                print(matches)

        except EOFError:
            break

if __name__ == "__main__":
    main()
