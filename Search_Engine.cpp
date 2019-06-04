#include <iostream>
#include <vector>      //to vector
#include <fstream>    //to files
#include <string>     //to strings
#include <locale>    //tolower

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
		
		Node *pRoot = new Node;

		Trie() {
			cout << "./engine" << endl;
			ifstream file ("Serialization.txt");			
			clock_t t = clock();
			deserialize(file);
			cout << "... Loading index done with ";
			t = clock() - t;
			cout << ((float)t)/CLOCKS_PER_SEC;
			cout << " s!" << endl << endl;
			file.close();
		}	 //constructor
		                 // here, we have to load (or deserialize) the Trie
		                 
		void search(string key, vector<int> &p){
			//do the iniciatlization of a search. Separetes different words			
		}
	
	private:
		
	//	void search(string key, vector<int> &p){         //search pattern in the text, for now, *p is a pointer to a vector
		
	//		Node* pAux2 = pRoot;	                    //pRoot should be told in the inicialization
	//	    //string word_aux = "english historian";
	//	    string word_aux = key;
	//	    int p_value = (int)word_aux[0];
	//	    string word_test = pAux2->pChild[p_value];
	//	
	//	    while (word_aux.length() > 0) {
	//	    	if (word_test == ""){
	//	    		cout << "nÃ£o encontrei";
	//	    		break;
	//	    	}
	//	
	//	    	else if (word_test == word_aux){
	//	    		cout<<"encontrei";
	//	    		break;
	//	    	}
	//	
	//	    	else if (word_aux == word_test.substr(0,word_aux.length())){
	//	    		cout<<"encontrei";
	//	    		break;
	//	    	}
	//	    	
	//	    	else if(word_test == word_aux.substr(0,word_test.length())){
	//	    		pAux2 = pAux2 -> pChild[p_value];
	//	    		p_value = (int)word_aux[word_test.length()];
	//	    		word_aux = word_aux.substr(word_test.length(), word_aux.length()+1);
	//	    		word_test = pAux2->pChild[p_value];
	//	    	}
	//	    }
	//	} 
	
	void deserialize(ifstream& file) {
		Node* pNode = pRoot;
		char letter;
		string doc;
		string number;
		vector<Node*> pNodes;
		while (file.get(letter)) {
			if (letter == '[') {
				doc = "";
				file.get(letter);				
				while (letter != ']') {
					if (letter == ' ') {
						pNode->documents.push_back(stoi(doc));
						doc = "";
					}
					else
						doc = doc + letter;
					file.get(letter);					
				}
			}
			else if (letter == '-') {
				pNode = pNodes.back();
				pNodes.pop_back();	
			}
			else {
				number = "";
				while (letter != ' ') {
					number = number + letter;
					file.get(letter);
				}
				pNodes.push_back(pNode);
				pNode->pChild[stoi(number)] = new Node;
				pNode = pNode->pChild[stoi(number)];
			}
		}
	} 
};

string get_title(fstream &fs, int id){
	//get the title from some page
	string line;
	string this_line;
	if (fs.is_open()){
		for (int i = 0;i < id; i++){
			getline(fs, line);
		}
		getline(fs,this_line);
		return this_line;
	}
	return "";
}

void open_page(int id){
	fstream page;
	string line;
	string str_id = to_string(id);
	page.open("SeparetedPages/"+ str_id +".txt", fstream::in);
	getline(page,line);
	cout << line << endl;
	while (line != "") {
		getline(page,line);
		cout << line << endl;		
	}
}

void clean_query(string &query){
	locale loc;
	
	string accented_a = "áàãâ";
	string accented_e = "éèê";
	string accented_i = "íìî";
	string accented_o = "óòôõ";
	string accented_u = "ùúû";
	string accented_c = "ç";
	string accented_n = "ñ";
	
	for (string::size_type i = 0; i<query.length(); i++){
		tolower(query[i], loc);
		if (accented_a.find(query[i])) query.replace(i,1,"a");
		else if (accented_e.find(query[i])) query.replace(i,1,"e");
		else if (accented_i.find(query[i])) query.replace(i,1,"i");
		else if (accented_o.find(query[i])) query.replace(i,1,"o");
		else if (accented_u.find(query[i])) query.replace(i,1,"u");
		else if (accented_c.find(query[i])) query.replace(i,1,"c");
		else if (accented_n.find(query[i])) query.replace(i,1,"n");	
	}
	
	return;
}

int main(){
	
	Trie trie;	
	
	fstream titles;
	titles.open("title_ordered.txt", fstream::in);
	
	string answer;
	int aux = 1;
	
	while(true){
		cout << "Enter your query: ";
		string query;
		getline(cin, query);
		clean_query(query);
		
		vector<int> p;                                                   //I want p to be a vector of integers. Could it be??
		
		float time = clock();
		//trie.search(query, p);                                     
		time = (clock() - time)/CLOCKS_PER_SEC;
		
		if (p.size() == 0 || p.size() == 1) cout << "\n.. About " << p.size() << " result (" << time << " second)" << endl << endl;
		else cout << "\n.. About " << p.size() << " results (" << time << " seconds)" << endl << endl;
		
		for(int i=0; i < p.size(); i++){
			if (i > 0 && i %20 == 0){
				while(true){
					cout << "\nDo you want to open any result[n or result number]?" << endl;
					cin >> answer;
					if (answer == "n"){
						while(true){				
							cout << "Show more 20 results[y or n]" << endl;
							cin >> answer;
							if (answer == "n"){
								aux = 0;
								break;
							}else if (answer == "y"){
								aux = 1;
								break;
							}
						}
						break;
					}else if (stoi(answer) < p.size()){
						open_page(p[i]);
						break;
					} 
				}
			}
			if (aux == 0) break;
			string title = get_title(titles,p[i]);
			cout << "[" << i+1 << "]" << get_title(titles, p[i]) << endl;
		}
	}
	
	return 0;
}
