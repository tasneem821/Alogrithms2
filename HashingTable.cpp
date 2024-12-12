#include "iostream"
#include "list"
#include "math.h"
#include "vector"

using namespace std;
class DoubleHashing{
private:
    int size;
    vector<int>table;
    vector<bool> deleted;
    bool isPrime(int size){
        if(size<=1) return false;
        else{
            for(int i =2;i*i<=size;i++){
                if(size%i==0)return false;
            }
            return true;
        }
    }
    int findLessPrimeNumberThansize(int size){
        for(int i=size-1;i>1;i--){
            if(isPrime(i)==true) return i;
        }
        return 2;
    }
    int DivisonMethodFun(int key) {
//        cout<<"problem"<<"\n";
        return (key % size);
    }
    int DivisionMethod2(int key){
        int newsize = findLessPrimeNumberThansize(size);
        return( newsize-(key%newsize));

    }
    double MultiplicationMethodFun(int key){
        double a = (sqrt(5)-1)/2;
        double num = key * a;
        double mod = num - floor(num);
        int res = int(floor(size*mod));
        return res;
    }

    double MultiplicationMethod2(int key){
        double a = (sqrt(5)-1)/2;
        double num = key * a;
        double mod = num - floor(num);
        int newsize = findLessPrimeNumberThansize(size);

        int res = int(floor(newsize*mod));
        return newsize-res;
    }
    int mid_square(int key){
        int squareNum = key*key;
        int mid = (squareNum/100)%100;
        return mid%table.size();
    }
    int midsquare2(int key){
        int squareNum = key*key;
        int mid = (squareNum/100)%100;
        int newsize = findLessPrimeNumberThansize(size);

        return newsize-(mid%newsize);
    }
    int foldingMethod(int key){
        string keystring = to_string(key);
        int sum =0;
        for(int i=0;i<keystring.size();i+=2){
            string ans = keystring.substr(i,2);
            sum+= stoi(ans);
        }
        return sum%table.size();
    }
    int foldingMethod2(int key){
        string keystring = to_string(key);
        int sum =0;
        for(int i=0;i<keystring.size();i+=2){
            string ans = keystring.substr(i,2);
            sum+= stoi(ans);
        }
        int newsize = findLessPrimeNumberThansize(size);

        return newsize-(sum%newsize);
    }
    int hash1(int key){
        return DivisonMethodFun(key);
    }
    int hash2(int key){
        return DivisionMethod2(key);
    }
    int doubleHashingMehtod(int key,int index){
        int ans = (hash1(key)+(index* hash2(key)))%size;
        return ans;
    }
public:
    DoubleHashing(int size) : size(size), table(size,-1),deleted(size,false) {}
    void DoubleHashingInsert(int key){
        int index =0;
        int keyIndex = doubleHashingMehtod(key,index);
        while (table[keyIndex]!=-1&&table[keyIndex]!=key&&!deleted[keyIndex]){
            index++;
            keyIndex = doubleHashingMehtod(key,index);
        }
        table[keyIndex]=key;
        deleted[keyIndex]= false;

    }
    void DoubleHashingSearch(int key){
        int index =0;
        int keyIndex = doubleHashingMehtod(key,index);
        while (table[keyIndex]!=-1){
            while(table[keyIndex]==key&&!deleted[keyIndex]){
                cout<<"the key"<<key<<" is found\n ";
                return;
            }
            index++;
            keyIndex = doubleHashingMehtod(key,index);
        }
        cout<<"the key "<<key<<" is not found\n ";
    }
    void DoubleHashingDelete(int key){
        int index =0;
        int keyIndex = doubleHashingMehtod(key,index);
        while (table[keyIndex]!=-1){
            while(table[keyIndex]==key&&!deleted[keyIndex]){
                deleted[keyIndex]=true;
                table[keyIndex]=-1;
                cout<<"the key "<<key<<" is deleted\n ";
                return;
            }
            index++;
            keyIndex = doubleHashingMehtod(key,index);
        }
        cout<<"the key "<<key<<" is not found for deletion\n ";
    }
    void print() {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                cout << "Index " << i << ": Empty" << endl;
            } else if (deleted[i]) {
                cout << "Index " << i << ": Deleted" << endl;
            } else {
                cout << "Index " << i << ": " << table[i] << endl;
            }
        }
    }
};
class ChaingingMethod{
private:
    int size;
    vector<list<int>>table;

    //Divison Method
    int DivisonMethodFun(int key) {
//        cout<<"problem"<<"\n";
        return (key % size);
    }
    double MultiplicationMethodFun(int key){
        double a = (sqrt(5)-1)/2;
        double num = key * a;
        double mod = num - floor(num);
        int res = int(floor(size*mod));
        return res;
    }

    int mid_square(int key){
        int squareNum = key*key;
        int mid = (squareNum/100)%100;
        return mid%table.size();
    }
    int foldingMethod(int key){
        string keystring = to_string(key);
        int sum =0;
        for(int i=0;i<keystring.size();i+=2){
            string ans = keystring.substr(i,2);
            sum+= stoi(ans);
        }
        return sum%table.size();
    }
public:

    explicit ChaingingMethod(int size) : size(size) ,table(size){}


    void print(){
        for(int i=0;i<size;i++){
            cout<<"table["<<i<<"]";
            for(int ele: table[i]){

                cout<<"-->"<<ele;
            }
            cout<<"\n";
        }
    }
    void insertDivisonmethod(int element){

        int keyIndex = DivisonMethodFun(element);
//        cout<<"problem2";
        table[keyIndex].push_back(element);

    }

    //search Division Method
    void searchDivisionMethod(int key){
        int keyIndex = DivisonMethodFun(key);
        bool found = false;
        for(int element : table[keyIndex]){
            if(element==key){
                found = true;
                cout<<"the element is found\n";

            }


        }
        if(!found){
            cout<<"canot find the element \n";
        }
    }
};
class Linearprobing{

    vector<int> table;
    int DivisonMethodFun(int key) {
//        cout<<"problem"<<"\n";
        return (key % table.size());
    }
    double MultiplicationMethodFun(int key){
        double a = (sqrt(5)-1)/2;
        double num = key * a;
        double mod = num - floor(num);
        int res = int(floor(table.size()*mod));
        return res;
    }
    int mid_square(int key){
        int squareNum = key*key;
        int mid = (squareNum/100)%100;
        return mid%table.size();
    }
    int foldingMethod(int key){
        string keystring = to_string(key);
        int sum =0;
        for(int i=0;i<keystring.size();i+=2){
            string ans = keystring.substr(i,2);
            sum+= stoi(ans);
        }
        return sum%table.size();
    }

public:
    Linearprobing(int size) : table(size,-1) {}

    void insertLinear(int key) {
        int keyIndex = DivisonMethodFun(key);
        int i = 0;

        for(int i=0;i<table.size();i++) {
            int index = (keyIndex + (i)) % table.size();
            if (table[index]==-1||table[index]==-2) {
                table[index]=key;
                return;
            }
        }
        cout << " Cannot insert key " << key <<"there is no space" << "\n";

    }

    void print() {
        for (int i = 0; i < table.size(); ++i) {
            if (table[i] == -1)
                cout << "table[" << i << "] is empty" << endl;
            else if (table[i] == -2)
                cout << "table[" << i << "] is deleted" << endl;
            else
                cout << "table[" << i << "] key = " << table[i] << endl;
        }
    }


    void searchLinearProbing(int key){
        int keyIndex = DivisonMethodFun(key);
//        cout<<index;

        for (int i = 0; i < table.size(); i++) {
            int index = (keyIndex + i) % table.size();
            if (table[index] == -1) {
                cout << "The key " << key << " was not found." << endl;
                return;
            }
            if (table[index] == key) {
                cout << "The key " << table[index] << " was found at index " << index << endl;
                return;
            }
        }
        cout<<"the key is not found\n";



    }


    void deleteLinearProbing(int key){
        int keyIndex = DivisonMethodFun(key);
        for (int i = 0; i < table.size(); i++) {
            int index = (keyIndex + i) % table.size();
            if (table[index] == -1) {
                cout << "The key " << key << " was not found for deletion." << endl;
                return;
            }
            if (table[index] == key) {
                table[index] = -2;
                cout << "The key " << key << " was deleted successfully." << endl;
                return;
            }
        }
        cout<<"the element is not found to be deleted\n";
    }



};


//////////////////////Quadaratic Technique///////////////////
class QuadraticProbing{

    std::vector<int> table;
    int DivisonMethodFun(int key) {
//        cout<<"problem"<<"\n";
        return (key % table.size());
    }
    double MultiplicationMethodFun(int key){
        double a = (sqrt(5)-1)/2;
        double num = key * a;
        double mod = num - floor(num);
        int res = int(floor(table.size()*mod));
        return res;
    }

public:
    QuadraticProbing(int size) : table(size,-1) {}

    void insert(int key) {
        int keyIndex = DivisonMethodFun(key);

        for(int i=0;i<table.size();i++) {
            int index = (keyIndex + (i * i)) % table.size();
            if (table[index] == -1 || table[index] == -2) {
                table[index] = key;
                return;
            }
        }
        cout << " Cannot insert key " << key <<"there is no space" << "\n";

    }

    void print() {
        for (int i = 0; i < table.size(); ++i) {
            if (table[i] == -1)
                cout << "table[" << i << "] is empty" << endl;
            else if (table[i] == -2)
                cout << "table[" << i << "] is deleted" << endl;
            else
                cout << "table[" << i << "] key = " << table[i] << endl;
        }
    }


    void searchQuadraticProbing(int key){
        int keyIndex = DivisonMethodFun(key);
//        cout<<index;

        for (int i = 0; i < table.size(); i++) {
            int index = (keyIndex + i * i) % table.size();
            if (table[index] == -1) {
                cout << "The key " << key << " was not found." << endl;
                return;
            }
            if (table[index] == key) {
                cout << "The key " << table[index] << " was found at index " << index << endl;
                return;
            }
        }

        cout<<"the key is not found\n";



    }


    void deleteQuadraticProbing(int key){
        int keyIndex = DivisonMethodFun(key);
        for (int i = 0; i < table.size(); i++) {
            int index = (keyIndex + i * i) % table.size();
            if (table[index] == -1) {
                cout << "The key " << key << " was not found for deletion." << endl;
                return;
            }
            if (table[index] == key) {
                table[index] = -2;
                cout << "The key " << key << " was deleted successfully." << endl;
                return;
            }
        }
        cout<<"the element is not found to be deleted\n";
    }



};
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
