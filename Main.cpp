#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TrieNode {
	
	public :
	
	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {
		
		this -> data = data;
		children = new TrieNode*[26];
		
		for(int i = 0; i < 26; i++) 
		{
			children[i] = NULL;
		}
		
		isTerminal = false;
	}
};

class Trie {
	
	TrieNode *root;

	public :

	int count;

	Trie() {
		
		this->count = 0;
		root = new TrieNode('\0');
	}

	bool insertWord(TrieNode *root, string word) {
		
		if(word.size() == 0) 
		{
			if (!root->isTerminal) 
			{
				root -> isTerminal = true;
				return true;	
			} 
			else 
			{
				return false;
			}
		}

		int index = word[0] - 'a';
		TrieNode *child;
		
		if(root -> children[index] != NULL) 
		{
			child = root -> children[index];
		}
		else 
		{
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}
		
		return insertWord(child, word.substr(1));
	}

	void insertWord(string word) {
		if (insertWord(root, word)) 
		{
			this->count++;
		}
	}
    
    void possibleWord(TrieNode *root, string ans, string pattern){
        
        if(!pattern.size() && root->isTerminal==true)
        {
            cout<< ans<<endl;
        }
        
        if(pattern.size())
        {
            int index = pattern[0] - 'a';
            if(root -> children[index] == NULL) 
            {
                return;
            } 
            else 
            {
                ans +=pattern[0];
                possibleWord(root -> children[index], ans, pattern.substr(1));
            }
        }
        else 
        {
            for(int i = 0; i < 26; i++) 
            {
                if(root -> children[i] != NULL) 
                {
                    string smallAns = ans;
                    smallAns += root -> children[i] -> data;
                    possibleWord(root -> children[i], smallAns, pattern);
                }
            }
        }       
    }
    
    
    TrieNode* findWord(TrieNode *root, string pattern){
        
        if(pattern.size()==0)
        {
            return root;
        }
        
        int index=pattern[0]-'a';
        TrieNode *child;
        
		if(root->children[index]!=NULL)
        {
            child=root->children[index];
            return findWord(child,pattern.substr(1));
        }
        else
        {
            return NULL;
        }
    }
    
    
    void autoComplete(vector<string> input, string pattern) {
        
        for(int i = 0; i < input.size(); i++) 
		{
            insertWord(input[i]);
        }
        
        string ans = "";
        
        possibleWord(root, ans, pattern);
    }
};


int main() {
	
	Trie t;
    int N;
    cin >> N;
    string pattern;
    vector<string> vect;
    for (int i=0; i < N; i++) 
	{
        string word;
        cin >> word;
        vect.push_back(word);
    }
    
	cin >> pattern;
    t.autoComplete(vect, pattern);
}
