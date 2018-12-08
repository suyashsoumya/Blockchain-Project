#include "Blockchain.h"


Blockchain::Blockchain(){
    difficulty = 1;
}

vector<Block> Blockchain::getBlockchain() { return blockchain; }


Block Blockchain::getLastBlock(){ return blockchain.back(); }


bool Blockchain::isBlockchainValid(){
    if(blockchain.size() == 0){ return true; }
    for (int i = 1; i < blockchain.size(); ++i){
        Block currBlock = blockchain[i];
        Block prevBlock = blockchain[i-1];
        if(currBlock.getHash() != currBlock.genHash()){ return false; } 
        if(currBlock.getPrevHash() != prevBlock.getHash()){ return false; } 
    }
    return true;
}

void Blockchain::addBlock(string data, time_t timestamp){
    int index = blockchain.size();
    string prevHash;
    if(blockchain.size() > 0){
        prevHash = getLastBlock().getHash();
    }else{
        prevHash = "0";
    }
    Block newBlock (index, data, prevHash, timestamp);
    newBlock.mine(difficulty);
    blockchain.push_back(newBlock);
}

void Blockchain::displayBlockchain() {
    if(blockchain.size() == 0){
        cout << "No blocks in this blockchain" << endl;
    }else{
        for (int i = 0; i < blockchain.size(); ++i){
            Block currBlock = blockchain[i];
            cout << "Block=======================================" << endl;
            cout << "Index: " <<currBlock.getIndex() << endl;
            cout << "Data: " << currBlock.getData() << endl;
            cout << "Timestamp: " << currBlock.getTimestamp() << endl;
            cout << "Hash: " << currBlock.getHash() << endl;
            cout << "Previous Hash: " << currBlock.getPrevHash() << endl;
        }
    }


}

