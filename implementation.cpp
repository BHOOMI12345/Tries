#include<bits/stdc++.h>
using namespace std;

class TrieNode 
{
    public:
      
    char data;
    TrieNode * children[26];
    bool isTreminal;
    int childCount;

    TrieNode(char ch)
    {
        data = ch;
        for(int i = 0;i<26;i++)
        {
            children[i] = NULL;
        }
        childCount = 0;
        isTreminal = false;
    }
};

class Trie
{
    public:

    TrieNode * root;
    Trie(char ch)
    {
        root = new TrieNode(ch);
    }

//INSERTION IN TRIES
    void insertUtil(TrieNode * root, string word)
    {
        if(word.length()==0)
        {
            root->isTreminal = true;
            return ;
        }

        int index = word[0]-'A';
        TrieNode *child;

        if(root->children[index]!=NULL)
        {
            child = root->children[index];
        }

        else
        {
            child = new TrieNode(word[0]);
            root->childCount ++;
            root->children[index] = child;
        }

        insertUtil(child,word.substr(1));
    }

    void insertWord(string word)
    {
        insertUtil(root,word);
    }

//SEARCHING IN TRIES
    bool searchUtil(TrieNode * root, string word)
    {
        if(word.length()==0)
        {
            return root->isTreminal;
        }

        int index = word[0] - 'A';
        TrieNode * child;

        if(root->children[index]!=NULL)
        {
            child = root->children[index];
        }

        else
        {
            return false;
        }

        return searchUtil(child,word.substr(1));
    }

    bool searchword(string str)
    {
        return searchUtil(root,str);
    }


//CHECKING THE PREFIX OF TRIES

    bool  startsWithUtil(TrieNode * root, string prefix)
{
    if(prefix.length()==0)
    {
        return true;
    }

    int index = prefix[0] - 'a';
    TrieNode * child;
    
    if(root->children[index]!=NULL)
    {
        child = root->children[index];
    }

    else
    {
        return false;
    }
    
    return startsWithUtil(child,prefix.substr(1));

}

bool startsWith(string prefix)
{
    return startsWithUtil(root,prefix);
}


//Q1 FINDING LONGEST COMMOM SUBSEQUENCE 

//APPROACH 1
string longestCommonPrefix(vector<string> &arr, int n)
{
    string ans = "";
    for(int i = 0;i<arr[0].length();i++)
    {
        char ch = arr[0][i];

        bool match = true;

        for(int j = 1;j<n;j++)
        {
            if(arr[j].size()<i || ch != arr[j][i])
            {
                match = false;
                break;
            }
        }

        if(match==false)
        {
            break;
        }

        else
        {
            ans.push_back(ch);
        }
    }

    return ans;
}

//APPROACH 2
void lcp(string str, string &arr)
{
    for(int i = 0;i<str.length();i++)
    {
        char ch = str[i];


        if(root->childCount==1)
        {
            arr.push_back(ch);
            int index = ch - 'a';
            root = root->children[index];
        }

        else
        {
            break;
        }

        if(root->isTreminal)
        {
            break;
        }
    }
}

void printSuggestions(TrieNode * curr, vector<int> & temp, string prefix)
{
    if(curr->isTreminal)
    {
        temp.push_back(prefix);
    }
    for(char ch = 'a'; ch<='z';ch++)
    {
        TrieNode * next = curr->children[ch-'a'];
        if(next!=NULL)
        {
            prefix.push_back(ch);
            printSuggestions(next,temp,prefix);
            prefix.pop_back();
        }
    }
}
vector<vector<string>> getSuggestions(string str)
{
    TrieNode * prev;
    vector<vector<string>> output;
    string prefix = "";
    for(int i = 0;i<str.length();i++)
    {
        char lastchr = str[i];
        prefix.push_back(str[i]);

        TrieNode * curr = prev->children[lastchr - 'a'];

        if(curr==NULL)
        {
            break;
        }

        vector<string> temp;

        printSuggestions(curr,temp, prefix);
        output.push_back(temp);
        temp.clear();

        prev = curr;


    }

    return output;
}
};

string lcp1(vector<string> arr, int n)
{
    Trie * t = new Trie('\0');
    for(int i = 0;i<arr.size();i++)
    {
        t->insertWord(arr[i]);
    }

    string first = arr[0];
    string ans = "";
    t->lcp(first,ans);
    return ans;


}



vector<vector<string>> phoneDirectory(vector<string> &contactList, string &queryStr)
{
    Trie *t = new Trie('\0');

    for(int i = 0;i<contactList.size();i++)
    {
        t->insertWord(contactList[i]);
        return t->getSuggestions(queryStr);
    }
}

int main()
{
    Trie * t = new Trie('\0');
    t->insertWord("abcd");
    cout<<"Present or not"<<t->searchword("abcd");
    return 0;

}