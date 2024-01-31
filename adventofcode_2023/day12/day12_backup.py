import argparse
import logging
import re
import sys
from enum import Enum
from copy import deepcopy

def debug_print(*args, **kwargs):
    print(*args, **kwargs, file=sys.stdout, flush=True)

class RecordType(Enum):
    UNKNOWN = 0
    BADSPRINGS = 1
    GOODSPRINGS = 2

class Record:
    def __init__(self, length, type):
        self.length = length
        self.type = type

    def __str__(self):
        match self.type:
            case RecordType.UNKNOWN:
                return "?" * self.length
            case RecordType.BADSPRINGS:
                return "#" * self.length
            case RecordType.GOODSPRINGS:
                return "." * self.length
    
    def __repr__(self):
        return str(self)

class CurrentState:

    def __init__(self, input: list | str):
        if isinstance(input, str):
            self.from_string(input)
        else:
            self.processed_row = input

    def __str__(self):
        rep = ""
        for row in self.processed_row:
            rep += str(row)
        return rep

    def from_string(self, input: str):
        self.processed_row = []
        current_type = None
        previous_type = None
        length = 0
        for c in input:
            match c: 
                case '.':
                    current_type = RecordType.GOODSPRINGS
                case '?':
                    current_type = RecordType.UNKNOWN
                case '#': 
                    current_type = RecordType.BADSPRINGS
            if current_type != previous_type:
                if previous_type != None:
                    self.processed_row.append(Record(length, previous_type))
                length = 1
                previous_type = current_type
            else:
                length += 1
        self.processed_row.append(Record(length, previous_type))

    def __repr__(self):
        return str(self)
    
    def __hash__(self):
        return hash(str(self))
    
    def append(self, record: Record):
        self.processed_row.append(record)

    def __len__(self):
        return len(self.processed_row)
    
    def __getitem__(self, index: int):
        return self.processed_row[index]
    
    def pop(self, index: int = -1 ):
        return self.processed_row.pop(index)
    
    def sum(self):
        return sum([x.length for x in self.processed_row])

    def replace(self, index: int, records):
        self.processed_row[index:index+1] = records.processed_row
        if index - 1 >= 0:
            if self.processed_row[index-1].type == self.processed_row[index].type:
                self.processed_row[index-1].length += self.processed_row[index].length
                self.processed_row.pop(index)
        added_len = len(records)
        if index + added_len < len(self.processed_row):
            if self.processed_row[index + added_len - 1].type == self.processed_row[index + added_len].type:
                self.processed_row[index  + added_len - 1].length += self.processed_row[index + added_len].length
                self.processed_row.pop(index + added_len)

    def copy(self):
        return CurrentState(deepcopy(self.processed_row))

class Side(Enum):
    LEFT = 1
    RIGHT = 2

def generate_options(length):
    if length == 0:
        return []
    if length == 1:
        return ['.', '#']
    prev = generate_options(length -1)
    current = ['.' + x for x in prev]
    current.extend(['#' + x for x in prev])
    return current

def remove_good_springs(side: Side, processed_row: CurrentState, defected_springs_specification):
    index = 0 if side == Side.LEFT else -1
    next = index + 1 if side == Side.LEFT else -1

    while len(processed_row) and processed_row[index].type != RecordType.UNKNOWN:

        # we shave of the good springs from the left
        if processed_row[index].type == RecordType.GOODSPRINGS:
            processed_row.pop(index)
            continue

        # this is definitely a bad spring, since it can not be good and 
        # can not be unknown
        if len(defected_springs_specification) and processed_row[index].length == defected_springs_specification[index]:

            # be the rules we can be sure, bad springs are followed by at least one good one
            if len(processed_row) > 1 and processed_row[next].type == RecordType.UNKNOWN:
                if side == Side.LEFT:
                    to_replace = CurrentState("." + "?" * (processed_row[next].length - 1))
                else: 
                    to_replace = CurrentState("?" * (processed_row[next].length - 1) + "." )    
                debug_print("To replace:", to_replace)
                processed_row.replace(next, to_replace)
                debug_print("After replace:", processed_row)
            processed_row.pop(0)
            defected_springs_specification.pop(0)
            continue
        break

def solve(processed_row: CurrentState, defected_springs_specification, indent = 0):

    debug_print(indent * "\t" + "Begining of solve:", processed_row, defected_springs_specification)

    # specification and the row in process does not match. One of the is empty and the other is not
    if len(processed_row) == 0 and defected_springs_specification:
        return 0
    if len(processed_row) != 0 and not defected_springs_specification:
        return 0

    # we have to remove the good springs from the left and right
    # just remove those, who fit the specification (and if followed by unknown, make one if them good spring ('.'))
    debug_print(indent * "\t" + "Before remove from the left: ", processed_row, defected_springs_specification)
    remove_good_springs(side=Side.LEFT, processed_row=processed_row, defected_springs_specification=defected_springs_specification)
    debug_print(indent * "\t" + "Before remove from the right: ", processed_row, defected_springs_specification)
    remove_good_springs(side=Side.RIGHT, processed_row=processed_row, defected_springs_specification=defected_springs_specification)
    debug_print(indent * "\t" + "After", processed_row, defected_springs_specification)

    # specification is empty, we are done and there were only one possible solution
    if not defected_springs_specification and len(processed_row) == 0:
        return 1
    
    # we have a single unknown record and we can fill it with bad springs and good springs between them
    # like ??? and 1,1 means we have #.# and similar cases
    
    if (sum(defected_springs_specification) + len(defected_springs_specification) - 1) > processed_row.sum():
        return 0
    
    # if (sum(defected_springs_specification) + len(defected_springs_specification) - 1) == processed_row.sum():
    #     print(indent * "\t", "We are here2:", processed_row, defected_springs_specification)
    #     return 1
    
    # this is where the interesting place starts: we have to try to fill the unknown records with bad springs and good springs
    # and try to find a solutionß by the previous logic we know that either the first record has to be unknown or bad spring
    # followed by unknowns

    debug_print(indent * "\t", "We are here1:", processed_row, defected_springs_specification)
    if processed_row[0].type == RecordType.BADSPRINGS:

        if len(defected_springs_specification) == 0:
            # specification run out but we still have bad springs
            return 0

        length = processed_row[0].length
        if (length > defected_springs_specification[0]):
            # too long badspring compared to the specification
            return 0
        
        assert processed_row[1].type == RecordType.UNKNOWN

        # just enough long bad spring for the specification would have been delt with removing the good springs from the left
        # so we have to deal with the case when the bad spring is shorter than the specification
        while (len(processed_row) > 1 and 
               processed_row[0].type == RecordType.BADSPRINGS and 
               processed_row[1].type == RecordType.UNKNOWN):
            
            # case 1: unknown is shorter than what we need
            # case 2: unknown is just long enough
            # case 3: unknown is longer than what we need

            if processed_row[1].length > defected_springs_specification[0] - length:
                length += processed_row[1].length
                processed_row.pop(1)
                # since this was an unknown record, we have to check if the next one is good or bad

                if processed_row[0].type == RecordType.BADSPRINGS:
                    pass

            processed_row[0].length += processed_row[1].length
            processed_row.pop(1)

        if processed_row[1].length == defected_springs_specification[0] - length:
            processed_row.pop(1)
            processed_row[0].length = defected_springs_specification[0]
        
        if processed_row[1].length < defected_springs_specification[0] - length:
            processed_row.pop(1)
            processed_row[0].length += length

        remove_good_springs(side=Side.LEFT, processed_row=processed_row, defected_springs_specification=defected_springs_specification)
        if len(processed_row) == 0:
            return 1
        else:
            return solve(processed_row, defected_springs_specification, indent+1)
        
    if processed_row[-1].type == RecordType.BADSPRINGS:
        length = processed_row[-1].length
        assert length < defected_springs_specification[-1]
        assert processed_row[-2].type == RecordType.UNKNOWN

        if processed_row[-2].length == defected_springs_specification[-1] - length:
            processed_row.pop(-2)
            processed_row[-1].length = defected_springs_specification[-1]
        
        remove_good_springs(side=Side.RIGHT, processed_row=processed_row, defected_springs_specification=defected_springs_specification)
        if len(processed_row) == 0:
            return 1
    
    # well the previous cases were the easy one, now we really have to start to guess the unknowns

    print (indent * "\t", "We are here2:", processed_row, defected_springs_specification)
    assert processed_row[0].type == RecordType.UNKNOWN

    partial_sum = 0

    if processed_row[0].length == 1:
        current_option = processed_row.copy()
        current_option[0].type = RecordType.BADSPRINGS
        if current_option[1].type == RecordType.BADSPRINGS:
            current_option[1].length += 1
            current_option.pop(0)
        partial_sum += solve(current_option, defected_springs_specification.copy(), indent+1)

        current_option2 = processed_row.copy()
        current_option2[0].type = RecordType.GOODSPRINGS
        if current_option2[1].type == RecordType.GOODSPRINGS:
            current_option2[1].length += 1
            current_option2.pop(0)
    
        partial_sum += solve(current_option2, defected_springs_specification.copy(), indent+1)

    if processed_row[0].length > 1:
        print(indent * "\t", "We are here:")
        options = generate_options(processed_row[0].length)
        print(indent * "\t", options)
        print(indent * "\t", processed_row, defected_springs_specification)
        for option in options:
            print(indent * "\t -", "Current option: ", option)
            new_proccessed = CurrentState(option)

            current_option = processed_row.copy()
            current_option.replace(0, new_proccessed)            
            print(indent * "\t" + " -", current_option)
            solutions = solve(current_option, defected_springs_specification.copy(), indent+1)
            if solutions > 0:
                print(indent * "\t" + " -", "Solutions:", solutions)
            # print(indent * "\t" + " -", "Solutions:", solutions)
            partial_sum += solutions

    # there wasn't a solution
    return partial_sum

def create_regex (defected_springs_specification):
    regex = "^\.*"
    for i in range(len(defected_springs_specification)):
        regex += "#{" + str(defected_springs_specification[i]) + "}"
        if i != len(defected_springs_specification) - 1:
            regex += "\.+"
    regex += "\.*$"
    return regex

def generate_options_for_regex(current_row: CurrentState):
    previous_options = ['.']
    for rec in current_row.processed_row:
        new_options = []
        if rec.type == RecordType.UNKNOWN:
            generated = generate_options(rec.length)
            for previous in previous_options:
                for new in generated:
                    new_options.append(previous + new)
        if rec.type == RecordType.BADSPRINGS:
            for previous in previous_options:
                new_options.append(previous + "#" * rec.length)
        if rec.type == RecordType.GOODSPRINGS:
            for previous in previous_options:
                new_options.append(previous + "." * rec.length)
        previous_options = new_options
    return previous_options

def solve_with_regex(current_row: CurrentState, defected_springs_specification):
    print(create_regex(defected_springs_specification))
    options = generate_options_for_regex(current_row)
    compiled = re.compile(create_regex(defected_springs_specification))
    
    matches = []
    for option in options:
        if compiled.match(option):
            matches.append(option)
    return matches

assert generate_options(0) == []
assert generate_options(1) == ['.', '#']
assert generate_options(2) == ['..', '.#', '#.', '##']

def main():

    parser = argparse.ArgumentParser(description='Solve the puzzle.')
    parser.add_argument('input', type=str,
                        help='input file')
    parser.add_argument('--part', type=int, default=1)
    args = parser.parse_args()

    with open(sys.argv[1], 'r') as f:
        lines = f.readlines()

    counter = 0
    for line in lines:
        mistery, specification = line.strip().split(" ")
        defected_springs_specification = list(map(int, specification.split(',')))

        if args.part == 1:
            solved = solve_with_regex(CurrentState(mistery), defected_springs_specification)
            counter += len(solved)
        else:
            new_mistery = "?".join([mistery for i in range(5)])
            defected_springs_specification = defected_springs_specification * 5
            print(new_mistery)
            print(defected_springs_specification)

        print("-" * 80)

    print(counter)
    return

    defected_springs_specification = list(map(int, "1,3,1,6".split(',')))
    processed_row = CurrentState("?#?#?#?#?#?#?#?")
    solutions = solve(processed_row, defected_springs_specification, indent= 0)
    print(solutions)

if __name__ == "__main__":
    main()