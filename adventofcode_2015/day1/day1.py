import argparse
import itertools
import unittest

def solve_part1(input:str) -> int:
    return sum([1 if c == "(" else -1 for c in input])

def solve_part2(input:str) -> int:
    return list(itertools.accumulate([1 if c == "(" else -1 for c in input])).index(-1) + 1


class TestCounter(unittest.TestCase):

    """
    (()) and ()() both result in floor 0.
    ((( and (()(()( both result in floor 3.
    ))((((( also results in floor 3.
    ()) and ))( both result in floor -1 (the first basement level).
    ))) and )())()) both result in floor -3.
    """
    def test_part1_solver(self):
        self.assertEqual(solve_part1("(())"), 0)
        self.assertEqual(solve_part1("()()"), 0)
        self.assertEqual(solve_part1("((("), 3)
        self.assertEqual(solve_part1("(()(()("), 3)
        self.assertEqual(solve_part1("))((((("), 3)
        self.assertEqual(solve_part1("())"), -1)
        self.assertEqual(solve_part1("))("), -1)
        self.assertEqual(solve_part1(")))"), -3)
        self.assertEqual(solve_part1(")())())"), -3)

    """
    ) causes him to enter the basement at character position 1.
    ()()) causes him to enter the basement at character position 5.
    """
    def test_part2_solver(self):
        self.assertEqual(solve_part2(")"), 1)
        self.assertEqual(solve_part2("()())"), 5)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input file")
    parser.add_argument("--part", help="part 1 or 2", default=1, type=int)
    args = parser.parse_args()
    input = open(args.input, 'r').readline().strip()

    if args.part == 1:
        print(solve_part1(input))
    else:
        print(solve_part2(input))
    pass

if __name__ == "__main__":
    main()