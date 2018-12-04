#include "Block.h"
#include "sha256.h"



Block::Block(int index, string data, string prevHash, time_t timestamp){
    this->index = index;
    this->data = data;
    this->prevHash = prevHash;
    this->timestamp = timestamp;
    this->hash = genHash();
}

int Block::getIndex(){ return index; }

string Block::getData(){ return data; }

string Block::getHash(){ return hash; }

string Block::getPrevHash(){ return prevHash; }

time_t Block::getTimestamp(){ return timestamp; }

string Block::genHash(){
    string toHash = to_string(index) + data + to_string(timestamp) + prevHash;
    return sha256(toHash);
}

bool Block::isHashValid() { return genHash() == getHash(); }