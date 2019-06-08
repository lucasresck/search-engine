#include <iostream>
#include <vector>      //to vector
#include <fstream>    //to files
#include <string>     //to strings
#include <locale>    //tolower

using namespace std;

struct Node {
	int doc_size;
	int* docs;//vector<int> docs;
	Node* pChild[128];
	Node() {
		for (int i = 0; i < 128; i++) {
			pChild[i] = nullptr;
		}
		doc_size = 0;
	}
	void array_size(int size) {
		docs = new int[size];
		doc_size = size;
	}
};

class Trie {
	
public:
	
	Node *pRoot = new Node;

	Trie() {
		cout << "Indexing ..." << endl;
		ifstream serialization ("Serialization.txt");
		clock_t t = clock();
		deserialize(serialization);
		cout << "\r" << "... Loading index done with " << flush;
		t = clock() - t;
		cout << ((float)t)/CLOCKS_PER_SEC;
		cout << " s!" << endl << endl;
		serialization.close();
	}
	
	void search(string key, vector<int> &p){
		vector<int> space_loc;
		clean_query(key, space_loc);
		
		string word;
		
		int count = 0;
		
		if (space_loc.size() > 0) {
			
			//first we search for the first word in the query
			word = key.substr(0,space_loc[0]);
			search_word(word,p);
			
			//than we go through a loop in space_loc identifyng words in the middle
			for (int i=0; i < space_loc.size()-1; i++) {
				word = key.substr(space_loc[i]+1, space_loc[i+1]-1-space_loc[i]);
				vector<int> p_aux;
				search_word(word,p_aux);
				p = intersection(p, p_aux);
				count = count + 1;
			}
			
			//last we search for the last word in the query
			word = key.substr(space_loc[space_loc.size()-1] + 1, key.size()-space_loc[space_loc.size()-1]);
			vector<int> p_aux;
			search_word(word,p_aux);
			p = intersection(p, p_aux);
			
		}//if we only have one word
		else {
			search_word(key,p);
			return;
		}
	}

private:
	
	void search_word(string key, vector<int> &p){
		
		Node* pInit = pRoot;
		Node* pParent;
		bool sug = true;
        
		//identifies last node of the word in the trie
		for (int i = 0; i < key.length(); i++) {
			pParent = pInit;
			pInit = pInit->pChild[(int)key[i]];
            if (pInit == nullptr){
            	cout << "HERE" << endl;
                sug = false;
                p.clear();
                break;
            }
		}
		if (sug) {
			for (int i = 0; i < pInit->doc_size; i++)
				p.push_back(*(pInit->docs + i));
		}
	}
	
//	void suggestion_naive(Node* p, int &len, Node* &chosen_one){
//		for (int i = 0; i < 128; i++){
//			if (p->pChild[i]) {
//				if ((p->pChild[i]->docs).size() > len){
//					chosen_one = p->pChild[i];
//					len = (chosen_one->docs).size();
//				}
//				suggestion(p->pChild[i], len, chosen_one);
//			}
//		}
//		return;
//	}

	void deserialize(ifstream& serialization) {
		Node* pNode = pRoot;
		char letter;
		string number = "";
		vector<Node*> pNodes;
		int loading = 0;
		int i;
		while (serialization.get(letter)) {
			if (letter == ',') {
				//pNode->docs.push_back(stoi(number));
				*(pNode->docs + i) = stoi(number);
				i++;
				number = "";
			}
			else if (letter == '.') {
				pNodes.push_back(pNode);
				pNode->pChild[stoi(number)] = new Node;
				pNode = pNode->pChild[stoi(number)];
				number = "";
			}
			else if (letter == '-') {
				pNode = pNodes.back();
				if (pNode == pRoot) {
					loading++;
					//cout << loading << endl;
					float status = (float)loading/0.41;
					cout << "\r" << status << "% completed.     " << flush;
				}
				pNodes.pop_back();
				number = "";
			}
			else if (letter == '+') {
				i = 0;
				pNode->array_size(stoi(number));
				number = "";
			}
			else number = number + letter;
		}
	} 


	void clean_query(string &query, vector<int> &space_loc){
		locale loc;
	
		string accented_a = "באדג";
		string accented_e = "יטך";
		string accented_i = "םלמ";
		string accented_o = "ףעפץ";
		string accented_u = "שתû";
		string accented_c = "ח";
		string accented_n = "ס";
		
		int length = query.length();
		
		
		for (int i = 0; i < query.length(); i++){

			if (query[i] == ' ')
				space_loc.push_back(i);
		
			tolower(query[i], loc);
			if (accented_a.find(query[i]) < length) query.replace(i,1,"a");
			else if (accented_e.find(query[i]) < length) query.replace(i,1,"e");
			else if (accented_i.find(query[i]) < length) query.replace(i,1,"i");
			else if (accented_o.find(query[i]) < length) query.replace(i,1,"o");
			else if (accented_u.find(query[i]) < length) query.replace(i,1,"u");
			else if (accented_c.find(query[i]) < length) query.replace(i,1,"c");
			else if (accented_n.find(query[i]) < length) query.replace(i,1,"n");
		}
	
		return;
	}
	
	vector<int> intersection(vector<int> v1, vector<int> v2) {
		cout << endl;
		vector<int> v;
		int j = 0;
		for (int i = 0; i < v1.size(); i++) {
			while (j < v2.size()) {
				if (v1[i] < v2[j]) break;
				else if (v1[i] == v2[j]) {
					j++;
					v.push_back(v1[i]);
					break;
				}
				else {
					j++;
				}
			} 

		}
		return v;
	}
};

string get_title(fstream &fs, int id){
	//get the title from some page
	string line;
	string this_line;
	if (fs.is_open()){
		if (fs.good()) {
			for (int i = 0;i < id; i++){
				getline(fs, line);
			}
			getline(fs,this_line);
			return this_line;
		}
	}
	return "";
}

void open_page(int id){
	fstream page;
	string line;
	string str_id = to_string(id);
	page.open("SeparetedPages/"+ str_id +".txt", fstream::in);
	cout << endl;
	while (getline(page,line)) {
		if (line == "ENDOFARTICLE.") break;
		cout << line << endl;		
	}
	page.close();
}

int compare(char c1, char c2){
	if (c1 == c2) return 0;
	return 1;
}

int* partial_med(string word, char ch, int* array){
	
	int* arr = new int[word.length()+1];
	arr[0] = array[0] + 1;
	for(int i = 1; i <= word.length(); i++){
		arr[i] = min(min(arr[i-1]+1, array[i] + 1), array[i-1] + compare(ch,word[i-1]));
	}
	return arr;
}

string suggestion(Node *p, string word, int * array, bool &aux){
	
	string s2;
	
	for (int i = 0; i < 128; i++){
		if (p->pChild[i]){
			bool good = false;
			int * arr = partial_med(word, (char)i, array);
			
			for(int j = 0; j <= word.length(); j++){
				if (arr[j] <= 1){
					good = true;
				}
				if (j == word.length() && arr[j] <= 1 && p->pChild[i]->doc_size > 0){
					aux = true;
					string s(1, (char)i);
					return s;
				}
			}
			if (good){
				s2 = suggestion(p->pChild[i], word, arr, aux);
			}
			if (aux){
				string s(1, (char)i);
				return (s + s2);
			}
		}		
	}
	return ""; 
}

vector<string> suggestions_med(Node* p, string word){
	string s;
	vector<string> v;
	
	bool aux = false;
	int* arr = new int[word.length()+1];
	
	while(true){
		for (int i = 0; i <= word.length();i++) arr[i] = i;
		s = suggestion(p, word, arr, aux);
		v.push_back(s);
		if (v.size() == 1) break;
	}
	return v;
}

int main(){
	
	Trie trie;
	
	fstream titles;
	
	string answer;
	int aux;
	string title;
	string query;

	vector<int> p;
	
	while(true){
		titles.open("titles_ordered.txt", fstream::in);
		aux = 1;
		cout << "Enter your query: ";
		cin >> query;
		
		float time = clock();
		trie.search(query, p);
		time = (clock() - time)/CLOCKS_PER_SEC;
		
		//Here, I am doing the suggestions. It's in developing processing.
		
		if (p.size() == 0){
            cout << "Your word does not exist in Wikipedia. Look at these results for a similar expression!" << endl;
			vector<string> v = suggestions_med(trie.pRoot, query);
			cout << "Choose one of these words to search: " << endl;
			for (int i = 0; i < v.size(); i++){
				cout << "[" << i+1 << "]" << v[i] << endl;
			}
			while(true){
				cout << "Digit one of these numbers: ";
			    cin >> answer;
				if (stoi(answer) == 1){
					trie.search(v[stoi(answer)-1], p);
					break;
				}
			}
		}
		
		if (p.size() == 1) cout << "\n.. About " << p.size() << " result (" << time << " second)" << endl << endl;
		else cout << "\n.. About " << p.size() << " results (" << time << " seconds)" << endl << endl;
		
		for(int i=0; i < p.size(); i++){
			
			if (i == 0) title = get_title(titles,p[i]);
			else title = get_title(titles, p[i] - p[i - 1] - 1);
			cout << "[" << i+1 << "]" << title << endl;
			if ((i > 0 && (i + 1) %20 == 0) || i == p.size() - 1){
				while(true){
					cout << "\nDo you want to open any result [n or result number]?" << endl;
					cin >> answer;
					if (answer == "n"){
						while(true){
							if (i < p.size()){				
								cout << "Show more 20 results [y or n]?" << endl;
								cin >> answer;
								if (answer == "n"){
									aux = 0;
									cout << endl;
									break;
								}else if (answer == "y"){
									aux = 1;
									break;
								}
							}
						}
						break;
					}else if (stoi(answer) < p.size()){
						aux = 0;
						open_page(p[stoi(answer) - 1]);
						break;
					} 
					else cout << "Big number. Please, try again." << endl;
				}
			}
			if (aux == 0) break;
		}
		
		p.clear();   //restart p
		titles.close();
	}
	
	return 0;
}
