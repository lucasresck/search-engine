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

h = open("title_ordered.txt")
string = h.readline()
titles_ord = dict()
i = 0
while string != "":
    string = string[0:-1]
    titles_ord[string] = i
    i += 1
    string = h.readline()
h.close()

#Titles = list()
#number_file = 0
g = open("titles.txt","w")
h = open("titles.txt","w")
t0 = time.time()
for i in files_names:
    print(time.time() - t0)
    f = open("englishTexts/" + i)
    string = f.readline()
    while string != "":
        if "<doc id" in string:
            g.close()   #closes the previous file
            h.close()

            #getting title
            string = get_title(string)
            #Titles.append(string)
            
            title_id = titles_ord[string]            
            name = "CleanedPages/"+ str(title_id) + ".txt"
            name2 = "SeparetedPages/"+str(title_id) + ".txt"

            g = open(name, "w")
            h = open(name2, "w")
            g.close()
            h.close()
            g = open(name,"a")
            h = open(name2, "a")
            #number_file += 1

        ##separeting    

        h.write(string)
        h.write("\n")

        ##cleaning

        string = string.lower()
        for symbol in symbols_out:
            string = string.replace(symbol," ")
        for symbol in subst_accented.keys():
            string = string.replace(symbol, subst_accented[symbol])
        if "endofarticle" not in string:
            g.write(string)
            g.write(" ")
        string = f.readline()
    f.close()
g.close()
h.close()

#f = open("titles.txt","a")
#for t in Titles:
#    f.write(t)
#    f.write("\n")