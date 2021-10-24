import re
import string

items = []

def GetFile():
    f = open("CS210_Project_Three_Input_File.txt", "r")
    with f as a_file:
        for line in a_file:
            stripped_line = line.strip()
            items.append(stripped_line)
    f.close()

def ListAll():
    GetFile()
    i = 0        
    while i < len(items):
        count = 0
        for item in items:
            if item == items[i]: 
                count = count + 1
                tempItem = item
        print(items[i], count)
        i += 1
        while tempItem in items: items.remove(tempItem) #removes the item after printing and counting it

def GetOneItem(itemName):
    GetFile()
    number = items.count(itemName)
    print("\n" + itemName + ": " + str(number))
           
def CreateHisto():
    f = open("frequency.dat", "w")
    GetFile()
    i = 0        
    while i < len(items):
        count = 0
        for item in items:
            if item == items[i]: 
                count = count + 1
                tempItem = item
        f.write("{}: {}\n".format(items[i], count))
        i += 1
        while tempItem in items: items.remove(tempItem) #removes the item after printing and counting it


                
    # for 1 = 0; i < items.len(); i++
    # for each item in items
    # if items[i] == item
    # count + 1
    # print (items[1]: count
    # loop through all items in my list
    # for each item look for matching ones within the list. 
    # if there is a matching one increment the count 
    # leave the inside loop and print the final count and name
    # reset the count variable and move on to next item in the loop.