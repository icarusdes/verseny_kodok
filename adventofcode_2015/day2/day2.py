import argparse
import unittest

class TestWrapping(unittest.TestCase):
    def test_parse_one_line(self):
        self.assertEqual(parse_one_line("2x3x4"), [2,3,4])
        self.assertEqual(parse_one_line("1x1x10"), [1,1,10])

    """
    Fortunately, every present is a box (a perfect right rectangular prism), which makes 
    calculating the required wrapping paper for each gift a little easier: find the surface 
    area of the box, which is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra 
    paper for each present: the area of the smallest side.

    For example:

    A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping 
    paper plus 6 square feet of slack, for a total of 58 square feet.
    A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping 
    paper plus 1 square foot of slack, for a total of 43 square feet.
    """
    def test_part_one_solver(self):
        self.assertEqual(solve_part1([2,3,4]), 58)
        self.assertEqual(solve_part1([1,1,10]), 43)

    """
    The elves are also running low on ribbon. Ribbon is all the same width, so they only have to worry about the length they need to order, which they would again like to be exact.

    The ribbon required to wrap a present is the shortest distance around its sides, or the smallest perimeter of any one face. Each present also requires a bow made out of ribbon as well; the feet of ribbon required for the perfect bow is equal to the cubic feet of volume of the present. Don't ask how they tie the bow, though; they'll never tell.

    For example:
    A present with dimensions 2x3x4 requires 2+2+3+3 = 10 feet of ribbon to wrap the present
    plus 2*3*4 = 24 feet of ribbon for the bow, for a total of 34 feet.
    A present with dimensions 1x1x10 requires 1+1+1+1 = 4 feet of ribbon to wrap the present
    plus 1*1*10 = 10 feet of ribbon for the bow, for a total of 14 feet.
    """
    def test_part_two_solver(self):
        self.assertEqual(solve_part2([2,3,4]), 34)
        self.assertEqual(solve_part2([1,1,10]), 14)

def parse_one_line(line: str) -> list[int]:
    return [int(v) for v in line.strip().split("x")]
    
def solve_part1(dimensions: list[int]) -> int:
    l, w, h = dimensions
    sides = [l*w, w*h, h*l]
    return sum(side *2 for side in sides) + min(sides)

def solve_part2(dimensions: list[int]) -> int: 
    l, w, h = dimensions
    perimetes = [ 2*l + 2*w, 2*h + 2*w, 2*l + 2*h]
    return min(perimetes) + l*w*h

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input file")
    parser.add_argument("--part", help="part 1 or 2", default=1, type=int)
    args = parser.parse_args()

    input_file = open(args.input, "r")
    dimensions = [parse_one_line(line) for line in input_file.read().splitlines()]

    if args.part == 1:
        print (sum(solve_part1(dim) for dim in dimensions))
    else:
        print (sum(solve_part2(dim) for dim in dimensions))
    pass

if __name__ == "__main__":
    main()