import argparse
import re
import unittest


def parse_line(line: str) -> tuple[int, int, int]:
    match = re.match(r"(\w+) can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.", line)
    if match:
        return (match.group(1), int(match.group(2)), int(match.group(3)), int(match.group(4)))
    else:
        raise ValueError(f"Could not parse line: {line}")
    
class TestParse(unittest.TestCase):

    def test_successful_parse(self):
        self.assertEqual(parse_line("Dancer can fly 27 km/s for 5 seconds, but then must rest for 132 seconds."), ("Dancer", 27, 5, 132))
        self.assertEqual(parse_line("Cupid can fly 22 km/s for 2 seconds, but then must rest for 41 seconds."), ("Cupid", 22, 2, 41))

    def test_unsuccesful_parse(self):
        with self.assertRaises(ValueError):
            parse_line("Dancer can fly 27 km/s for 5 seconds, but then must rest for 132")

def calculate_one_distance(speed: int, duration: int, rest: int, time: int) -> int:
    cycle_time = duration + rest
    cycles = time // cycle_time
    remaining_time = time % cycle_time
    return cycles * speed * duration + min(remaining_time, duration) * speed

class TestDistance(unittest.TestCase):
    def test_calculate_one_distance(self):
        self.assertEqual(calculate_one_distance(14, 10, 127, 1000), 1120)
        self.assertEqual(calculate_one_distance(16, 11, 162, 1000), 1056)

def solve_part1(reindeers: dict[str, tuple[int, int, int]], time: int) -> int:
    return max([calculate_one_distance(*reindeer, time) for reindeer in reindeers.values()])

def solve_part2(reindeers: dict[str, tuple[int, int, int]], time: int) -> int:
    points = {name: 0 for name in reindeers.keys()}
    for i in range(1, time+1):
        distances = {name: calculate_one_distance(*reindeer, i) for name, reindeer in reindeers.items()}
        max_distance = max(distances.values())
        for name, distance in distances.items():
            if distance == max_distance:
                points[name] += 1
    print(points)
    return max(points.values())

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input file")
    parser.add_argument("--part", help="part 1 or 2", default=1, type=int)
    args = parser.parse_args()

    input_file = open(args.input, "r")
    reindeers = {}
    for line in input_file:
        parsed_line = parse_line(line)
        reindeers[parsed_line[0]] = parsed_line[1:]

    if args.part == 1:
        print(solve_part1(reindeers, 2503))
    else:
        print(solve_part2(reindeers, 2503))
        pass

if __name__ == "__main__":
    main()