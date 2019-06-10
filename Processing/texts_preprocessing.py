# coding=utf-8

import os
import time

files_names = os.listdir("englishTexts")

symbols = {'8', '¼', 'ß', 'f', 'C', '<', 'e', '\\', ',', 'P', '©', '+', 'û', 'Ê', 'î', '6', '¢', 'T', 'F', 'O', '{', 'N', '=', 'Ü', '(', 'g', '¬', 'ë', '´', ':', 'ä', 'Á', 'Ø', 's', 'ê', '&', 'R', '¦', 'S', 'A', '¡', 'h', 'à', 'E', '¹', 'þ', 'w', '^', ';', 'â', '»', '`', 'Û', 'ç', 'X', '±', 'Ö', 'n', '%', 'Ò', '7', '_', '$', 'Ô', 'õ', 'è', '-', 'o', '÷', 'Æ', 'H', 'ñ', 'Ó', 'i', 'º', 'ø', 'ÿ', 'Ð', 'U', 'p', '?', 'å', 'á', 'ú', 'Í', 'Ý', 'W', 'ã', 'j', '/', '·', '\xad', 'Ú', 'Q', '¿', 'Z', 'Â', 'ü', 'ì', '3', '.', 'ù', '¨', '"', 'µ', 'M', 'Y', '#', ')', 'ð', '4', 'í', '×', 'z', 'r', '¤', ' ', 'Ñ', '²', '|', 'Þ', '2', '[', 'Ï', "'", '9', 'ö', 'È', 'Ì', 'm', 'x', '}', 'a', 'Õ', 'Ë', 'Å', '\n', 'ó', '¯', 'D', 'ô', 'Ä', 'd', 'ò', '!', 'Ù', '«', 'l', 'v', '£', '\t', 't', 'u', '~', '¶', 'c', 'I', 'b', '¸', 'K', 'é', 'V', '°', '³', 'Î', 'k', '0', 'y', '§', 'B', '>', 'q', '¥', 'G', '*', 'À', '½', '¾', '1', '\xa0', 'æ', '®', 'É', '5', 'ï', 'Ã', '@', 'Ç', 'J', 'ª', ']', 'L', 'ý'}
upper = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
lower = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}
numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}
used_symbols = {'%','&','-','@',"'"}
accented = {"ô", "Ã", "é", "ã", "â", "É", "Ù", "ñ", "Î", "Ñ", "Ú", "ù", "ü","í", "ì", "î", "Ó", "À", "Á", "È", "à", "Ê", "Ò", "Û", "ç", "Â", "Í","á","ú", "õ", "ó","Õ","ê","Ç","è","Ì","û","Ô"}
wanted_symbols = upper.union(lower)
wanted_symbols = wanted_symbols.union(numbers)
wanted_symbols = wanted_symbols.union(used_symbols)
wanted_symbols = wanted_symbols.union(accented)
symbols_out = symbols - wanted_symbols
accented_list = list(accented)
accented_list = sorted(accented_list)
subst_accented = {"ç": "c", 'à':"a", 'á':"a", 'â':"a", 'ã':"a", 'è':"e", 'é':"e", 'ê':"e", 'ì':"i", 'í':"i", 'î':"i", "ñ":"n", 'ó':"o", 'ô':"o", 'õ':"o", 'ù':"u", 'ú':"u", 'û':"u", 'ü':"u"}

def get_title(string):                  ##function to get title from title lines
    begin = string.find("title")
    end = string.find("nonfiltered")
    if begin == -1 or end == -1: return None
    title = string[begin+7:end - 2]
    return title

h = open("titles_ordered.txt")
string = h.readline()
titles_ord = dict()
i = 0
while string != "":
    string = string[0:-1]
    try:
        titles_ord[string].append(i)
    except:
        titles_ord[string] = [i]
    i += 1
    string = h.readline()
h.close()

h = open("titles_ordered.txt")
t0 = time.time()
j = 0
for i in files_names:
    print(i)
    print(time.time() - t0)
    f = open("englishTexts/" + i)
    string = f.readline()
    while string != "":
        if "<doc id" in string:
            j+=1
            if j%100==0: print(time.time() - t0)
            h.close()             #closes the previous file

            #getting title
            string = get_title(string)
            #Titles.append(string)
            
            title_id = (titles_ord[string])[0]
            titles_ord[string].pop(0)
            
            name = "SeparetedPages/"+str(title_id) + ".txt"

            h = open(name, "w")

        ##separating
        h.write(string)
        h.write("\n")
        string = f.readline()
        
    f.close()
h.close()

pages_ids = os.listdir("SeparetedPages")
print("Now, cleaning")

name = 0
g = open("CleanedPages" + str(name) + ".txt","w")

for i in range(len(pages_ids)):
    if i%1000 == 0: print(time.time() - t0)
    if i%10000 == 0 and i > 0: 
        g.close()
        name+=1
        g = open("CleanedPages"+str(name)+".txt","w")
    h = open("SeparetedPages/"+str(i)+".txt")
    string = h.readline()
    while string != "":  
        ##cleaning
        string = string.lower()
        for symbol in symbols_out:
            string = string.replace(symbol," ")
        for symbol in subst_accented.keys():
            string = string.replace(symbol, subst_accented[symbol])
        g.write(string)
        g.write(" ")
        string = h.readline()
    g.write("\n")
    h.close()
g.close()
