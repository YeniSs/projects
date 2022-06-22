#ifndef CINEMAPROJECT_REPOSITORY_H
#define CINEMAPROJECT_REPOSITORY_H

#include <vector>
#include <algorithm>
#include <ios>
#include <sstream>
#include <functional>

using namespace std;

template<class T>
class Repository {
    vector<T> objects;
public:
    Repository() = default;;

    ~Repository() = default;;

    int getSize() {
        return objects.size();
    }

    void addObject(T object) {
        objects.push_back(object);
    }

    void removeObject(T object) {
        objects.erase(remove(objects.begin(), objects.end(), object), objects.end());
    }

    string getObjects() {
        string output;
        int i = 1;
        for (auto &item : objects) {
            output += to_string(i) + ". " + item->getInfo() + "\n";
            i++;
        }
        return output;
    }

    T find(function<bool(T)> predicate) {
        for (T l: objects) {
            if (predicate(l))
                return l;
        }
        return nullptr;
    }

    vector<T> findAll(function<bool(T)> predicate) {
        vector<T> tmp;
        for (T l: objects) {
            if (predicate(l))
                tmp.push_back(l);
        }
        return tmp;
    }


};

#endif //CINEMAPROJECT_REPOSITORY_H