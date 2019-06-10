#include <iostream>
#include <vector>      //to vector
#include <fstream>    //to files
#include <string>     //to strings
#include <ctype.h>    //tolower
#include <bits/stdc++.h>
#include <iomanip>
#include <chrono>

using namespace std;

struct Node {
	int doc_size;
	int* docs;      //vector<int> docs;
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
		ifstream serialization ("Serialization2.txt");
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
	
		int accented_a[4] = {-58,-96,-123,-125};
		int accented_e[4] = {-118,-120,-126,0};
		int accented_i[4] = {-95,-115,-116,0};
		int accented_o[4] = {-28,-94,-107,-109};
		int accented_u[4] = {-93,-103,-106,0};
		int accented_c[4] = {-12,0,0,0};
		int accented_n[4] = {-92,0,0,0};
		
		transform(query.begin(), query.end(), query.begin(), ::tolower);
		
		for (int i = 0; i < query.length(); i++){
	
			if (query[i] == ' ') space_loc.push_back(i);
			
			if ((int)query[i] < 0){
				for (int k = 0; k < 4; k++){
					if ((int)query[i] == accented_a[k]) query.replace(i,1,"a");
					else if ((int)query[i] == accented_e[k]) query.replace(i,1,"e");
					else if ((int)query[i] == accented_i[k]) query.replace(i,1,"i");
					else if ((int)query[i] == accented_o[k]) query.replace(i,1,"o");
					else if ((int)query[i] == accented_u[k]) query.replace(i,1,"u");
					else if ((int)query[i] == accented_c[k]) query.replace(i,1,"c");
					else if ((int)query[i] == accented_n[k]) query.replace(i,1,"n");
				}	
			}
	
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
	string file = to_string(id/10000);
	page.open("SeparatedPages/" + file +".txt", fstream::in);
	
	int i = 0;
	while(i < id){
		getline(page,line);
		if (line == "$$$$$$$$$$"){
			i ++;
		}
	}
	
	cout << endl;
	while (getline(page,line)) {
		if (line == "ENDOFARTICLE.") break;
		cout << line << endl;		
	}
	page.close();
}

int* partial_med(string word, char ch, int* array){
	
	int* arr = new int[word.length()+1];
	arr[0] = array[0] + 1;
	for(int i = 1; i <= word.length(); i++){
		arr[i] = min(min(arr[i-1]+1, array[i] + 1), array[i-1] + (int)(ch!=word[i-1]));
	}
	return arr;
}

void suggestion(Node *p, string word, int * array, vector<string> &v, vector<int> &is_good, int maxCost, vector<int> &size){
	
	for (int i = 0; i < 128; i++){
		
		if (p->pChild[i]){
			bool good = false;
			int * arr = partial_med(word, (char)i, array);
			
			for(int j = 0; j <= word.length(); j++){
				if (arr[j] <= maxCost){
					good = true;
					break;
				}
			}
			
			if (arr[word.length()] <= maxCost && p->pChild[i]->doc_size > 0){
				is_good.push_back(v.size());
				string s(1, (char)i);
				v.push_back(s);
				size.push_back(p->pChild[i]->doc_size);
				good = false;
			}
			
			if (good){
				vector<int> new_one;
				suggestion(p->pChild[i], word, arr, v, new_one, maxCost, size);
				string s(1, (char)i);
				for(int j = 0; j < new_one.size(); j++) {
					v[new_one[j]] =  s + v[new_one[j]];
					is_good.push_back(new_one[j]);
				}
				
			}
			if (v.size() >= 5) return;
		}		
	}
	return; 
}

void sorting(vector<string> &s, vector<int> v){
	vector<string> new_sort;
	for(int j = 0; j < v.size() - 1; j++){
		for (int k = j+1; k < v.size(); k ++){
			if (v[j] >= v[k]) continue;
			else {
				int value = v[j];
				v[j] = v[k];
				v[k] = value;
				string str = s[j];
				s[j] = s[k];
				s[k] = str;
			}
		}
	}
}

void clean_query(string &query, vector<int> &space_loc){

	int accented_a[4] = {-58,-96,-123,-125};
	int accented_e[4] = {-118,-120,-126,0};
	int accented_i[4] = {-95,-115,-116,0};
	int accented_o[4] = {-28,-94,-107,-109};
	int accented_u[4] = {-93,-103,-106,0};
	int accented_c[4] = {-12,0,0,0};
	int accented_n[4] = {-92,0,0,0};
	
	transform(query.begin(), query.end(), query.begin(), ::tolower);
	
	for (int i = 0; i < query.length(); i++){

		if (query[i] == ' '){
			space_loc.push_back(i);	
		}
		
		if ((int)query[i] < 0){
			for (int k = 0; k < 4; k++){
				if ((int)query[i] == accented_a[k]) query.replace(i,1,"a");
				else if ((int)query[i] == accented_e[k]) query.replace(i,1,"e");
				else if ((int)query[i] == accented_i[k]) query.replace(i,1,"i");
				else if ((int)query[i] == accented_o[k]) query.replace(i,1,"o");
				else if ((int)query[i] == accented_u[k]) query.replace(i,1,"u");
				else if ((int)query[i] == accented_c[k]) query.replace(i,1,"c");
				else if ((int)query[i] == accented_n[k]) query.replace(i,1,"n");
			}	
		}

	}
	return;
}

vector<string> suggestions_med(Node* p, string word){
	
	vector<string> v;
	vector<int> number_found;
	vector<int> size;
	
	int maxCost = 1;
	
	int* arr = new int[word.length()+1];
	
	for (int i = 0; i <= word.length();i++) arr[i] = i;
	suggestion(p, word, arr, v, number_found, maxCost, size);
	if (v.size() < 5)  suggestion(p, word, arr, v, number_found, 2, size);
	sorting(v, size);
	return v;
}

bool isNumber(string s){
	for (int i = 0; i < s.length(); i++){
		if (isdigit(s[i])) continue;
		else return false;
	}
	return true;
}

void execute(Trie trie){
	
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
		getline(cin, query);
		
		auto start = chrono::steady_clock::now();
		trie.search(query, p);
		auto end = chrono::steady_clock::now();
		auto diff = end - start;
		
		//Here, I am doing the suggestions.
		
		vector<string> v;
		
		if (p.size() == 0){
			vector<int> p_unique;
			vector<int> space;
            cout << "Your input does not exist in Wikipedia." << endl;
            clean_query(query, space);
            if (space.size() > 0) {
            	trie.search(query.substr(0,space[0]),p_unique);
            	if (p_unique.size() == 0){
        			if (query.substr(0,space[0]) != " ") {
        				v = suggestions_med(trie.pRoot, query.substr(0,space[0]));
        				cout << "This word in not in the text. " ; 
						cout << "Look at the suggestions for    " << query.substr(0,space[0]) << ":" << endl;
					}	
				}
            	else {
	            	for (int k = 0; k < space.size();k++){
	            		p_unique.clear();
	            		trie.search(query.substr(space[k]+1,space[k+1]-1-space[k]), p_unique);
	            		if (p_unique.size() == 0){
	            			if (query.substr(space[k]+1,space[k+1]-1-space[k]) != " "){
		            			v = suggestions_med(trie.pRoot, query.substr(space[k]+1,space[k+1]-1-space[k]));
								cout << "This word in not in the text: " << query.substr(space[k]+1,space[k+1]-1-space[k]);
								cout << " Look at the suggestions: " << endl;
								break; 	
							}
						}
					} 
					if (p_unique.size() != 0){
						cout << "Every input word is in the texts, but they do not appear together :/ . Click enter to continue.";
					}  		
				}
			}
			
			else {
				v = suggestions_med(trie.pRoot, query);
				cout << "Look at these suggestions: " << endl;
			}
			for (int i = 0; i < v.size(); i++){
				cout << "[" << i+1 << "]" << v[i] << endl;
			}
			while(true){
				if (v.size() == 0) break;
				cout << "Digit one of these numbers or n (if none pleases you): ";
			    cin >> answer;
			    if (answer == "n") break;
				else{
					if (isNumber(answer)){
						if (stoi(answer) <= 5){
							trie.search(v[stoi(answer)-1], p);
							break;						
						} else cout << "Big number! Please, try again!" << endl;
					} 
				}
			}
		}
		
		if (p.size() == 1) {
			cout << "\n.. About " << p.size() << " result (" ;
			cout << fixed << showpoint << setprecision(10) << chrono::duration <double> (diff).count();
			cout << " second)" << endl << endl;	
		}
		else if (p.size() > 1){
			cout << "\n.. About " << p.size() << " results (";
			cout << fixed << showpoint << setprecision(10) << chrono::duration <double> (diff).count();
			cout << " second)" << endl << endl;
		} 
		
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
							if (i < p.size() - 1){				
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
						cout << "The results finished here :)"<< endl << endl << endl;
						break;
					}else {
						if (isNumber(answer)){
							if (stoi(answer) < p.size()){
								aux = 0;
								open_page(p[stoi(answer) - 1]);
								break;
							} 
							else cout << "Big number. Please, try again." << endl;								
						}
					}
				}
			}
			if (aux == 0) break;
		}
		p.clear();   //restart p
		titles.close();
		cin.ignore();
	}	
}

int main(){
	
	Trie trie;
	
	execute(trie);
	
	return 0;
}
