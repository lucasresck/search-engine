#include <iostream>
#include <iomanip>
#include<stdio.h> 
#define MARKER -1  

using namespace std;

template<typename U>
struct Node{
    U data;
    Node<U> *pChild[2];

    Node(U x):data(x){
    	pChild[0] = pChild[1] = NULL;
	}
};

template<typename T>
class LinkedList{
private:
    Node<T> *pRoot;
    
	void serialize(Node<T> *root, FILE *fp) 
	{ 
	    // Base case 
	    if (root == NULL){
			fprintf(fp, "%d", MARKER);
			fprintf(fp, " ");
		return;
		}
		
		fprintf(fp, "%d", root->data);
		fprintf(fp, " ");
		serialize(root->pChild[0], fp);
		serialize(root->pChild[1], fp); 
	}

public:
LinkedList<T>(): pRoot(NULL){}

    bool find(T x, Node<T> **&pNode) {
	        pNode = &pRoot;
        while(*pNode) {
            if ((*pNode)->data==x) return true;
            pNode = &((*pNode)->pChild[(*pNode)->data < x]);
        }
        return 0;
    }

    void insert(T x) {
        Node<T> **pNode;
        if ((find(x, pNode))) return;
        Node<T> *newNode = new Node<T>(x);
        *pNode = newNode;
    }
    
    void print() {
    	print(pRoot);
		cout << endl;
	}

    void print(Node<T> *p, int indent = 0) {
        if(p) {
            print(p->pChild[1], indent+8);
            cout << setw(indent) << ' ';
            cout<< p->data << " ";
			cout << endl;
            print(p->pChild[0], indent+8);
        }
    }
    
    void serialize(FILE *fp){
    	serialize(pRoot,fp);
	}
	
	//void deSerialize(Node<U> *&root, FILE *fp) 
	//{ 
	//    int val; 
	//    if ( !fscanf(fp, "%d ", &val) || val == MARKER) 
//	       return; 
//	  
//	    root = (val); 
//	    deSerialize(root->left, fp); 
//	    deSerialize(root->right, fp); 
//	} 
};

int main() {
	
    LinkedList<int> list;
    list.insert(6);
	list.insert(25);
	list.insert(5);
	list.insert(4);
	FILE *fp = fopen("tree.txt", "w"); 
    list.serialize(fp); 
    fclose(fp);

    return 0;
}
