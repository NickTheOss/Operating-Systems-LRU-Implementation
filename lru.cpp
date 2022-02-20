#include "lru.h"



Node_lru::Node_lru(char typeref, Cell * cell_ptr){  

	this->typeref = typeref;
	this->cell_ptr = cell_ptr;
	prev = NULL;
	next = NULL;

}




List_lru::List_lru(int p_id, PageTable * pt_ptr){  

	this->p_id = p_id;
	this->pt_ptr = pt_ptr;
	read_counter = 0;    
	write_counter = 0;
	page_faults_counter = 0;
	page_exists_counter = 0;
	counter = 0;
	p_id = 0;
	head = NULL;
	tail = NULL;

}



List_lru::~List_lru(){ 

	Node_lru * current;

	while(head){

		current = head;
		head = head->next;
		delete current;


	}
}



void List_lru::move_to_front(Node_lru * node){

	if( node == head ){   
		return;
	}
	else if(node == tail){  

		tail = node->prev; 
		tail->next = NULL;  
		node->prev = NULL;  
		node->next = head;
		head->prev = node;
		head = node;
		
		return;
	}
	
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->prev = NULL;
	node->next = head;
	head->prev = node;
	head = node;
}



bool List_lru::is_exist_page(string page,char type){  

	if(is_empty()) return false; 
	Node_lru * current = head;
	while(current){  

		if(page == current->cell_ptr->page && current->cell_ptr->p_id == p_id){
			page_exists_counter++;  
			if(type == 'W'){  

				current->typeref = 'W'; 
			}
			move_to_front(current);  
			return true;
		}
		current = current->next;
	}
	return false;
}


void List_lru::remove_page(){


	if(counter == 1){   
		counter--;
		if(head->typeref == 'W'){  

			write_counter++;  

		}
		head->cell_ptr->empty = true; 
		delete head;  
		head = NULL;
		tail = NULL;
		tail->prev = NULL;
		return;
	}
	
	counter--;
	Node_lru * temp = tail;
	tail = tail->prev; 
	tail->next = NULL;  
	if(temp->typeref == 'W'){

			write_counter++;

	}
	temp->cell_ptr->empty = true; 
	delete temp;
}



void List_lru::insert_page_to_node(char reference, Cell * cell_ptr){

	Node_lru * temp = new Node_lru(reference, cell_ptr);
	read_counter++;   
	page_faults_counter++;  
	if(is_empty()){
		counter++;
		head = temp;
		tail = temp;
		return;
	}

	counter++;
	temp->next = head;  
	head->prev = temp; 
	head = temp;

}



void List_lru::add_page_to_memory(char reference,string page){

	if(is_exist_page(page,reference))  
		return;    
	if(pt_ptr->is_full()){   

		remove_page();  

	}

	Cell * cell = pt_ptr->insert_page(page, p_id);
	insert_page_to_node( reference, cell);

}