#include "iostream"
#include "OpenAdressing.h"
#include "DoubleHashing.h"
#include "MultiplicationMethod.h"
#include "ChainingMehtod.h"
using namespace std;
int main() {
    cout<<"=================Chaining Techniques===============\n";

    cout<<"=================Divison Method===============\n";
    ChaingingMethod h1(7);

    h1.insertDivisonmethod(10);
    h1.insertDivisonmethod(20);
    h1.insertDivisonmethod(15);
    h1.insertDivisonmethod(7);
    h1.insertDivisonmethod(27);
    h1.insertDivisonmethod(14);
    h1.insertDivisonmethod(18);

    h1.searchDivisionMethod(10);
    h1.searchDivisionMethod(27);
    h1.searchDivisionMethod(14);
    h1.searchDivisionMethod(30);
    h1.searchDivisionMethod(25);

    h1.print();

    cout<<"================= Open Addressing Techniques===============\n";

    cout<<"================= Linear Probing  ===============\n";
    Linearprobing hashTable(10);

    hashTable.insertLinear( 10);
    hashTable.insertLinear( 20);
    hashTable.insertLinear( 15);
    hashTable.insertLinear( 7);
    hashTable.insertLinear( 27);
    hashTable.insertLinear( 14);
    hashTable.insertLinear( 18);


    hashTable.print();

    hashTable.searchLinearProbing(20);
    hashTable.searchLinearProbing(15);
    hashTable.searchLinearProbing(5);
    hashTable.searchLinearProbing(3);
    hashTable.searchLinearProbing(7);
    hashTable.searchLinearProbing(0);
hashTable.deleteLinearProbing(2);
hashTable.print();
hashTable.insertLinear(20);
hashTable.print();
    cout<<"================= Quadratic Probing  ===============\n";

    QuadraticProbing hashTable2(10);

    hashTable2.insert( 2);
    hashTable2.insert( 12);
    hashTable2.insert( 22);
    hashTable2.insert( 32);



    hashTable2.print();

    hashTable2.searchQuadraticProbing(1);
    hashTable2.searchQuadraticProbing(4);
    hashTable2.searchQuadraticProbing(5);
    hashTable2.searchQuadraticProbing(3);
    hashTable2.searchQuadraticProbing(2);
    hashTable2.searchQuadraticProbing(2);
    hashTable2.deleteQuadraticProbing(2);
    hashTable.print();
    cout<<"=================Double Hashing Techniques===============\n";
DoubleHashing hashTable3(13);
    hashTable3.DoubleHashingInsert( 18);
    hashTable3.DoubleHashingInsert( 41);
    hashTable3.DoubleHashingInsert( 22);
    hashTable3.DoubleHashingInsert( 44);
    hashTable3.DoubleHashingSearch( 18);
    hashTable3.DoubleHashingSearch( 41);
    hashTable3.DoubleHashingSearch( 22);
    hashTable3.DoubleHashingSearch( 20);


    hashTable3.print();
    hashTable3.DoubleHashingDelete( 22);
    hashTable3.DoubleHashingDelete( 20);
    hashTable3.print();
}