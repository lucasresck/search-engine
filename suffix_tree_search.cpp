#include <iostream>

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
private:
	
	void add(string word, Node* pInit) {
		Node* pNode = pInit;
		int i = (int)word[0];
		if (pNode->alphabet[i] == "") {
			pNode->alphabet[i] = word;
		}
		else if (word == pNode->alphabet[i]) //Nothing to do
			return;
		else if (pNode->alphabet[i] == word.substr(0, (pNode->alphabet[i]).length())) {	//If our word constains the edge (beggining)
			if (pNode->pChild[i] == nullptr)
				pNode->pChild[i] = new Node;
			add(word.substr((pNode->alphabet[i]).length(), (word.length() - (pNode->alphabet[i]).length())), pNode->pChild[i]);
			return;
		}
		else { //So, the first letters of the edge and the word are equal, but they are different and the word doesn't contain the edge. So, some letter is different between them.
			int letter = 0;
			for (int j = 0; j < word.length() && j < (pNode->alphabet[i]).length() && word[j] == (pNode->alphabet[i])[j]; j++)
				letter = j;
			Node* pNew = new Node;
			Node* pAux = pNode->pChild[i];
			pNode->pChild[i] = pNew;
			string alphabetAux = pNode->alphabet[i];
			pNode->alphabet[i] = alphabetAux.substr(0, letter + 1);
			string alphabetAux2 = alphabetAux.substr(letter + 1, alphabetAux.length() - (letter + 1));
			
			int k = (int)alphabetAux2[0];			
			pNew->alphabet[k] = alphabetAux2;
			pNew->pChild[k] = pAux;
			add(word.substr(letter + 1, word.length() - (letter + 1)), pNew);
			return;
		}
	}


	
public:
		
	Node* pRoot = new Node;
	
	SuffixTree(string word) {
		word = word + "$";		
		string suffixes = word;                                  
		add(suffixes, pRoot);											//add the entire word
		for (int i = 1; i < word.length();i++){ 
			suffixes.erase(suffixes.begin(), suffixes.begin()+1);       //each iteration takes off the first letter
			add(suffixes, pRoot);
		}
	
	Node* pAux2 = pRoot;	
    string word_aux = "english historian";
    word_aux = " " + word_aux + " ";
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


int main() {
	string sg = "henry hallam (july 9, 1777 - january 21, 1859) was an  english historian the only son of john hallam, canon of windsor and dean of bristol, he was educated at eton and christ church, oxford, graduating in 1799. called to the bar, he practised for some years on the oxford circuit; but his tastes were literary, and when, on his father's death in 1812, he inherited a small estate in lincolnshire, he gave himself up wholly to academic study. he had become connected with the brilliant band of authors and politicians who led the whig party, a connection to which he owed his appointment to the well-paid and easy post of commissioner of stamps; but took no part in politics himself.  he was, however, an active supporter of many popular movements--particularly of that which ended in the abolition of the slave trade; and he was sincerely attached to the political principles of the whigs. hallams earliest literary work was undertaken in connexion with the great organ of the whig party, the edinburgh review, where his review of scotts dryden attracted attention. his first great work, the view of the state of europe during the middle ages, was produced in 1818, and was followed nine years later by the constitutional history of england. in 1838-1839 appeared the introduction to the literature of europe in the 15th, 16th and 17th centuries.  these are the three works on which hallam's fame rests. they took a place in english literature which was not seriously challenged until the 20th century. a volume of supplemental notes to his middle ages was published in 1848; these facts and dates represent nearly all of hallam's career. the strongest personal interest in his life was the affliction which befell him in the loss of his children, one after another. his eldest son, arthur henry hallam--the a.h.h. of tennyson's in memoriam, and by the testimony of his contemporaries a man of the most brilliant promise--died in 1833 at the age of twenty-two. seventeen years later, his second son, henry fitzmaurice hallam, was cut off like his brother at the very threshold of what might have been a great career. the premature death and high talents of these young men, and the association of one of them with the most popular poem of the age, have made hallam's family afflictions better known than any other incidents of his life. he survived wife, daughter and sons by many years. in 1834 hallam published the remains in prose and verse of arthur henry hallam, with a sketch of his life. in 1852 a selection of literary essays and characters from the literature of europe was published. hallam was a fellow of the royal society, and a trustee of the british museum, and enjoyed many other appropriate distinctions. in 1830 he received the gold medal for history, founded by george iv.  the middle ages is described by hallam himself as a series of historical dissertations, a comprehensive survey of the chief circumstances that can interest a philosophical inquirer during the period from the 5th to the 15th century. the work consists of nine long chapters, each of which is a complete treatise in itself. the history of france, of italy, of spain, of germany, and of the greek and saracenic empires, sketched in rapid and general terms, is the subject of five separate chapters. others deal with the great institutional features of medieval society--the development of the feudal system, of the ecclesiastical system, and of the free political system of england. the last chapter sketches the general state of society, the growth of commerce, manners, and literature in the middle ages. the book may be regarded as a general view of early modern history, preparatory to the more detailed treatment of special lines of inquiry carried out in his subsequent works, although hallam's original intention was to continue the work on the scale on which it had been begun. the constitutional history of england takes up the subject at the point at which it had been dropped in the view of the middle ages, viz, the accession of henry vii, and carries it down to the accession of george iii. hallam stopped here for a characteristic reason, which it is impossible not to respect and to regret. he was unwilling to excite the prejudices of modern politics which seemed to him to run back through the whole period of the reign of george iii; nevertheless, he was accused of bias.  the quarterly review for 1828 contains an article on the constitutional history, written by southey, full of reproach. the work, he says. is the production of a decided partisan, who rakes in the ashes of long-forgotten and a thousand times buried slanders, for the means of heaping obloquy on all who supported the established institutions of the country. hallams view of constitutional history was that it should contain only so much of the political and general history of the time as bears directly on specific changes in the organization of the state, including judicial as well as ecclesiastical institutions.  it was his cool treatment of such sanctified names as charles i, cranmer and laud that provoked the indignation of southey, who forgot that the same impartial measure was extended to statesmen on the other side. if hallam ever deviated from perfect fairness, it was in the tacit assumption that the 19th century theory of the constitution was the right theory in previous centuries, and that those who departed from it on one side or the other were in the wrong. he did unconsciously antedate the constitution, and it is clear from incidental allusions in his last work that he did not favour the democratic changes he thought to be impending. hallam, like macaulay, ultimately referred all political questions to the standard of whig constitutionalism. but he was scrupulously conscientious in collecting and weighing his materials. in this he was helped by his legal training, and it was this which made the constitutional history one of the standard text-books of english politics. like the constitutional history, the introduction to the literature of europe continues a branch of inquiry which had been opened in the view of the middle ages. in the first chapter of the literature, which is to a great extent supplementary to the last chapter of the middle ages, hallam sketches the state of literature in europe down to the end of the 14th century: the extinction of ancient learning which followed the fall of the roman empire and the rise of christianity; the preservation of the latin language in the services of the church; and the slow revival of letters, which began to show itself soon after the 7th century--the nadir of the human mind--had been passed. for the first century and a half of his special period he is mainly occupied with a review of classical learning, and he adopts the plan of taking short decennial periods and noticing the most remarkable works which they produced.  the rapid growth of literature in the 16th century compels him to resort to a classification of subjects: in the period 1520-1550 we have separate chapters on ancient literature, theology, speculative philosophy and jurisprudence, the literature of taste, and scientific and miscellaneous literature; and the subdivisions of subjects is carried further of course in the later periods. thus poetry, the drama and polite literature form the subjects of separate chapters. one inconvenient result of this arrangement is that the same author is scattered over many chapters, according as his works fall within this category or that period of time. names like shakespeare, grotius, francis bacon and thomas hobbes appear in half a dozen different places. the individuality of great authors is thus dissipated except when it has been preserved by an occasional sacrifice of the arrangement--and this defect, if it is to be esteemed a defect, is increased by the very sparing references to personal history and character with which hallam was obliged to content himself. his plan excluded biographical history, nor is the work, he tells us, to be regarded as one of reference. it is rigidly an account of the books which would make a complete library of the period, arranged according to the date of their publication and the nature of their subjects. the history of institutions like universities and academies, and that of great popular movements like the reformation, are of course noticed in their immediate connection with literary results; but hallam had little taste for the spacious generalization which such subjects suggest. the great qualities displayed in this work have been universally acknowledged--conscientiousness, accuracy, judgment and enormous reading. not the least styiking testimony to hallam's powers is his mastery over so many diverse forms of intellectual activity. in science and theology, mathematics and poetry, metaphysics and law, he is a competent and always a fair if not a profound critic. the bent of his own mind is manifest in his treatment of pure literature and of political speculation--which seems to be inspired with stronger personal interest and a higher sense of power than other parts of his work display. not less worthy of notice in a literary history is the good sense by which both his learning and his tastes have been held in control. probably no writer ever possessed a juster view of the relative importance of men and things. the labour devoted to an investigation is with hallam no excuse for dwelling on the result, unless that is in itself important. he turns away contemptuously from the mere curiosities of literature, and is never tempted to make a display of trivial erudition. nor do we find that his interest in special studies leads him to assign them a disproportionate place in his general view of the literature of a period. hallam is generally described as a philosophical historian. the description is justified not so much by any philosophical quality in his method as by the nature of his subject and his own temper. hallam is a philosopher to this extent that both in political and in literary history he fixed his attention on results rather than on persons. his conception of history embraced the whole movement of society. beside that conception the issue of battles and the fate of kings fall into comparative insignificance. we can trace the pedigree of princes, he reflects, fill up the catalogue of towns besieged and provinces desolated, describe even the whole pageantry of coronations and festivals, but we cannot recover the genuine history of mankind. but, on the other hand, there is no trace in hallam of anything like a philosophy of history or society. wise and generally melancholy reflections on human nature and political society are not infrequent in his writings, and they arise naturally and incidentally out of the subject he is discussing. his object is the attainment of truth in matters of fact. sweeping theories of the movement of society, and broad characterizations of particular periods of history seem to have no attraction for him.  the view of mankind on which such generalizations are usually based, taking little account of individual character, was distasteful to him. thus he objects to the use of statistics because they favour the tendency to regard all men as mentally and morally equal. at the same time hallam by no means assumes the tone of the mere scholar. he is solicitous to show that his point of view is that of the cultivated gentleman and not of the specialist. thus he tells us that montaigne is the first french author whom an english gentleman is ashamed not to have read. in fact, allusions to the necessary studies of a gentleman meet us constantly, reminding us of the unlikely erudition of the schoolboy in macaulay. hallam's prejudices, so far as he had any, belong to the same character. his criticism assumes a tone of moral censure when he has to deal with certain extremes of human thought--scepticism in philosophy, atheism in religion and democracy in politics. macaulays essay in review of the constitutional history is available at: http://www.history1700s.com/etexts/html/texts/1cahe10.txt references.";
	
	SuffixTree st(sg);
	return 0;}