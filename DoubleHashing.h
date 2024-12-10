//
// Created by tasnim on 12/10/2024.
//

#ifndef ASSIGNMENT2_DOUBLEHASHING_H
#define ASSIGNMENT2_DOUBLEHASHING_H
#include "iostream"
#include "vector"
#include "math.h"
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
#endif //ASSIGNMENT2_DOUBLEHASHING_H
