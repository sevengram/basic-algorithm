//
// Created by jfan on 7/30/16.
//

#include <vector>
#include <string>

using namespace std;

class trie
{
private:
    struct trie_node
    {
        vector<trie_node *> children;

        bool is_word;

        trie_node() : is_word{false}
        {
            children.resize(26, nullptr);
        }
    };

    trie_node *root;

    trie_node *search_node(const string &str)
    {
        if (root == nullptr) {
            return nullptr;
        }
        trie_node *p = root;
        for (auto &c: str) {
            int i = c - 'a';
            if (p->children[i] == nullptr) {
                return nullptr;
            }
            p = p->children[i];
        }
        return p;
    }

public:
    bool search(const string &word)
    {
        trie_node *n = search_node(word);
        return n != nullptr && n->is_word;
    }

    bool starts_with(const string &word)
    {
        trie_node *n = search_node(word);
        return n != nullptr;
    }

    void insert(const string &word)
    {
        if (root == nullptr) {
            root = new trie_node();
        }
        trie_node *p = root;
        for (auto &c: word) {
            int i = c - 'a';
            if (p->children[i] == nullptr) {
                p->children[i] = new trie_node();
            }
            p = p->children[i];
        }
        p->is_word = true;
    }
};