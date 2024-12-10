//
// Created by tasnim on 12/4/2024.
//

#ifndef ASSIGNMENT2_CHAININGMEHTOD_H
#define ASSIGNMENT2_CHAININGMEHTOD_H
#include "vector"
#include "iostream"
#include "list"
#include "math.h"

using namespace std;
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
#endif //ASSIGNMENT2_CHAININGMEHTOD_H
