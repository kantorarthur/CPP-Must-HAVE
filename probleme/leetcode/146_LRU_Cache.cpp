#include <utility>
#include <unordered_map>
#include <list>

using namespace std;


class LRUCache {
public:
    list<pair<int, int>> lru;
    unordered_map<int, list<pair<int, int>>::iterator> map;
    size_t current_size{};
    int capacity{};
    LRUCache(int capacity) : capacity{capacity} {

    }
   //The idea is: I map the list in the map
   //
   // And at every operation I check wether the list actually exists or not
   //
   // If it exists, I'm doing the operation on that list and then I'm moving it
   // To the front of the list.
    int get(int key) {
        auto it = map.find(key);
        if(it == map.end())
            return -1;
        lru.splice(lru.begin(), lru, it -> second);
        return (it -> second) -> second;
    }
    
    void put(int key, int value) {
        auto it = map.find(key);
        if(it != map.end())
        {
            (it -> second) -> second = value;
            lru.splice(lru.begin(), lru, it -> second);
            return ;
        }
        if(capacity == map.size())
        {
            map.erase(lru.back().first);
            lru.pop_back();
        }
        lru.emplace_front(key, value);
        map.emplace(key, lru.begin());
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
