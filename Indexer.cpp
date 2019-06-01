#include <iostream>
#include <fstream>
#include <time.h>

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
public:
	
	Node* pRoot = new Node;
	
	void add_string(string word, Node* pNode) {
		int word_ant_length = word.length() - 1;
		string word_ant = word.substr(0, word_ant_length);
		char new_char = word[word.length() - 1];
		
		int i = (int)word[0];
		
		string edge = pNode->alphabet[i];
		int edge_length = edge.length();
		
		if (word_ant_length == edge_length) {
			if (pNode->pChild[i] == nullptr) {
				//Rule 1
				pNode->alphabet[i] = word;
			}
			else {
				string new_char_str;
				new_char_str = new_char;
				add_string(new_char_str, pNode->pChild[i]);
			}
		}
		else if (word_ant_length > edge_length)
			add_string(word.substr(edge_length, word_ant_length - edge_length), pNode->pChild[i]);
		else {
			char old_char = edge[word_ant_length];
			if (old_char != new_char) {
				//Rule 2
				Node* pAux = new Node;
				pAux->alphabet[(int)new_char] = new_char;
				pAux->pChild[(int)old_char] = pNode->pChild[i];
				pNode->pChild[i] = pAux;
				pAux->alphabet[(int)old_char] = edge.substr(word_ant_length, edge_length - word_ant_length);
				pNode->alphabet[i] = word_ant;
			}
			else
				return; //Rule 3	
		}
	}
	
	void add_page(string page) {
		int m = page.length();
		time_t init = time(NULL);
		time_t now;
		cout << m << endl;
		for (int phase = 1; phase <= m; phase++) {
		//cout << "Phase" + to_string(phase) << endl;
			for (int extension = 1; extension <= phase; extension++) {
				//cout << "Extension " + to_string(extension) << endl;
				add_string(page.substr(extension - 1, phase - extension + 1), pRoot);
				//cout << endl;
				now = time(NULL);
				if (now - init > 1) {
					init = now;
					cout << "Phase " << to_string(phase) << "; extension " << to_string(extension)<< endl;
				}
			}
		}
	}
	
	SuffixTree() {
		
	}
	
};

int main() {
time_t init = time(NULL);
	time_t now;
	SuffixTree st;
	for (int i = 1; i < 5; i++) {
		if (i % 1 == 0) {
			now = time(NULL);
			cout << i << endl;
			cout << now - init;
			cout << " s = ";
			cout << (now - init) / 60;
			cout << " min" << endl << endl;
		}
		string page;
		ifstream file ("Cleaned_Texts/" + to_string(i) + ".txt");
		if (file.is_open()) {
			if (file.good()) {
				getline(file, page);
				st.add_page(page);
			}
		}
	}
	return 0;
}
