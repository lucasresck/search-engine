#include <iostream>
#include <vector>      //to vector
#include <fstream>    //to files
#include <string>     //to strings
#include <locale>    //tolower
#include <map>

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
		}
    
    //constructor
    //here, we have to load (or deserialize) the Trie
    
    
    //search receives the query (key) and a vector that is going to store the pages with the words searched
		void search(string key, vector<int> &p){
        
            //vector with the location of the spaces in the query
            //(in case there is more than one word or in case there are extra spaces in the query)
            vector<int> space_loc;
            
            //cleans the query and fills space_loc
            clean_query(key, space_loc);
            
            //word is going to be the word searched
            string word;
            
            //counts how many words we searched
            int count = 0;
            
            //we are now going to identify the words in the query and search for it
            
            //if we have more than one word
            if (space_loc.size() > 0) {
                
                //first we search for the first word in the query
                word = key.substr(0,space_loc[1]);
                search_word(word,p);
                
                //than we go through a loop in space_loc identifyng words in the middle
                for (int i=0; i < space_loc.size()-1; i++) {
                    word = key.substr(space_loc[i-1]+1,space_loc[i]-1-space(loc[i-1]));
                    search_word(word,p)
                    count = count + 1
                }
                
                //last we search for the last word in the query
                word = key.substr(space_loc[space_loc.size()-1],query.size()-space_loc[space_loc.size()-1]);
                search_word(word,p);
                
            }
            
            //if we only have one word
            else {
                word = key.substr(0,key.length());
                search_word(word,p)
            }
            
            //identifies pages in which all of our words appear (in case there is more than one word in the query)
            
            vector<int> aux;
            
            if (count > 0) {
                std::map<int, int> countMap;
                
                for (auto & elem : p){
                    auto result = countMap.insert(std::pair<int, int>(elem, 1));
                    if (result.second == false)
                        result.first->second++;}
                
                for (auto & elem : countMap){
                    if (elem.second > count)
                        aux.push_back(elem.first);
                }
                
                p = aux;
                
            }
	
	private:
		
            void search_word(string key, vector<int> &p,  Node* pInit){
                
                Node* pAux = pInit;
                
                //identifies last node of the word in the trie
                for (int i = 0; i < key.length(); i++) {
                    pInit = pInit->pChild[int()key[i]];
                }
                
                //identifies pages in which the searched word exists and adds them to our vector p
                if (pInit->documents.size() > 0) {
                    p.insert(std::end(p), std::begin(pInit->documents), std::end(pInit->documents));
                }
            };
	
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

            void clean_query(string &query, vector<int> &space_loc;){
                locale loc;
                
                string accented_a = "באדג";
                string accented_e = "יטך";
                string accented_i = "םלמ";
                string accented_o = "ףעפץ";
                string accented_u = "שתû";
                string accented_c = "ח";
                string accented_n = "ס";
                
                for (string::size_type i = 0; i<query.length(); i++){
                    
                    string ch = query[i];
                    if (ch == " "){
                        space_loc.push_back(i);
                    }
                    
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
		//clean_query(query);
		
		vector<int> p;                                                   //I want p to be a vector of integers. Could it be??
		
		float time = clock();
		trie.search(query, p);
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
