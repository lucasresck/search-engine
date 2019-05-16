#include <iostream>

using namespace std;

struct Node {
	Node* pChild[6];
	Node() {
		for (int i = 0; i < 6; i++)
			pChild[i] = nullptr;
	}
};

class SuffixTree {
private:
	
	string* get_suffixes(string word) {
		string* suffixes = new string[word.length()];
		suffixes[0] = word;
		for (int i = 1; i < word.length(); i++) {
			suffixes[i] = word;
			suffixes[i].erase(suffixes[i].begin(), suffixes[i].begin() + i);
		}
				
		return suffixes;	
	}
	
	void add(string word) {
		Node* pNode = pRoot;
		int n;
		for (int i = 0; i < word.length(); i++) {
			if (word[i] == '$')
				n = 0;
			else if (word[i] == 'a')
				n = 1;
			else if (word[i] == 'e')
				n = 2;
			else if (word[i] == 'i')
				n = 3;
			else if (word[i] == 'o')
				n = 4;
			else
				n = 5;
			if (pNode->pChild[n] != nullptr)
				pNode = pNode->pChild[n];
			else
			{
				pNode->pChild[n] = new Node;
				pNode = pNode->pChild[n];
			}
		}
	}
	
	void compress_it() {
	}
	
public:
		
	Node* pRoot = new Node;
	
	SuffixTree(string word) {
		word = word + "$";
		string* suffixes = get_suffixes(word);
		for (int i = 0; i < word.length(); i++) {
			add(*(suffixes + i));
		}
		compress_it();
	}
	
};

int main() {
	SuffixTree st("aeiioeou");
	cout << (st.pRoot)->pChild[3]->pChild[2] << endl;
	return 0;
}
