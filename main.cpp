//Genghis Khan
#include <iostream>
#include <queue>
using namespace std;

class list; //forward declaration

class node //will be used for both list and trie ADTs
{
public:
    int key;
    list* children; //all the children of the node will be stored in the list
    node* sibling; //within a list, provides access to all children, functions like a "next"
    friend class list;
    friend class trie;
};

class list
{
public:
    node* head;
    list()
    {
        head = new node;
        head->key = -1; //head is a sentinel
        head->sibling = NULL;
        head->children = NULL;
    }

    void insert(int a) //insertion into the list at the head/works properly
    {
        node* v= new node;
        v->key = a;
        v->sibling = head;
        v->children = NULL;
        head = v;
    }

    int size() //so that I can use an empty() boolean, runs properly
    {
        int size = 0;
        node* temp = head;
        while(temp->sibling != NULL)
        {
            size++;
            temp = temp->sibling;
        }
        return size;
    }

    bool empty() //empty condition
    {
        return(size() == 0);
    }

    void print() //works properly
    {
        node* temp = head;
        while(temp->sibling != NULL)
        {
            cout << temp->key << ' ';
            temp = temp->sibling;
        }
        cout << "** ";
    }

    friend class trie;
    friend class node;
};



class tree
{
public:
    node* root; //sentinel root
    queue <node*> q; //queue for using a breadth first search
    tree()
    {
        root = new node;
        root->key = -1; //sentinel
        root->children = NULL; //to be changed when we add children
        root->sibling = NULL; //will never change
        q.push(root); //pushing the root onto the queue for BFS
    }

    bool haschildren(node* v) //if a node has children or not
    {
        return(v->children != NULL);
    }

    bool match(node* v, int k) //check if v's key is the key we are searching for, boolean
    {
        return(v->key == k);
    }

    void enqueue_children(node* v) //enqueue all of a node's children for the breadth first search
    {
        node* iter = v->children->head;
        while(iter->sibling != NULL)
        {
            q.push(iter);
            iter= iter->sibling;
        }
    }

    node* search(int k, node* temp) //breadth first search, always pass it the key to search for and the root node
    {
        //recursive iteration, core Breadth First Search
        if(!match(temp, k))
        {
            if(haschildren(temp))
            {
                q.pop();
                enqueue_children(temp);
                search(k, q.front());
            }
            else
            {
                q.pop();
                search(k, q.front());
            }
        }

        //once the recursion is over
        if(q.empty())
        {
            return NULL;
        }
        else
        {
            return(q.front());
        }
    }

    void insert(int parent, int child) //tree insert
    {
        node* v = search(parent, root); //returns location of the parent key
        if(v != NULL) //if the parent is in the tree
        {
            if(haschildren(v)) //if children list already exists
            {
                v->children->insert(child); //list insert
            }
            else //if there are no children, build a new list and insert
            {
                v->children = new list;
                v->children->insert(child); //list insert
            }
        }
        else
        {
            cout << parent << " not in tree" << endl;
        }
    }

};



int main()
{
    cout << "To insert the root, pass it '-1' and the key for the root." << endl;
    tree t;

    /*void build() //you can uncomment this for a function that will run as many times as you want to insert values
    {
        int parent;
        int child;
        char response;
        cout << "Would you like to continue building the tree (y/n): ";
        cin >> response;
        if(response == 'y')
        {
            cout << "Insert parent key: ";
            cin >> parent;
            cout << "Insert child key: ";
            cin >> child;
            t.insert(parent, child);
            build();
        }
    }*/

    t.insert(-1, 5);
    t.insert(5, 2);
    t.insert(5, 7);
    t.insert(5, 8);
    t.insert(5, 4);
    t.insert(5, 3);
    node* v = t.search(5, t.root);
    (*v->children).print();
    t.insert(7, 12);
    t.insert(7, 14);
    node* q = t.search(7, t.root);
    (*q->children).print();
    t.insert(14, 42);
    t.insert(14, 69);
    node* r = t.search(14, t.root);
    (*r->children).print();
    return 0;
}