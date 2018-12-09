#include "Block.h"
#include "Blockchain.h"

int main(){

    Blockchain b(5); // pass in difficulty value
    
    cout << "Mining Block 0..." << endl;
    time_t time1;
    b.addBlock("Hello", time(&time1)); //pass in data & timestamp
    cout << "Mining Block 0 complete" << endl;

    cout << "Mining Block 1..." << endl;
    time_t time2;
    b.addBlock("Bye", time(&time2));
    cout << "Mining Block 1 complete" << endl;
    
    b.displayBlockchain();
    
    return 0;
}
