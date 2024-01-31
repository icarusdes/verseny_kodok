import argparse
import logging
import re
import sys
import unittest
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
    
    def __eq__(self, other):
        return self.length == other.length and self.type == other.type

    def __repr__(self):
        return str(self)

class TestRecord(unittest.TestCase):
    def test_str(self):
        self.assertEqual(str(Record(3, RecordType.GOODSPRINGS)), "...")
        self.assertEqual(str(Record(3, RecordType.UNKNOWN)), "???")
        self.assertEqual(str(Record(3, RecordType.BADSPRINGS)), "###")

    def test_eq(self):
        self.assertEqual(Record(3, RecordType.GOODSPRINGS), Record(3, RecordType.GOODSPRINGS))
        self.assertEqual(Record(2, RecordType.BADSPRINGS), Record(2, RecordType.BADSPRINGS))
        self.assertEqual(Record(1, RecordType.UNKNOWN), Record(1, RecordType.UNKNOWN))
        self.assertNotEqual(Record(3, RecordType.GOODSPRINGS), Record(3, RecordType.UNKNOWN))
        self.assertNotEqual(Record(3, RecordType.GOODSPRINGS), Record(4, RecordType.GOODSPRINGS))
        self.assertNotEqual(Record(3, RecordType.GOODSPRINGS), Record(4, RecordType.UNKNOWN))

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

class Test(unittest.TestCase):
    def test_generate_options(self):
        self.assertEqual(generate_options(0), [])
        self.assertEqual(generate_options(1), ['.', '#'])
        self.assertEqual(generate_options(2), ['..', '.#', '#.', '##'])
        self.assertEqual(generate_options(3), ['...', '..#', '.#.', '.##', '#..', '#.#', '##.', '###'])

    def test_from_string(self):
        self.assertEqual(CurrentState("...").processed_row, [Record(3, RecordType.GOODSPRINGS)])
        self.assertEqual(CurrentState("???").processed_row, [Record(3, RecordType.UNKNOWN)])
        self.assertEqual(CurrentState("###").processed_row, [Record(3, RecordType.BADSPRINGS)])
        self.assertEqual(CurrentState("...???").processed_row, [Record(3, RecordType.GOODSPRINGS), Record(3, RecordType.UNKNOWN)])
        self.assertEqual(CurrentState("...???###").processed_row, [Record(3, RecordType.GOODSPRINGS), Record(3, RecordType.UNKNOWN), Record(3, RecordType.BADSPRINGS)])


def remove_good_springs(side: Side, processed_row: CurrentState, defected_springs_specification):
    print("Removing good springs from", side, processed_row, defected_springs_specification)
    index = 0 if side == Side.LEFT else -1
    next_i = 1 if side == Side.LEFT else -2

    while len(processed_row) and processed_row[index].type != RecordType.UNKNOWN:

        if processed_row[index].type == RecordType.GOODSPRINGS:
            processed_row.pop(index)
            continue

        # this is definitely a bad spring, since it can not be good and it is not unknown (because of the while loop)
        if len(defected_springs_specification) and processed_row[index].length == defected_springs_specification[index]:

            # be the rules we can be sure, bad springs are followed by at least one good one
            if len(processed_row) > 1 and processed_row[next_i].type == RecordType.UNKNOWN:
                if side == Side.LEFT:
                    to_replace = CurrentState("." + "?" * (processed_row[next_i].length - 1))
                else: 
                    to_replace = CurrentState("?" * (processed_row[next_i].length - 1) + "." )    
                debug_print("To replace:", to_replace)
                processed_row.replace(next_i, to_replace)
                debug_print("After replace:", processed_row)
            processed_row.pop(index)
            defected_springs_specification.pop(index)
            continue
        break

def solve(processed_row: CurrentState, defected_springs_specification, indent = 0):
    debug_print(" " * indent, "Solving:", processed_row, defected_springs_specification)
    remove_good_springs(Side.LEFT, processed_row, defected_springs_specification)
    debug_print(" " * indent, "After removing good springs:", processed_row, defected_springs_specification)
    remove_good_springs(Side.RIGHT, processed_row, defected_springs_specification)
    debug_print(" " * indent, "After removing good springs:", processed_row, defected_springs_specification)
    if processed_row.sum() == 0 and len(defected_springs_specification) == 0:
        return 1
    return None

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
            solutions = solve(CurrentState(mistery), defected_springs_specification)
            if solutions:
                print("Number of solutions for part 1:", solutions)
                print(mistery)
                counter += solutions
            else: 
                print("No solution found")
                print(mistery)
                print(defected_springs_specification)    
        else:
            new_mistery = "?".join([mistery for i in range(5)])
            defected_springs_specification = defected_springs_specification * 5
            print(new_mistery)
            print(defected_springs_specification)

        print("-" * 80)

    print(counter)
    return

if __name__ == "__main__":
    main()