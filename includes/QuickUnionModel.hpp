#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class QuickUnionModel{
    private:
    int count; // number of available components
    int length; //  length of array
    int *id_cache; // access to component id
    public:
    QuickUnionModel(int n){
        count=length = n;
        id_cache = new int[n];
        for(int i=0;i<n;i++)
        {
            id_cache[i] = i; //+ using intergers 
        }
    };
    ~QuickUnionModel(){
        delete [] id_cache;
    };
    void _union(int p,int q){
        int pRoot= find(p);
        int qRoot =find(q);

        if (pRoot==qRoot)  return;
       
        id_cache[pRoot] = qRoot;
        
        
        count--;
    }
    int find(int p){
        while(p != id_cache[p])  p = id_cache[p];
        return p;
    }


    bool connected(int p,int q){
        return find(p)==find(q);
    }


    int getcount() const{ return count;}
    friend void reader(std::string&);
};



void reader(std::string& filePath){
    std::fstream in(filePath);
    if(!in.is_open()) {
        std::cout << " cannot open " <<  filePath << std::endl;
    }
    int N,p,q;
    in >> N;
    QuickUnionModel uf(N);
    while (in>>p>>q) //Todo: read in pair from input
    {
        if (uf.connected(p,q))  continue; // Todo: skip if connected
        uf._union(p,q) ; // Todo: connect the pair together
        std::cout << p <<"  " << q <<std::endl;
    }

    std::cout << uf.getcount() << " component" << std::endl;
    in.close();
}