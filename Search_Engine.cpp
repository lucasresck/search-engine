#include <iostream>

using namespace sts;

class SuffixTree(){
	
	public:

		SuffixTree() {}	 //constructor
		// here, we have to load (or deserialize) the SuffixTree
	
	private:
		
		void search(string key, int *&p){}   //search pattern in the text
											 //for now, *p is a pointer for the first page
	
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
		query = " " + query + " ";
		
		int *p;
		
		float time = clock();
		SuffixTree.search(query, p);
		time = (clock() - time)/CLOCKS_PER_SEC;
		
		cout << "\n.. About " << "Number of results" << " results" << endl;
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
