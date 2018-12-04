#include "Block.h"
#include "Blockchain.h"

int main(){

    Blockchain b;
    
    time_t time1;
    b.addBlock("Hello", time(&time1));

    time_t time2;
    b.addBlock("Bye", time(&time2));
    
    b.displayBlockchain();
    
    return 0;
}
