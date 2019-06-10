# Search-engine
Implementation of a search engine for Data Structures and Algorithms class.

Group: Alessandra Corrêa Cid, Lucas Emanuel Resck Domingues and Lucas Machado Moschen.

Professor: Jorge Poco

For this project our group developed a search engine that searches for a word, or multiple words, in the English portion of the Wikipedia corpus. In order to do that, we constructed a trie in C++ to use as our data structure. We used Python to pre-process the corpus and then inserted it into the trie. Our search is also done in C++. If we have more than one word, we compare the pages that are common to all words and only return them. 
