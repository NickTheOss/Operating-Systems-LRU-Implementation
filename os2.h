#ifndef  OS2_H
#define  OS2_H
#define MAXSIZE 30
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include "lru.h"



using namespace std;



class Cell{   

public:

	int p_id; 
	string page; // page name
	bool empty;  
	Cell(){empty = true; }  


};



class PageTable{  

public:

	Cell * pg_ptr;   
	int size;  
	PageTable(int size){   

		this->size = size;
		pg_ptr = new Cell[size];

	}

	~PageTable(){

		delete [] pg_ptr;

	}
	Cell * insert_page(string page,int p_id);
	bool is_full();
};


void lru( int pg_size, int q, string file1, string file2);

#endif