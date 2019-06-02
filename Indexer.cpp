#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>

using namespace std;

struct Node {
	vector<int> documents;
	//string alphabet[128];
	Node* pChild[128];
	Node() {
		for (int i = 0; i < 128; i++) {
			//alphabet[i] = "";
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
};

int main() {
	time_t init = time(NULL);
	time_t now;
	Trie trie;
	for (int doc = 0; doc < 1359870; doc++) {
		if (doc % 100 == 0) {
			now = time(NULL);
			cout << doc << endl;
			cout << now - init;
			cout << " s = ";
			cout << (now - init) / 60;
			cout << " min" << endl << endl;
		}
		string page;
		ifstream file ("Cleaned_Texts/" + to_string(doc) + ".txt");
		if (file.is_open()) {
			if (file.good()) {
				getline(file, page);
				trie.add_page(page, doc);
			}
		}
	}
	return 0;
}
