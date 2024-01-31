import argparse
import unittest
import re


"""
Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3
"""

class Ingredient:
    def __init__(self, name: str, capacity: int, durability: int, flavor: int, texture: int, calories: int):
        self.name = name
        self.capacity = capacity
        self.durability = durability
        self.flavor = flavor
        self.texture = texture
        self.calories = calories

    def __str__(self):
        return f"({self.name}: capacity {self.capacity}, durability {self.durability}, flavor {self.flavor}, texture {self.texture}, calories {self.calories})"
    
    def __repr__(self):
        return str(self)
    
    def __eq__(self, other):
        return (
            self.name == other.name and 
            self.capacity == other.capacity and 
            self.durability == other.durability and 
            self.flavor == other.flavor and 
            self.texture == other.texture and 
            self.calories == other.calories
        )

def parse_line(line: str) -> tuple[str, int, int, int, int, int]:
    match = re.match("^(\w+): capacity (-?\d+), durability (-?\d+), flavor (-?\d+), texture (-?\d+), calories (-?\d+)$", line.strip())
    if match:
        return Ingredient(match.group(1), int(match.group(2)), int(match.group(3)), int(match.group(4)), int(match.group(5)), int(match.group(6)))
    else:
        raise ValueError(f"Could not parse line: {line}")
    
class TestParse(unittest.TestCase):
        def test_successful_parse(self):
            self.assertEqual(parse_line("Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8"), Ingredient("Butterscotch", -1, -2, 6, 3, 8))
            self.assertEqual(parse_line("Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3"), Ingredient("Cinnamon", 2, 3, -2, -1, 3))
    
        def test_unsuccesful_parse(self):
            with self.assertRaises(ValueError):
                parse_line("Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8, 9")

def calculate_score(ingredients: list[Ingredient], amounts: list[int]) -> int:
    capacity = 0
    durability = 0
    flavor = 0
    texture = 0
    for i in range(len(ingredients)):
        capacity += ingredients[i].capacity * amounts[i]
        durability += ingredients[i].durability * amounts[i]
        flavor += ingredients[i].flavor * amounts[i]
        texture += ingredients[i].texture * amounts[i]
    return max(capacity, 0) * max(durability, 0) * max(flavor, 0) * max(texture, 0)

def calculate_calories(ingredients: list[Ingredient], amounts: list[int]) -> int:
    calories = 0
    for i in range(len(ingredients)):
        calories += ingredients[i].calories * amounts[i]
    return calories

def calculate_score_with_calories(ingredients: list[Ingredient], amounts: list[int]) -> int:
    return (calculate_score(ingredients, amounts), calculate_calories(ingredients, amounts))

def solve_part1(ingredients: list[Ingredient]):
    ingredients_num = len(ingredients)
    max_ingridients = 100

    possible_variations = []

    if (ingredients_num == 2):
        for i in range(max_ingridients+1):
            j = max_ingridients - i
            possible_variations.append((i, j))

    elif (ingredients_num == 3):
        pass
    elif (ingredients_num == 4):
        for i in range(max_ingridients+1):
            for j in range(max_ingridients+1-i):
                for k in range(max_ingridients+1-i-j):
                    l = max_ingridients - i - j - k
                    possible_variations.append((i, j, k, l))

    return max([calculate_score(ingredients, amounts) for amounts in possible_variations])

def solve_part2(ingredients: list[Ingredient]):

    ingredients_num = len(ingredients)
    max_ingridients = 100

    possible_variations = []

    if (ingredients_num == 2):
        for i in range(max_ingridients+1):
            j = max_ingridients - i
            possible_variations.append((i, j))

    elif (ingredients_num == 3):
        pass
    elif (ingredients_num == 4):
        for i in range(max_ingridients+1):
            for j in range(max_ingridients+1-i):
                for k in range(max_ingridients+1-i-j):
                    l = max_ingridients - i - j - k
                    possible_variations.append((i, j, k, l))

    calculations = [calculate_score_with_calories(ingredients, amounts) for amounts in possible_variations]
    return max([score for score, calories in calculations if calories == 500])

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input file")
    parser.add_argument("--part", help="part 1 or 2", default=1, type=int)
    args = parser.parse_args()


    input_file = open(args.input, "r")
    ingredients = [parse_line(line) for line in input_file.readlines()]

    print(ingredients)

    if args.part == 1:
        print(solve_part1(ingredients))
    else:
        print(solve_part2(ingredients))

if __name__ == "__main__":
    main()