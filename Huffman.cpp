/*
 * Filename: huffman.cpp
 Description: Declaration of the class HuffmanTree to represent the binary Huffman Tree
 Author: Azhar Amir Kimanje
 Date: 06/24/2018
 Course: Data Structures II
 *
 *
 * */
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

/*class Huffbuild{
public:

    int val;
    char letter;
    Huffbuild *right;
    Huffbuild *left;

    Huffbuild (int val, char V) {
        this->right=NULL;
        this->left=NULL;
        this->val=val;

    }

};*/
//structure of a tree node

struct Node {
    int frequency;
    char ch;
    Node * left, *right;

};
//function to get a new tree node;

Node* getNode (char ch, int frequency, Node * left, Node* right) {

    Node* node =new Node();

    node->frequency=frequency;
    node->left=left;
    node->right=right;
    node->ch=ch;

    return node;

}
//compares objects  according to highest priority item that has the lowest frequency;
struct comp {
    bool operator()(Node*X, Node*Y) {

        return X->frequency > Y-> frequency;
    }
};

// using  map; traverses through the huffman Tree and encodes the characters;
void encodetree( Node * root, string str, unordered_map<char, string >& huffmanCode) {

if(root==nullptr)
    return;
if (!root-> left && !root->right) {
    huffmanCode[root->ch]=str;
}
    encodetree(root->left,str + "0", huffmanCode);
    encodetree(root->right,str + "1", huffmanCode);
}

//traverses through the huffman Tree and encodes the characters
void decodetree( Node * root, int  &position, string str) {
    if(root==nullptr) {
        return;

    }
    //when a leaf node is found
    if (!root-> left && !root->right) {
        cout << root ->ch;
        return;
    }
    position++;

    if(str[position]=='0')
        decodetree(root->left,position, str);
    else
    decodetree(root->right,position, str);

}

//assigns the characters with a frequency and print them out
/*vector <pair<char, int>> frequencyDeter (string lines) {
    map<char,int> ln;
    for(int i=0;i <lines.size(); i++) {
        ln[lines[i]]++;
    }
    vector <pair<char,int>> v;
    for(int i=0;i<lines.size(); i++) {
        if(ln[lines[i]]!=0){
           v.push_back(make_pair(lines[i],ln[lines[i]]));
           ln[lines[i]]=0;
        }
    }
    for(int i=0;i<v.size(); i++) {
        cout << "{element: " << v[i].first << ", " << "frequency: " << v[i].second << "}"<<  endl;
    }

    return v;
}*/

void buildHuffmanTree(string const& lines) {
    unordered_map<char, int> freq;
    for(char ch:lines) {
        freq[ch]++;
    }

    //used a priority queue to store live nodes of tree
    priority_queue<Node* , vector<Node*>, comp> pq;

    //create a leaf node of each character and add it to the priority queue
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));

    }
     while (pq.size()!=1) {

         Node *left=pq.top(); pq.pop();
         Node *right=pq.top(); pq.pop();

         int sum =left-> frequency + right->frequency;
         pq.push(getNode ('\0', sum, left, right));
     }
     Node * root =pq.top();
     unordered_map<char, string> huffmanCode;
     encodetree(root, "", huffmanCode);

     //printing the encoded string
     string str="";
     for (char ch:lines) {
         str+=huffmanCode[ch];

     }
     cout << str << endl;
//decoding back to original
     int index =-1;
     cout << "\nDecoded string is: " << endl;
     while (index< (int)str.size()-2) {
         decodetree(root,index,str);

     }
};
int main() {
 string paragraph;
 /*stringstream ss;
 ifstream myfile;

 myfile.open("../test-file-0.txt");

 if(!myfile) {
    cout << "Messed up" << endl;

 } else {
    cout << "You did it" << endl;

}
    getline(myfile,paragraph);*/

buildHuffmanTree(paragraph);

 /*vector <pair<char, int >> frq = frequencyDeter(paragraph);
    for(int i=frq.size();i>=0; i--) {
        cout << "{element: " << frq[i].first << ", " << "frequency: " << frq[i].second << "}"<<  endl;
    }*/
    return 0;
}