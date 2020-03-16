#include<bits/stdc++.h>
using namespace std;
int n,maxChild;
int numc=0,childn=0,nodes=0;
struct node
{
    int numOfKeys;
    node *parent,*next;
    string *english,*bangla;
    bool isLeaf;
    node **index;
} ;
node *root,*firstLeaf;

node* createNode()
{
    node *newNode=new node();
	nodes++;

    newNode->index = new node *[n+1];
    newNode->english=new string[n];
    newNode->bangla=new string[n];

    newNode->numOfKeys = 0;
    newNode->parent = NULL;
    newNode->next = NULL;
    newNode->isLeaf = true;
    return newNode;
}
node *findLeaf(node *tempRt,string english)
{
	
    while(tempRt->isLeaf==false)
    {
        int i;
        for(i=0; i<tempRt->numOfKeys; i++){
			
			if(english<tempRt->english[i]) break;
			
			} 
        tempRt = tempRt->index[i];
    }
    
    
    return tempRt;

}

node *count(node *tempRt,string english)
{
	
    while(tempRt->isLeaf==false)
    {
        int i;
        numc++;
        for(i=0; i<tempRt->numOfKeys; i++){
			
			childn++;
			if(english<tempRt->english[i]) break;
			
			} 
        tempRt = tempRt->index[i];
    }
    
    
    return tempRt;

}

void insertValueAndindex(node *parent,string value,node *right)
{
    int i=parent->numOfKeys-1;
    for(;i>=0; i--)
    {
        if(parent->english[i]<=value) break;
        else
        {
            parent->english[i+1] = parent->english[i];
            parent->index[i+2] = parent->index[i+1];
        }
    }
    parent->english[i+1] = value;
    parent->index[i+2] = right;
    parent->numOfKeys++;
}

void insertMiddle(node *parent,string value,node *left,node *right)
{
    if(parent==NULL)
    {
        parent = createNode();
        parent->english[0] = value;
        parent->index[0] = left;
        parent->index[1] = right;
        parent->numOfKeys++;
        parent->isLeaf = false;
        root = parent;
        left->parent = parent;
        right->parent = parent;
        return;
    }
    right->parent = parent;
    insertValueAndindex(parent,value,right);
    if(parent->numOfKeys==maxChild)
    {
        node *splitNode = createNode();
        splitNode->isLeaf = false;
        int j=0;
        for(int i=parent->numOfKeys-(n-1)/2;i<maxChild; i++)
        {
            splitNode->english[j] = parent->english[i];
            if(j==0)
            {
                splitNode->index[0] = parent->index[i];
                splitNode->index[0]->parent = splitNode;
            }
            splitNode->index[j+1] = parent->index[i+1];
            splitNode->index[j+1]->parent = splitNode;
            j++;
        }
        parent->numOfKeys-=(n-1)/2+1;
        splitNode->numOfKeys = (n-1)/2;
        insertMiddle(parent->parent,parent->english[parent->numOfKeys],parent,splitNode);
    }

}

void insertLeaf(string english,string bangla)
{
    node *leaf = findLeaf(root,english);
    int i= leaf->numOfKeys-1;
    if(i>-1) {
    for( ; i>=0; i--)
    {
    	if(english<leaf->english[i])
    	{
    		leaf->english[i+1] = leaf->english[i];
    		leaf->bangla[i+1] = leaf->bangla[i];
    	}
    	else break;
    }
    }
    leaf->english[i+1] = english;
    leaf->bangla[i+1] = bangla;
    leaf->numOfKeys++;

    if(leaf->numOfKeys==maxChild)
    {
        node *splitNode = createNode();
        int j=0;
        for(int i=leaf->numOfKeys-n/2;i<maxChild; i++)
        {
            splitNode->english[j] = leaf->english[i];
            splitNode->bangla[j] = leaf->bangla[i];
            j++;
        }
        leaf->numOfKeys-=n/2;
        splitNode->numOfKeys = n/2;
        splitNode->next = leaf->next;
        leaf->next = splitNode;
        insertMiddle(leaf->parent,splitNode->english[0],leaf,splitNode);
    }
}

int main(void)
{
	cout << "number of Child:" << endl;
	cin >> n;
	maxChild=n;
	int input=0;
    root = createNode();
    node *leaf;
    int i=0;
    string english,bangla,searchEnglish;
    ifstream ifile;
    ofstream ofile;
    ifile.open("input.txt");
    ofile.open("output.txt");
    if(!ifile) return 0;
    while(ifile>>english)
    {

    	getline(ifile,bangla);
    	getline(ifile,bangla);
    	insertLeaf(english,bangla);
    	input++;
    }
    cout<<"number of input : "<<input<<endl;
    cout<<"number of nodes : "<<nodes<<endl;
    ifile.close();
    cout<<"Enter text to search: ";
    while(cin>>searchEnglish)
    {
    	 leaf= count(root,searchEnglish);
    	 for(i=0; i<leaf->numOfKeys; i++) if(searchEnglish==leaf->english[i]) break;
    	 if(i==leaf->numOfKeys) cout<<"Not found\n";
    	 else{
			 cout<<searchEnglish<<" "<<leaf->bangla[i]<<endl;
			 ofile<<searchEnglish<<" "<<leaf->bangla[i]<<endl;
			 cout<<"Number of node visited : "<<numc+1<<endl;
			 //cout<<"Position of node : "<<childn<<endl;
			 } 
    	 
    	 cout<<"enter text to search: ";
    }


    ofile.close();
}
