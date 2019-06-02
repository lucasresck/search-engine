#include <iostream>

using namespace sts;

class SuffixTree(){
	
	public:

		SuffixTree() {}	 //constructor
		                 // here, we have to load (or deserialize) the SuffixTree
	
	private:
		
		void search(string key, int *&p){         //search pattern in the text, for now, *p is a pointer for the first page
		
			Node* pAux2 = pRoot;	
		    //string word_aux = "english historian";
		    //word_aux = " " + word_aux + " ";
		    int p_value = (int)word_aux[0];
		    string word_test = pAux2 -> alphabet[p_value];
		
		    while (word_aux.length() > 0) {
		    	if (word_test == ""){
		    		cout << "não encontrei";
		    		break;
		    	}
		
		    	else if (word_test == word_aux){
		    		cout<<"encontrei";
		    		break;
		    	}
		
		    	else if (word_aux == word_test.substr(0,word_aux.length())){
		    		cout<<"encontrei";
		    		break;
		    	}
		    	
		    	else if(word_test == word_aux.substr(0,word_test.length())){
		    		pAux2 = pAux2 -> pChild[p_value];
		    		p_value = (int)word_aux[word_test.length()];
		    		word_aux = word_aux.substr(word_test.length(), word_aux.length()+1);
		    		word_test = pAux2-> alphabet[p_value];
		    	}
		    }
		}  
};

string get_title(int id){
	//get the title from some page
	
}

void open_page(int id){
	//open the page 
}

int main(){
	
	SuffixTree tree()
	
	string answer;
	int aux = 1;
	
	while(true){
		cout << "Enter your query: " << endl;
		getline(cin, query);
		query += " ";
		
		int *p;                                                   //I want p to be a vector of integers. Could it be??
		
		float time = clock();
		SuffixTree.search(query, p);
		time = (clock() - time)/CLOCKS_PER_SEC;
		
		cout << "\n.. About " << len(p) << " results" << endl;     //len(p) is the amount of pages
		cout << "(" << time << "seconds)" << endl;
		
		for(int i=0; i < len(p); i++){
			if (i > 0 && i %20 == 0){
				while(true){
					cout "\nDo you want to open any result[n or result number]?" << endl;
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
						break 
					}else if (stoi(answer) < len(p)){
						open_page(p[i]);
						break
					} 
				}
			}
			if (aux == 0) break;
			cout << "[" << i+1 << "]" << get_title(p[i]) << endl;
		}
	}
	
	return 0;
}
