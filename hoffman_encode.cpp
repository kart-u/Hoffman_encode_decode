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
    create(q);
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
void getCode(struct hoffmanNode* node,string &s,string hoffCode[]){
    if(node->left==NULL&&node->right==NULL){
        hoffCode[node->data-'a']=s;
        return;
    }
    if(node->left!=NULL){
        s.push_back('0');
        getCode(node->left,s,hoffCode);
        s.pop_back();
    }
    if(node->right!=NULL){
        s.push_back('1');
        getCode(node->right,s,hoffCode);
        s.pop_back();
    }
}
int main(){
    vector<pair<char,int>>v={{'a',5},{'b',9},{'c',12},{'d',13},{'e',16},{'f',45}};
    priority_queue<pair<int,struct hoffmanNode*>,vector<pair<int,struct hoffmanNode*>>,greater<pair<int,struct hoffmanNode*>>>q;
    initializeQueue(q,v);
    struct hoffmanNode* head=create(q);
    string hoffCode[26];
    string s="";
    getCode(head,s,hoffCode);
}