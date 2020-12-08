import hashlib 

myinput = "yzbqklnj"
i = 0

while True: 
    result = hashlib.md5((myinput + str(i)).encode() ).hexdigest()
    if result[0:6] == "000000": 
        break
    i += 1

print (i)