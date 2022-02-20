#ifndef  LRU_H
#define  LRU_H
#include <iostream>
#include "os2.h"

using namespace std;

class Cell;   
class PageTable;

class Node_lru{ 

public:

	Cell * cell_ptr;  
	char typeref;     //attribute 'R'  'W'
	Node_lru * prev;   
	Node_lru * next;	
	Node_lru(char typeref, Cell * cell_ptr);  

};


class List_lru{    

public:

	int read_counter, write_counter, page_faults_counter, p_id, page_exists_counter; 
	Node_lru * head;  
	Node_lru * tail; 
	PageTable * pt_ptr;  
	int counter;    //counter for num of pages added
	List_lru(int p_id, PageTable * pt_ptr);  
	~List_lru();

	bool is_empty(){

		return counter == 0; //
	}

	bool is_exist_page(string page, char  type);   
	void move_to_front(Node_lru * node); 
	void remove_page();   
	void insert_page_to_node(char reference, Cell * cell_ptr); 
	void add_page_to_memory(char reference,string page); 

};


#endif