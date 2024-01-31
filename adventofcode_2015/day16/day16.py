import argparse
import unittest

"""
children: 3
cats: 7
samoyeds: 2
pomeranians: 3
akitas: 0
vizslas: 0
goldfish: 5
trees: 3
cars: 2
perfumes: 1
"""

class Aunt:

    def __init__(self, number: int, children: int, cats: int, samoyeds: int, pomeranians: int, akitas: int, vizslas: int, goldfish: int, trees: int, cars: int, perfumes: int):
        self.number = number
        self.children = children
        self.cats = cats
        self.samoyeds = samoyeds
        self.pomeranians = pomeranians
        self.akitas = akitas
        self.vizslas = vizslas
        self.goldfish = goldfish
        self.trees = trees
        self.cars = cars
        self.perfumes = perfumes

    def __str__(self):
        return f"Aunt {self.number}: children {self.children}, cats {self.cats}, samoyeds {self.samoyeds}, pomeranians {self.pomeranians}, akitas {self.akitas}, vizslas {self.vizslas}, goldfish {self.goldfish}, trees {self.trees}, cars {self.cars}, perfumes {self.perfumes}"
    
    def __repr__(self):
        return str(self)
    
    def __eq__(self, other):
        return (
            self.number == other.number and 
            self.children == other.children and 
            self.cats == other.cats and 
            self.samoyeds == other.samoyeds and 
            self.pomeranians == other.pomeranians and 
            self.akitas == other.akitas and 
            self.vizslas == other.vizslas and 
            self.goldfish == other.goldfish and 
            self.trees == other.trees and 
            self.cars == other.cars and 
            self.perfumes == other.perfumes
        )
    
    def matches(self, other: Aunt) -> bool:
        return (
            (self.children == None or self.children == other.children) and 
            (self.cats == None or self.cats < other.cats) and 
            (self.samoyeds == None or self.samoyeds == other.samoyeds) and 
            (self.pomeranians == None or self.pomeranians > other.pomeranians) and 
            (self.akitas == None or self.akitas == other.akitas) and 
            (self.vizslas == None or self.vizslas == other.vizslas) and 
            (self.goldfish == None or self.goldfish > other.goldfish) and 
            (self.trees == None or self.trees < other.trees) and 
            (self.cars == None or self.cars == other.cars) and 
            (self.perfumes == None or self.perfumes == other.perfumes)
        )

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input")
    parser.add_argument("--part", type=int, default=1)
    args = parser.parse_args()

    input_file = open(args.input, "r")
    for line in input_file.readlines():
        print(line)

if __name__ == "__main__":
    main()
    