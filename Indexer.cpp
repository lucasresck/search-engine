#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>

using namespace std;

struct Node {
	vector<int> documents;
	Node* pChild[128];
	Node() {
		for (int i = 0; i < 128; i++) {
			pChild[i] = nullptr;
		}
	}
};

class Trie {
public:
	
	Node* pRoot = new Node;
	
	Trie() {
	}
	
	void add_page(string page, int doc) {
		int init, end;
		int letter = 0;
		while (letter < page.length()) {
			while (page[letter] == ' ' && letter < page.length()) letter++;
			init = letter;
			while (page[letter] != ' ' && letter < page.length()) letter++;
			end = letter - 1;
			if (init <= end) add_word(page.substr(init, end - init + 1), pRoot, doc);
		}
	}
	
	void add_word(string word, Node* pInit, int doc) {
		if (word == "") {
			if (pInit->documents.size() == 0)
				pInit->documents.push_back(doc);
			else if (pInit->documents[pInit->documents.size() - 1] != doc)
					pInit->documents.push_back(doc);
			return;
		}
		if (pInit->pChild[(int)word[0]] == nullptr)
			pInit->pChild[(int)word[0]] = new Node;
		add_word(word.substr(1, word.length() - 1), pInit->pChild[(int)word[0]], doc);
	}
	
	void serialize(Node* pNode, ofstream& serialization) {
		serialization << "[";
		for (int doc = 0; doc < pNode->documents.size(); doc++) {
			serialization << to_string(pNode->documents[doc]);
			serialization << " ";
		}
		serialization << "]";
		for (int child = 0; child < 128; child++) {
			if (pNode->pChild[child] != nullptr) {
				serialization << to_string(child);
				serialization << " ";
				serialize(pNode->pChild[child], serialization);
				serialization << "-";
			}
		}				
	}
};

int main() {
	clock_t t;
	t = clock();
	Trie trie;
	float expect;
	for (int doc = 0; doc < 30000; doc++) {
		if (doc % 250 == 0) {
			t = clock() - t;
			cout << "Document: " + to_string(doc) << endl;
			cout << ((float)t)/CLOCKS_PER_SEC;
			cout << " s = ";
			cout << ((float)t)/CLOCKS_PER_SEC/60;
			cout << " min" << endl;
			if (doc != 0) {
				expect = 1359870 / doc * ((float)t)/CLOCKS_PER_SEC - ((float)t)/CLOCKS_PER_SEC;
				cout << "Expected time: " + to_string(expect/60) + " min = " + to_string(expect/3600) + " h" << endl << endl;
			}
			else cout << endl;
		}
		string page;
		ifstream file ("CleanedAux/" + to_string(doc) + ".txt");
		if (file.is_open()) {
			if (file.good()) {
				getline(file, page);
				trie.add_page(page, doc);
			}
		}
	}

	ofstream serialization ("Serialization.txt");	
	trie.serialize(trie.pRoot, serialization);
	serialization.close();
	
	return 0;
}
