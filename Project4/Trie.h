#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>

class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct TrieNode;
    
    struct Node
    {
        Node()
        {
           // m_values = new std::vector<ValueType>;
           // m_children = new std::vector<TrieNode>;
        }
        Node(const ValueType& value)
        {
            m_values.push_back(value);
        }
        Node(TrieNode* trieN)
        {
            m_children.push_back(trieN);
        }
        ~Node() //FIX?
        {
            for(int i=m_values.size()-1; i >= 0; i--)
            {
                m_values.pop_back();
                i--;
            }
            for(int j=m_children.size()-1; j >= 0; j--)
            {
                if(m_children[j] != nullptr)
                    delete m_children[j];
            }
        }
        std::vector<ValueType> m_values;
        std::vector<TrieNode*> m_children;
    };
    struct TrieNode
    {
        TrieNode(Node* newNode, char l)
        {
            node = newNode;
            label = l;
        }
        char getLabel()
        {
            return label;
        }
        Node* getNode()
        {
            return node;
        }
        Node* node;
        char label;
    };
    
    Node* m_root;
    void clearNode(Node* node);
    //  std::vector<ValueType> findNode(const std::string key, bool exactMatchOnly);
};
template<typename ValueType>
Trie<ValueType>::Trie()
{
    m_root = new Node();
}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
    clearNode(m_root);
}

template<typename ValueType>
void Trie<ValueType>::clearNode(Node* node)
{
    if(node == nullptr)
        return;
    for(typename std::vector<TrieNode*>::iterator it = node->m_children.begin(); it != node->m_children.end(); it++)
    {
        clearNode((*it)->getNode());
    }
    delete node;
}

template<typename ValueType>
void Trie<ValueType>::reset()
{}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    Node* curr = m_root;
    for(int i=0; i<key.length(); i++)
    {
        bool insertNode = false;
        for(int n=0; n < curr->m_children.size(); n++)
        {
            if(curr->m_children[n]->getLabel() == key[i])
            {
                if(n == key.size() - 1)
                {
                    curr->m_children[n]->getNode()->m_values.push_back(value);
                    return;
                }
                curr = curr->m_children[n]->getNode();
                insertNode = true;
                break;
            }
            else if(n == key.length()-1 || curr->m_children[n]->getLabel() > key[i] )
            {
                curr->m_children.push_back(new TrieNode(new Node(value),key[i]));
                return;
            }
        }
        if(!insertNode){
            Node* next = new Node();
            curr->m_children.push_back(new TrieNode(next, key[i]));
            curr = next;
        }
        
    }
    
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    std::vector<ValueType> result;
    Node* current = m_root;
    TrieNode* child;
    char label;
    
    for(int i=0; i<key.size(); i++)
    {
        if(exactMatchOnly == true)
        {
            for(int n=0; n < current->m_children.size(); n++)
            {
                child = current->m_children[n];
                if(key[i] == child->getLabel())
                {
                    current = child->getNode();
                    if(i == key.size()-1)
                        result.insert(result.end(), (child->getNode()->m_values).begin(), (child->getNode()->m_values).end());
                    break;
                }
                
            }
        }
        if(exactMatchOnly == false)
        {
            for(int n=0; n < current->m_children.size(); n++)
           {
               child = current->m_children[n];
               if(i != key.size() - 1 && i > 0)
               {
                   std::vector<ValueType> v = find(key.substr(0,i) + child->getLabel() + key.substr(i+1,key.size()-1),true);
                   result.insert(result.end(), v.begin(), v.end());
                   continue;
               }
               else
               {
                std::vector<ValueType> v = find(key.substr(0,i) + child->getLabel(),true);
                   result.insert(result.end(), v.begin(), v.end());
               }
           }
        }
        if(key[i] == child->getLabel())
        {
            continue;
        }
        
    } 
    
    return result;
}
#endif // TRIE_INCLUDED
