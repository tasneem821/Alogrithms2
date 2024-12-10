//
// Created by tasnim on 12/4/2024.
//

#ifndef ASSIGNMENT2_OPENADRESSING_H
#define ASSIGNMENT2_OPENADRESSING_H
#include "vector"
#include "iostream"
#include "list"
#include "math.h"
#define EMPTY -1
using namespace std;


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
#endif //ASSIGNMENT2_OPENADRESSING_H
