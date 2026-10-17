#pragma once
#include <string>
#include <vector>

enum class buffertype {
    constb,
    addb
};

struct gonpiece {
    buffertype type = buffertype::constb;
    int start = 0;
    int length = 0;
};

class gonpiecetable {
    public:
        class iterator {
            public:
                iterator& operator++();
                iterator operator++(int);
                char& operator*();
                const char& operator*() const;
                auto operator<=>(const iterator&) const = default;
                int piecenum = 0;
                int piecechar = 0;
                gonpiecetable* pp = nullptr;
            private:
        };
        gonpiecetable(std::string& str);
        ~gonpiecetable();
        iterator begin();
        iterator end();

        gonpiecetable& operator+=(std::string str);
        void insert(int index, std::string& str);
    private:
        std::vector<gonpiece> pieces;
        std::string constbuf = "";
        std::string addbuf = "";

};