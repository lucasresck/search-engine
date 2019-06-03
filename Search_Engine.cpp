#include <iostream>
#include <vector>      //to vector
#include <fstream>    //to files
#include <string>     //to strings
#include <locale>    //tolower

using namespace sts;

class SuffixTree(){
	
	public:

		SuffixTree() {}	 //constructor
		                 // here, we have to load (or deserialize) the SuffixTree
		                 
		void search(string key, vector *&p){
			//do the iniciatlization of a search. Separetes different words			
		}
	
	private:
		
		void search(string key, vector *&p){         //search pattern in the text, for now, *p is a pointer to a vector
		
			Node* pAux2 = pRoot;	
		    //string word_aux = "english historian";
		    //word_aux = " " + word_aux + " ";
		    int p_value = (int)word_aux[0];
		    string word_test = pAux2 -> alphabet[p_value];
		
		    while (word_aux.length() > 0) {
		    	if (word_test == ""){
		    		cout << "nÃ£o encontrei";
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

string get_title(fstream fs, int id){
	//get the title from some page
	if (fs.is_open()){
		for (int i = 0;i < id; i++){
			get_line(fs,line);
		}
		get_line(fs,this_line);
		return this_line;
	}
	return "";
}

void open_page(int id){
	fstream page;
	page.open("SeparetedPages/"+stoi(id)+".txt", fstream::in);
	get_line(page,line);
	cout << line << endl;
	while (line != "") {
		get_line(page,line);
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
		if accented_a.find(query[i]) query.replace(i,1,"a")
		else if accented_e.find(query[i]) query.replace(i,1,"e")
		else if accented_i.find(query[i]) query.replace(i,1,"i")
		else if accented_o.find(query[i]) query.replace(i,1,"o")
		else if accented_u.find(query[i]) query.replace(i,1,"u")
		else if accented_c.find(query[i]) query.replace(i,1,"c")
		else if accented_n.find(query[i]) query.replace(i,1,"n")	
	}
	
	return;
}

int main(){
	
	SuffixTree tree()
	
	fstream titles;
	titles.open("titles.txt", fstream::in);
	
	string answer;
	int aux = 1;
	
	while(true){
		cout << "Enter your query: " << endl;
		getline(cin, query);
		clean_query(query)
		
		vector *p;                                                   //I want p to be a vector of integers. Could it be??
		
		float time = clock();
		SuffixTree.search(query, p);
		time = (clock() - time)/CLOCKS_PER_SEC;
		
		cout << "\n.. About " << (*p).size() << " results" << endl;     //(*p).size() is the amount of pages
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
			cout << "[" << i+1 << "]" << get_title(titles, p[i]) << endl;
		}
	}
	
	return 0;
}
