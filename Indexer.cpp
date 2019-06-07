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
	
	void serialize(ofstream& serialization) {
		Node* pNode = pRoot;
		for (int child = 0; child < 128; child++) {
			cout << "Processing words starting with " << (char)child << endl;
			if (pNode->pChild[child] != nullptr) {
				serialization << child;
				serialize(pNode->pChild[child], serialization);
				delete pNode->pChild[child];
				serialization << "-";
			}
			else cout << "Nothing" << endl;
		}				
	}
	
	void serialize(Node* pNode, ofstream& serialization) {
		int documents_size = pNode->documents.size();
		serialization << '.';
		if (documents_size > 0) {
			for (int doc = 0; doc < documents_size; doc++) {
				serialization << pNode->documents[doc];
				serialization << ",";
			}
		}
		for (int child = 0; child < 128; child++) {
			if (pNode->pChild[child] != nullptr) {
				serialization << child;
				serialize(pNode->pChild[child], serialization);
				delete pNode->pChild[child];
				serialization << "-";
			}
		}				
	}
};

int main() {
	clock_t t0, t;
	t0 = clock();
	Trie trie;
	int number_page = 0;
	for (int doc = 0; doc < 1; doc++) {
		if (doc % 5 == 0) {
			t = clock() - t0;
			cout << "Document: " + to_string(doc) << endl;
			cout << ((float)t)/CLOCKS_PER_SEC;
			cout << " s = ";
			cout << ((float)t)/CLOCKS_PER_SEC/60;
			cout << " min" << endl << endl;
		}
		string page;
		ifstream file ("CleanedPages/" + to_string(doc) + ".txt");
		if (file.is_open()) {
			if (file.good()) {
				while(getline(file, page)) {
					trie.add_page(page, number_page);
					number_page++;
				}
			}
		}
		file.close();
	}

	ofstream serialization ("Serialization.txt");
	trie.serialize(serialization);
	serialization.close();
	
	return 0;
}
