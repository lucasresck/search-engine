# coding=utf-8

import os

files_names = os.listdir("Texts")                           #list the files in the dir. Put the texts in the folder Texts. 
                                                            #Remember to take off all the not text files.
							                                #Remember to create a folder in this folder called "Cleaned_texts". 
symbols = {'8', '¼', 'ß', 'f', 'C', '<', 'e', '\\', ',', 'P', '©', '+', 'û', 'Ê', 'î', '6', '¢', 'T', 'F', 'O', '{', 'N', '=', 'Ü', '(', 'g', '¬', 'ë', '´', ':', 'ä', 'Á', 'Ø', 's', 'ê', '&', 'R', '¦', 'S', 'A', '¡', 'h', 'à', 'E', '¹', 'þ', 'w', '^', ';', 'â', '»', '`', 'Û', 'ç', 'X', '±', 'Ö', 'n', '%', 'Ò', '7', '_', '$', 'Ô', 'õ', 'è', '-', 'o', '÷', 'Æ', 'H', 'ñ', 'Ó', 'i', 'º', 'ø', 'ÿ', 'Ð', 'U', 'p', '?', 'å', 'á', 'ú', 'Í', 'Ý', 'W', 'ã', 'j', '/', '·', '\xad', 'Ú', 'Q', '¿', 'Z', 'Â', 'ü', 'ì', '3', '.', 'ù', '¨', '"', 'µ', 'M', 'Y', '#', ')', 'ð', '4', 'í', '×', 'z', 'r', '¤', ' ', 'Ñ', '²', '|', 'Þ', '2', '[', 'Ï', "'", '9', 'ö', 'È', 'Ì', 'm', 'x', '}', 'a', 'Õ', 'Ë', 'Å', '\n', 'ó', '¯', 'D', 'ô', 'Ä', 'd', 'ò', '!', 'Ù', '«', 'l', 'v', '£', '\t', 't', 'u', '~', '¶', 'c', 'I', 'b', '¸', 'K', 'é', 'V', '°', '³', 'Î', 'k', '0', 'y', '§', 'B', '>', 'q', '¥', 'G', '*', 'À', '½', '¾', '1', '\xa0', 'æ', '®', 'É', '5', 'ï', 'Ã', '@', 'Ç', 'J', 'ª', ']', 'L', 'ý'}

wanted_symbols = {'2', 'X', 'C', 'k', 'g', '9', 'c', 'U', '4', 'Ç', '0', 'R', 'û', 'K', 'z', 'Z', 'Ò', 'p', 'Í', 'j', 'Ó', 'N', 'Ã', 'ç', 't', 'ù', 'x', 'ô', 'Ù', 'd', 'q', 'B', 'J', 'm', 'Ê', 'ã', 'e', '8', '%', 'Y', '-', 'I', 'u', 'Ô', 'T', 'h', 'n', '7', 'y', 'r', '&', 'F', 'P', 'Â', 'ú', 'ì', 'Ú', 'ü', 'D', 'ê', 's', 'E', 'O', 'Q', 'l', 'S', 'Ñ', 'L', '6', 'V', 'Õ', 'õ', 'À', 'è', 'ñ', '5', 'i', 'H', '1', 'Ì', 'È', "'", 'É', 'Î', 'í', 'Û', 'á', 'b', 'W', 'v', '3', 'o', 'M', 'â', 'î', 'w', 'f', 'G', 'a', 'é', 'Á', 'ó', 'à', '@', 'A'}

symbols_out = symbols - wanted_symbols

subst_accented = {"ç": "c", 'à':"a", 'á':"a", 'â':"a", 'ã':"a", 'è':"e", 'é':"e", 'ê':"e", 'ì':"i", 'í':"i", 'î':"i", "ñ":"n", 'ó':"o", 'ô':"o", 'õ':"o", 'ù':"u", 'ú':"u", 'û':"u", 'ü':"u"}    #dict to change the letters. 

number_file = 0
g = open("teste.txt","w")
for i in files_names:
    f = open("Texts/"+i)
    string = f.readline()
    while string != "":
        if "<doc id" in string:
            g.close()
            name = "Cleaned_Texts/"+str(number_file) + ".txt"
            g = open(name, "w")
            g.close()
            g = open(name,"a")
            number_file += 1
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