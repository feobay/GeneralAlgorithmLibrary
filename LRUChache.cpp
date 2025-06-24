#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    int _key, _val;
    Node *_prev, *_next;
    Node(int key, int val) : _key(key), _val(val) {}
};

class LRUCache {
    int _capacity;
    Node *dummy;
    unordered_map<int, Node *> _chache_items_map;
    void remove(Node *tmp) {
        tmp->_next->_prev = tmp->_prev;
        tmp->_prev->_next = tmp->_next;
    }
    void push_front(Node *tmp) {
        tmp->_next = dummy->_next;
        tmp->_prev = dummy;
        dummy->_next->_prev = tmp;
        dummy->_next = tmp;
        
    }
public:
    LRUCache(int capacity) : _capacity(capacity) {
        dummy = new Node(-1, -1);
        dummy->_prev = dummy;
        dummy->_next = dummy;
    }
    
    int get(int key) {
        // auto it = _chache_items_map.begin(); // unordered_map<int, Node *>::iterator it;
        // it = _chache_items_map.find(key);
        // if (it == _chache_items_map.end()) {
        //     return -1;
        // }

        if (!_chache_items_map.count(key)) {
            return -1;
        }
        Node * tmp = _chache_items_map[key];
        remove(tmp);
        push_front(tmp);
        return tmp->_val;
    }
    
    void put(int key, int value) {
        if (_chache_items_map.count(key)) {
            Node *tmp = _chache_items_map[key];
            tmp->_val = value;
            remove(tmp);
            push_front(tmp);
            return ;
        }
        Node *tmp = new Node(key, value);
        push_front(tmp);
        _chache_items_map[key] = tmp;

        if (_chache_items_map.size() > _capacity) {
            Node *tail = dummy->_prev;
            remove(tail);
            _chache_items_map.erase(tail->_key);
            delete tail;
        }
    }
};

int main() {

    return 0;
}