#include<bits/stdc++.h>
using namespace std;

struct hoffmanNode{
    char data;
    int feq;
    struct hoffmanNode *left,*right;
};

struct hoffmanNode* create(priority_queue<pair<int,struct hoffmanNode*>,vector<pair<int,struct hoffmanNode*>>,greater<pair<int,struct hoffmanNode*>>>&q){
    if(q.size()==1){
        return q.top().second;
    }
    struct hoffmanNode* node = (struct hoffmanNode*)malloc(sizeof(struct hoffmanNode));
    pair<int,struct hoffmanNode*>p;
    int sum=0;
    node->left=q.top().second;
    sum+=q.top().first;
    q.pop();
    sum+=q.top().first;
    node->right=q.top().second;
    q.pop();
    node->feq=sum;
    node->data='!';
    p.first=sum;
    p.second=node;
    q.push(p);
    return create(q);
}

void initializeQueue(priority_queue<pair<int,struct hoffmanNode*>,vector<pair<int,struct hoffmanNode*>>,greater<pair<int,struct hoffmanNode*>>>&q,vector<pair<char,int>>&v){
    for(auto i:v){
        struct hoffmanNode* node = (struct hoffmanNode*)malloc(sizeof(struct hoffmanNode));
        node->left=NULL;
        node->right=NULL;
        node->data=i.first;
        node->feq=i.second;

        pair<int,struct hoffmanNode*>p;
        p.first=i.second;
        p.second=node;
        q.push(p);
    }
}

void show(struct hoffmanNode* node){
    if(node==NULL){
        return;
    }
    show(node->left);
    cout<<node->data<<" ";
    cout<<node->feq<<" ";
    cout<<"  ";
    show(node->right);
}
void getCode(struct hoffmanNode* node,vector<bool> &s,vector<bool> hoffCode[]){
    if(node->left==NULL&&node->right==NULL){
        // cout<<node->feq<<endl;
        hoffCode[node->data-'a']=s;
        return;
    }
    if(node->left!=NULL){
        s.push_back(false);
        getCode(node->left,s,hoffCode);
        s.pop_back();
    }
    if(node->right!=NULL){
        s.push_back(true);
        getCode(node->right,s,hoffCode);
        s.pop_back();
    }
}

void decoder(struct hoffmanNode* node,vector<bool>&coded,string &decoded,int i,struct hoffmanNode* head){
    if(i==(int)coded.size()+1){
        return;
    }
    if(node->left==NULL&&node->right==NULL){
        decoded.push_back(node->data);
        decoder(head,coded,decoded,i,head);
        return;
    }
    if(coded[i]==false){
        decoder(node->left,coded,decoded,i+1,head);
    }
    else{
        decoder(node->right,coded,decoded,i+1,head);
    }
}

int main(){
    map<char,int>count;
    cout<<"Input string :-";
    string s;
    cin>>s;
    s.push_back('x');
    s.push_back('y');
    for(int i=0;i<s.size();i++){
        count[s[i]]++;
    }
    vector<pair<char,int>>v;
    for(auto i:count){
        v.push_back({i.first,i.second});
    }
    priority_queue<pair<int,struct hoffmanNode*>,vector<pair<int,struct hoffmanNode*>>,greater<pair<int,struct hoffmanNode*>>>q;
    initializeQueue(q,v);
    struct hoffmanNode* head=create(q);
    vector<bool> hoffCode[26];
    vector<bool> s1;
    getCode(head,s1,hoffCode);
    
    vector<bool>coded;
    for(int i=0;i<s.size();i++){
        coded.insert(coded.end(),hoffCode[s[i]-'a'].begin(),hoffCode[s[i]-'a'].end());
    }
    cout<<"Coded :-";
    for(auto i:coded){
        cout<<i;
    }cout<<endl;

    cout<<"Size of Original string:- ";cout<<s.size()*8<<endl;
    cout<<"Size of Coded string:- ";cout<<coded.size()<<endl;
    string decoded;
    decoder(head,coded,decoded,0,head);
    decoded.pop_back();
    decoded.pop_back();
    cout<<"Decoded String:-";
    cout<<decoded<<endl;
}