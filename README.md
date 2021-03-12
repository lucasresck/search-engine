# search-engine
> Search engine for English Wikipedia

We implemented a search engine in C++ to return pages from English Wikipedia. Check our [video](https://youtu.be/iaAe9gT1-Y0).

This is our final project for [Data Structures and Algorithms](https://emap.fgv.br/disciplina/graduacao/estruturas-de-dados-algoritmos), an Applied Mathematics Graduation subject at Getulio Vargas Foundation (FGV, 2019).

Group: [Alessandra Corrêa Cid](https://github.com/alessandracid), [Lucas Emanuel Resck Domingues](https://github.com/lucasresck) and [Lucas Machado Moschen](https://github.com/lucasmoschen). Professor: [Dr. Jorge Poco](https://github.com/jpocom).

## Summary

For this project, our group developed a search engine that searches for a word, or multiple words, in the English portion of the Wikipedia corpus.
In order to do that, we constructed a trie in C++ to use as our data structure.
We used Python to pre-process the corpus and then inserted it into the trie.
Our search is also done in C++.
If we have more than one word, we compare the pages that are common to all words and only return them.
If a user misspells a word when searching, our program returns suggestions for alternative results.

## Setup

- In order to run the program you should download the files on [this link](https://bit.ly/2WYQing).
  - Folder `SeparatedPages`: this folder contains the Wikipedia pages separated in different files and ordered by alphabetical order;
  - File  `titles_ordered.txt`: list of titles of Wikipedia pages in alphabetical order;
  - File `Serialization.txt`: contains the serialization of the trie composed by the Wikipedia pages;
  - Folder `CleanedPages`: this folder contains the files used to build the trie. It is not necessary to download it to run the engine, but it can be downloaded in case a user wants to change the way the pages are processed. 
- You should unzip the `SeparatedPages` folder and make sure that you have the following packages: iostream, vector, fstream, string, ctype.h, bits/stdc++.h, iomanip and chrono.
- The final step is to run the `engine.exe` file while in the same folder as the `SeparatedPages`, the `titles_ordered.txt` file and the `Serialization.txt`.

The search should run in around 0,000005 second.
After the search ends, the program returns the number of results that were found and identifies the title of each page found in the search.
The title of the 20 first results are then displayed in alphabetical order.
The user is able to open in details an specific page that was returned as a result or to see the title of 20 more pages found in the search.
