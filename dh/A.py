from collections import namedtuple

def equalsIgnoreCase(s1, s2):
    return s1.lower() == s2.lower()
def key_helper(rec) -> str:
    return str.lower(rec[0])

def run():
    Record = namedtuple('Record', ['ea', 'name'])	

    inside_records = []
    outside_records = []

    while True:
        line = input()
        if line == '':
            break
        tokens = line.split()
        # print("DEBUG", tokens)
        inside_records.append(Record(tokens[2], tokens[1] + ' ' + tokens[0]))

    while True:
        try:
            line = input()
        except EOFError:
            break
        if line == '':
            break
        tokens = line.split()
        # print("DEBUG 2nd", tokens)
        outside_records.append(Record(tokens[2], tokens[1] + ' ' + tokens[0]))

    inside_mismatches = []
    for in_rec in inside_records:
        name_is_in_outside = False
        ea_is_in_outside = False
        for out_rec in outside_records:
            if equalsIgnoreCase(in_rec.name, out_rec.name):
                name_is_in_outside = True
            if equalsIgnoreCase(in_rec.ea, out_rec.ea):
                ea_is_in_outside = True
        if not (name_is_in_outside or  ea_is_in_outside):
            inside_mismatches.append(in_rec)

    outside_mismatches = []
    for out_rec in outside_records:
        name_is_inside = False
        ea_is_inside = False
        for in_rec in inside_records:
            if equalsIgnoreCase(in_rec.name, out_rec.name):
                name_is_inside = True
            if equalsIgnoreCase(in_rec.ea, out_rec.ea):
                ea_is_inside = True
        if not (name_is_inside or ea_is_inside):
            outside_mismatches.append(out_rec)
	
    inside_mismatches.sort(key=key_helper)
    outside_mismatches.sort(key=key_helper)
	
    for rec in inside_mismatches:
        print('I', rec.ea, rec.name)
    for rec in outside_mismatches:
        print('O', rec.ea, rec.name)
	
    if len(inside_mismatches) == len(outside_mismatches) == 0:
        print('No mismatches.')


if __name__ == '__main__':
    run()








