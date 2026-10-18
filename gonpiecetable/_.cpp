#include "_.hpp"
#include <iostream>

gonpiecetable::gonpiecetable(std::string& str) {
    constbuf = str;
    gonpiece p;
    p.type = buffertype::constb;
    p.start = 0;
    p.length = str.length();
    pieces.push_back(p);
    
}

gonpiecetable::~gonpiecetable() {

}

gonpiecetable& gonpiecetable::operator+=(std::string str) {
    gonpiece p;
    p.type = buffertype::addb;
    p.start = addbuf.length();
    p.length = str.length();
    pieces.push_back(p);
    addbuf += str;


    return *this;
}


void gonpiecetable::insert(int index, std::string& str) {
    int l = 0;
    int i = 0;
    while (l < index && i < pieces.size()) {
        l += pieces[i].length;
        ++i;
    }
    if (index == l) {
        gonpiece addp;
        addp.type = buffertype::addb;
        addp.start = addbuf.length();
        addp.length = str.length();
        pieces.insert(pieces.begin() + i, addp);
        addbuf += str;
    } else {
        int sa = index - l;
        gonpiece& h = pieces[i - 1];

        gonpiece p;
        p.type = h.type;
        p.start = h.length + sa;
        p.length = -sa;
        pieces.insert(pieces.begin() + i, p);

        pieces[i - 1].length = pieces[i - 1].length + sa;


        gonpiece addp;
        addp.type = buffertype::addb;
        addp.start = addbuf.length();
        addp.length = str.length();
        pieces.insert(pieces.begin() + i, addp);
        addbuf += str;
    }
}

void gonpiecetable::backspace(int index) {
    int l = 0;
    int i = 0;
    while (l < index && i < pieces.size()) {
        l += pieces[i].length;
        ++i;
    }
    if (index == l) {
        gonpiece& h = pieces[i - 1];
        h.length -= 1;
    } else {
        int sa = index - l;
        gonpiece& h = pieces[i - 1];
        if (sa == -(h.length) + 1) {
            h.start += 1;
            h.length -= 1;
        } else {
            gonpiece p;
            p.type = h.type;
            p.start = h.length + sa;
            p.length = -sa;
            pieces.insert(pieces.begin() + i, p);

            pieces[i - 1].length = pieces[i - 1].length + sa - 1;

        }
    }
}











gonpiecetable::iterator gonpiecetable::begin() {
    iterator i;
    i.pp = this;
    return i;
}

gonpiecetable::iterator gonpiecetable::end() {
    iterator i;
    i.pp = this;
    int l = pieces.size();
    i.piecenum = l;
    i.piecechar = 0;

    return i;
}

gonpiecetable::iterator& gonpiecetable::iterator::operator++() {
    if (pp->pieces[this->piecenum].length > (this->piecechar + 1)) {
        this->piecechar += 1;
    } else {
        this->piecenum += 1;
        this->piecechar = 0;
    }
    return *this;
}

gonpiecetable::iterator gonpiecetable::iterator::operator++(int) {
    gonpiecetable::iterator temp = *this;
    ++(*this);
    return temp;
}

char& gonpiecetable::iterator::operator*() {
    gonpiece& p = pp->pieces[this->piecenum];
    return ((p.type == buffertype::addb) ? pp->addbuf[this->piecechar + p.start] : pp->constbuf[this->piecechar + p.start]);
}
const char& gonpiecetable::iterator::operator*() const {
    gonpiece& p = pp->pieces[this->piecenum];
    return ((p.type == buffertype::addb) ? pp->addbuf[this->piecechar + p.start] : pp->constbuf[this->piecechar + p.start]);
}

/*


        for (int j = 0; j < pieces.size(); j++) {
            std::cout << "================== " << ((pieces[j].type == buffertype::addb) ? "tuika " : "motok ") << "nagasa " << pieces[j].length << " start " << pieces[j].start << std::endl;
        }

*/