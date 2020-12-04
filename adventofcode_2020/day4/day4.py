
import re
import sys
 
def check_validity(passport):  
    for key in passport.keys():
        if not key in ["byr", "iyr", "cid", "eyr", "ecl", "pid", "hgt", "hcl"]:
            return False

    if (len(passport) == 8) or (len(passport) == 7 and not "cid" in passport):
        if (int(passport['byr']) < 1920) or (int(passport['byr']) > 2002): 
            return False
        if (int(passport['iyr']) < 2010) or (int(passport['iyr']) > 2020): 
            return False
        if (int(passport['eyr']) < 2020) or (int(passport['eyr']) > 2030): 
            return False
        if (re.match('^#[a-f0-9]{6}$', passport['hcl']) == None): 
            return False
        if ( not passport['ecl'] in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"] ): 
            return False
        if (re.match('^[0-9]{9}$', passport['pid']) == None): 
            return False
        
        m = re.search('^([0-9]*)(in|cm)$', passport['hgt'])
        if m == None: 
            return False
        else: 
            if m.group(2) == "in":
                in_inch = int(m.group(1))
                if (in_inch < 59) or (in_inch > 76):
                    return False
            if m.group(2) == "cm":
                in_cm = int(m.group(1))
                if (in_cm < 150) or (in_cm > 193):
                    return False

        return True
    else: 
        return False

input_file = open(sys.argv[1], 'r') 
valid = 0 
passport = {}

for line in input_file.read().splitlines(): 
    if len(line) != 0: 
        substrings = line.split() #with parameters, splits by whitespaces
        for sub in substrings: 
            subsub = sub.split(":")
            passport[subsub[0]] = subsub[1]
    else: 
        if check_validity(passport):
            valid += 1; 
        passport = {}

if check_validity(passport):
    valid += 1; 

print("Number of valids are: {}".format(valid))