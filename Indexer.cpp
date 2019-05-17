#include <iostream>

using namespace std;

struct Node {
	string alphabet[128];
	Node* pChild[128];
	Node() {
		for (int i = 0; i < 128; i++) {
			alphabet[i] = "";
			pChild[i] = nullptr;
		}
	}
};

class SuffixTree {
private:
	
	void add(string word, Node* pInit) {
		Node* pNode = pInit;
		int i = (int)word[0];
		if (pNode->alphabet[i] == "")
			pNode->alphabet[i] = word;
		else if (word == pNode->alphabet[i]) //Nothing to do
			return;
		else if (pNode->alphabet[i] == word.substr(0, (pNode->alphabet[i]).length())) {	//If our word constains the edge (beggining)
			if (pNode->pChild[i] == nullptr)
				pNode->pChild[i] = new Node;
			add(word.substr((pNode->alphabet[i]).length(), (word.length() - (pNode->alphabet[i]).length())), pNode->pChild[i]);
			return;
		}
		else { //So, the first letters of the edge and the word are equal, but they are different and word doesn't constains the edge. So, some letter is diferrent between them.
			int letter = 0;
			for (int j = 0; j < word.length() && j < (pNode->alphabet[i]).length(); j++) {
				if (word[j] == (pNode->alphabet[i])[j])
					letter = j;
			}
			Node* pNew = new Node;
			Node* pAux = pNode->pChild[i];
			pNode->pChild[i] = pNew;
			string alphabetAux = pNode->alphabet[i];
			pNode->alphabet[i] = alphabetAux.substr(0, letter + 1);
			string alphabetAux2 = alphabetAux.substr(letter + 1, alphabetAux.length() - (letter + 1));
			
			int k = (int)alphabetAux2[0];			
			pNew->alphabet[k] = alphabetAux2;
			pNew->pChild[k] = pAux;
			
			add(word.substr(letter + 1, word.length() - (letter + 1)), pNew);
			return;
		}
	}
	
	//string* get_suffixes(string word) {
	//	string* suffixes = new string[word.length()];
	//	suffixes[0] = word;
	//	for (int i = 1; i < word.length(); i++) {
	//		suffixes[i] = word;
	//		suffixes[i].erase(suffixes[i].begin(), suffixes[i].begin() + i);
	//	}
	//			
	//	return suffixes;	
	//}
	
public:
		
	Node* pRoot = new Node;
	
	SuffixTree(string word) {
		word = word + "$";
		//string* suffixes = get_suffixes(word);
		//for (int i = 0; i < word.length(); i++) {
		//	add(*(suffixes + i), pRoot);
		//}
		
		string suffixes = word;                                  
		add(suffixes, pRoot);											//add the entire word
		for (int i = 1; i < word.length();i++){ 
			suffixes.erase(suffixes.begin(), suffixes.begin()+1);       //each iteration takes off the first letter
			add(suffixes, pRoot);
		}
	}
	
};

int main() {
	return 0;
}
