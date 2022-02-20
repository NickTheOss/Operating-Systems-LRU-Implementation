#include "os2.h"




bool PageTable::is_full(){   

	for (int i = 0; i < size; ++i)
	{
		if(pg_ptr[i].empty)   
			return false;
	}

	return true;

}


Cell * PageTable::insert_page(string page,int p_id){   


	for (int i = 0; i < size; ++i)  
	{
		if(pg_ptr[i].empty){  
			pg_ptr[i].empty = false; 
			pg_ptr[i].page = page;  
			pg_ptr[i].p_id = p_id;
			return & pg_ptr[i];  
		}
	}
}


void lru(int pg_size,int q){   
	
	char address[MAXSIZE],reference[MAXSIZE];
	PageTable pg(pg_size); 
	
	List_lru list1( 1, &pg);  
	List_lru list2( 2, &pg);  
	FILE * fp1 = fopen("bzip.trace","r");  
	FILE * fp2 = fopen("gcc.trace","r");

	for (int i = 0; i < q; ++i)  
	{
		fscanf(fp1,"%s",address);  
		fscanf(fp1,"%s",reference);
		address[5] = 0;  
		list1.add_page_to_memory( reference[0], address); 
		fscanf(fp2,"%s",address); 
		fscanf(fp2,"%s",reference);
		address[5] = 0;
		list2.add_page_to_memory( reference[0], address); 
		
	}
	fclose(fp1);
	fclose(fp2);

	cout << "Process 1:" << endl << "Total reads = "<< list1.read_counter << endl << "Total writes = " << list1.write_counter << endl << "Total page faults = " << list1.page_faults_counter << endl << "Total pages existed = " << list1.page_exists_counter << endl;
	cout << "Process 2:" << endl << "Total reads = "<< list2.read_counter << endl << "Total writes = " << list2.write_counter << endl << "Total page faults = " << list2.page_faults_counter << endl << "Total pages existed = " << list2.page_exists_counter << endl;

}




int main(int argc, char ** argv){

	if(argv[1] == NULL || argv[2] == NULL || atoi(argv[1])<=3){  //check for arguments
		cout<<" Please give page size and number of addresses,number of arguments must be\n exactly two after ./os2 with a space as a separator\nand page number must not be under 4"<<endl;
		exit(1);
	}
	

	lru( atoi(argv[1]), atoi(argv[2])); 
	cout << "Program now terminates.." << endl;
	
}

