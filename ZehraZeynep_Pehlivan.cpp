#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct node {
	
	struct node *left;
	struct node *midd;
	struct node *right;
	
	int num; 
	int depthLevel;
  };
  
   typedef struct node node;
   
    void generateTree();
    void insert(node * head, int sayi);
    node * remove (node * iter, int sayi);
	node * findMin (node * knot);
	node * findMax (node * knot);
	node * search (node * knot, int key);
	node * parentSearch (node * knot, int key);
	void check(node * knot, int value);
	void checkRight(node * temp, int value);
	void printTree(node * head); 	//inorder

    node *root= (node*)malloc(sizeof(node));  //ROOT NODE
	FILE *fptr;
	node *temp = root;
	node *oldTemp = root; //when iter == temp, to reach parent them
	node * iter = root;   //temp's parent
	node *temp2 = root;


   int main(){
   	
	 root -> left = NULL;  
   	 root -> midd = NULL;  
   	 root -> right = NULL;  
     root -> num = NULL;
	generateTree();

    	printf("WELCOME, PLEASE SELECT WHAT YOU WANT TO DO:");
		    	int choose=0;
		do{
			printf("\n 1.Insertion \n 2.Deletion \n 3.Searching \n 4.Print a tree \n 5.Quit \n");
    		choose;
    		scanf("%d", &choose);
    	
		 	 if(choose ==1) { //insert
		  		int value;
				printf("Please enter a integer you want to insert: ");
    			scanf("%d", &value);
    			insert(root, value);
		  }  	

		  else if(choose ==2) { //remove
		  		int value;
				printf("Please enter a integer you want to remove: ");
    			scanf("%d", &value);
				remove(root, value);
		  }  
		  
		  else if(choose ==3) {  //search
		  		int value;
				printf("Please enter a integer you want to find: ");
    			scanf("%d", &value);
				temp= search(root, value);
				if(temp == NULL) continue;

				printf("\n The depth level of %d is %d.", temp -> num, temp -> depthLevel);
		  }
		   
		  else if(choose ==4) {  //print
		  	printTree(root);
		  } 
	
		  else  {
		  	if(choose!=5) printf("Invalid choose");
		  }
		 	
	   } while(choose != 5);
   }
   
 void generateTree(){
  
 	int x=0;
 	fptr = fopen("./input.txt.txt", "r");  

	while (!(feof(fptr))){
	
	fscanf(fptr, "%d ", &x);
 		insert(root,x);	 

	}
	        fclose(fptr);
	}
 
 void insert(node * head, int sayi){
    
 	temp = head;

	if(temp -> num == NULL){    //first inserting
	 temp -> num = sayi;
	 temp -> depthLevel = 0;
		 return;
	}
 		
 	else if ( sayi < temp -> num ){     //LEFT
 		
 			if(temp -> left != NULL) { 
			 	
						temp = temp -> left;
			  insert(temp, sayi);
		    	return;
			}
			  		  
 				temp -> left = (node*)malloc(sizeof(node));
 				temp -> left -> num = sayi;
	   			temp -> left -> depthLevel = (parentSearch(root, temp -> left-> num) -> depthLevel ) +1 ;

					temp= temp-> left; 
	   	
   	 				temp -> right = NULL; 
 					temp -> left = NULL; 
  					temp -> midd = NULL;  

 						return;
	 }
	
    else if( sayi > temp -> num && (sayi <= (temp -> num)*(temp -> num) )){  //MIDDLE
	  		if(temp -> midd != NULL)  {  
			  
 						temp = temp -> midd;
			  				insert(temp, sayi); 
							  return;
							   }
		  
 		temp -> midd = (node*)malloc(sizeof(node));
 		temp -> midd -> num = sayi;
 		temp -> midd -> depthLevel = (parentSearch(root, temp -> midd -> num) -> depthLevel ) +1 ;

	   	 		temp= temp-> midd; 
			temp -> right = NULL; 
 			temp -> left = NULL; 
  			temp -> midd = NULL; 
	
 				return;
	 }
	
	else if( sayi > (temp -> num)*(temp -> num) ) {  //RIGHT
	 
	  		if(temp -> right != NULL) {  
			  
			temp = temp -> right;
			  insert(temp , sayi); 
			return;
	        }
		  
 		temp -> right = (node*)malloc(sizeof(node));
 		temp -> right -> num = sayi;
 		
 		 		temp -> right -> depthLevel = (parentSearch(root, temp ->right -> num) -> depthLevel ) +1 ;

			temp= temp-> right; 

  			temp -> right = NULL; 
 			temp -> left = NULL; 
  			temp -> midd = NULL; 

				return;
	 }
	 
 }
 
 node * remove (node * head, int key){  

		if(head == NULL) 	return NULL;
     	
     	node * max , *min; //max/min node
     	
		temp = search(head, key);
		if(temp == NULL) return NULL; //this integer not found at tree
		
	    iter = parentSearch(iter, key);  
		    	
       		 if(temp -> left == NULL  && temp -> right == NULL && temp -> midd == NULL){    //key is a leaf
		
				if(iter -> right != NULL && iter -> right-> num == temp -> num )  
					return 	 iter -> right = NULL;
										 
				if(iter -> midd != NULL && iter -> midd-> num == temp -> num) 
					return 	 iter -> midd = NULL;
								
				if(iter -> left!= NULL && iter -> left-> num == temp -> num) 
					return 	 iter -> left = NULL;
					
							
					if(iter == temp)  { 	//free() does not work. It is alternative way 					
					
						if(oldTemp-> right != NULL && oldTemp-> right-> num == temp -> num )  
						return 	 oldTemp -> right = NULL;
										 
						if(oldTemp-> midd != NULL && oldTemp-> midd-> num == temp -> num) 
						return 	 oldTemp -> midd = NULL;
														
						if(oldTemp-> left!= NULL && oldTemp-> left-> num == temp -> num) 
						return 	 oldTemp -> left = NULL;
					
					}

			 } 	
    		   
			 else if(iter-> right!= NULL && iter-> right-> num == temp -> num){  //TEMP ITERIN SAGINDA
			
				if(temp -> left == NULL  && temp -> right != NULL && temp -> midd == NULL)	{         //just right
			
					iter -> right = temp -> right;
		   			free(temp);
	        		return NULL;
			
				}
	
				else if(temp -> left != NULL  && temp -> right == NULL && temp -> midd == NULL) {     //just left

					iter -> right = temp -> left;
					free(temp);
		  			return NULL;
				}
			
				else if(temp -> left == NULL  && temp -> right == NULL && temp -> midd != NULL ){  	   //just middle

					iter -> right= temp -> midd;
					free(temp);
     	  			return NULL;
					
				}
			
				else{    //at least 2 branch
			 		
				 	if(temp-> left != NULL) {

					 max = findMax(temp -> left);
			     	temp -> num= max -> num;
			     	oldTemp = temp; 
			     	temp = temp-> left;
					iter = temp ;  //temp ten sonrakinden aramaya baslasin tekrar max degeri kaldirmak icin 
				 	remove(temp, max -> num);  
				 					 	
				 int checkValue = max -> num;
				 	max = search(root, checkValue) -> midd;
				 	
					iter= max;
				 	check(max, checkValue);
				 	
			    	}
			    
			   		 else{  //midd+ right 		//middle's min
			     	
					min = findMin(temp -> midd);
				 	temp -> num= min -> num;
				 	oldTemp = temp;
					temp= temp-> midd;
					iter= temp ;
				 	remove(temp, min -> num); 
				 	
			    	int checkValue = min -> num;
				 	min = search(root, checkValue) -> right;
				 	
					iter= min;
				 	checkRight(min, checkValue);
				     }
		 	    }	
			}
		
		     else if(iter-> left!= NULL && iter-> left-> num == temp -> num){  //TEMP ITERIN SOLUNDA
					
				 if(temp -> left == NULL  && temp -> right != NULL && temp -> midd == NULL)	{         //just right
			
					iter -> left = temp -> right;
		   			free(temp);
	        		return NULL;
			
			     }

				else if(temp -> left != NULL  && temp -> right == NULL && temp -> midd == NULL) {     //just left
				
					iter -> left = temp -> left;
					free(temp);
		  			return NULL;
				}
			
				else if(temp -> left == NULL  && temp -> right == NULL && temp -> midd != NULL ){  	   //just middle
				
					iter -> left= temp -> midd;
					free(temp);
     	  			return NULL;
					
				}
			
				else{    //at least 2 branch
				
				 	if(temp-> left != NULL) {
				
					max = findMax(temp -> left);
			     	temp -> num= max -> num;
			     	oldTemp = temp;
			     	temp = temp-> left;
			     	iter = temp;
				 	remove(temp, max -> num); 
					 	
				 int checkValue = max -> num;
				max = search(root, checkValue) -> midd;
				 	
					iter= max;
				check(max, checkValue);
				 	

			    	}
			    
			   		 else{  //midd+ right
			    	
			    		//middle's min
			     		min = findMin(temp -> midd);
				 	temp -> num= min -> num;
				 	oldTemp = temp;
					temp= temp-> midd;
					iter= temp;
				 	remove(temp, max -> num); 
			
					int checkValue = min -> num;
				 	min = search(root, checkValue) -> right;
				 	
					iter= min;
				 	checkRight(min, checkValue);
			    	
				     }
		 	    }	
				
			}
		
		     else if(iter-> midd!= NULL && iter-> midd-> num == temp -> num){  //TEMP ITERIN ORTASINDA
				
				if(temp -> left == NULL  && temp -> right != NULL && temp -> midd == NULL)	{         //just right
			
					iter -> midd = temp -> right;
		   			free(temp);
	        		return NULL;
			
				}
	
				else if(temp -> left != NULL  && temp -> right == NULL && temp -> midd == NULL) {     //just left
				
					iter -> midd = temp -> left;
					free(temp);
		  			return NULL;
				}
			
				else if(temp -> left == NULL  && temp -> right == NULL && temp -> midd != NULL ){  	   //just middle
				
					iter -> midd= temp -> midd;
					free(temp);
     	  			return NULL;
					
				}
			
				else{    //at least 2 branch
			 		
				 	if(temp-> left != NULL) {
				
					 max = findMax(temp -> left);
			     	temp -> num= max -> num;
			     	oldTemp = temp;
			     	temp = temp-> left;
			     	iter = temp ; 
				 	remove(temp, max -> num);  
				 	 	
				 int checkValue = max -> num;
				max = search(root, checkValue) -> midd;
				 		
						 iter= max;
					 	check(max, checkValue);
				 	
			    	}
			    
			   		 else{  //midd+ right
			    	
			    		//middle's min
			     	 min = findMin(temp -> midd);
				 	temp -> num= min -> num;
				 	oldTemp = temp;
					temp= temp-> midd;
					iter = temp ; 
				 	remove(temp, max -> num); 
			
			    	int checkValue = min -> num;
				 	min = search(root, checkValue) -> right;
				 	
					iter= min;
				 	checkRight(min, checkValue);
				     }
		 	    }	
			}

		     else if(temp == iter){  //temp == iter and key isnt leaf
		     	//min max problem
		     		if(temp-> left != NULL) {
				
					 max = findMax(temp -> left);
			     	temp -> num= max -> num;
			     	oldTemp = temp;
			     	temp = temp-> left;
			     	iter = temp ; 
				 	remove(temp, max -> num);  
				 		 	
				 	int checkValue = max -> num;
					max = search(root, checkValue) -> midd;
				 	
					iter= max;
				 	check(max , checkValue);

			    	}
			    
			   	    else{  //middle's min
			    	
			     	 min = findMin(temp -> midd);
				 	temp -> num= min -> num;
				 	oldTemp = temp;
					temp= temp-> midd;
					iter = temp ; 
				 	remove(temp, max -> num); 
		
					int checkValue = min -> num;
				 	min = search(root, checkValue) -> right;
				 	
					iter= min;
				 	checkRight(min, checkValue);
				    }
			 }
	}	

 node * search (node * knot, int key){ 

	 temp = knot;
		
		if(key == temp -> num) {   //key imi buldum
		  	return temp;
		}
		
		else if(key < temp -> num){   //key im solda

			if(temp -> left == NULL) {
					printf("THIS VALUE NOT FOUND AT TREE");
					return NULL;
			}
				temp = temp -> left;
				return search(temp, key);
			
		}
    	
    	else if(key > temp -> num && (key <= (temp -> num)*(temp -> num) )){   //key im ortada
				
				if(temp -> midd == NULL) {
					printf("THIS VALUE NOT FOUND AT TREE");
					return NULL;
			}
			
					temp = temp -> midd;
		       return search(temp, key);
		}
		
    	else if(key > (temp -> num)*(temp -> num) ){   //key im sagda

				if(temp -> right == NULL) {
					printf("THIS VALUE NOT FOUND AT TREE");
					return NULL;
			}
			
							temp = temp -> right;
			    return search(temp, key);
			
		}	
	}
	
 node * parentSearch (node * knot, int key){ 

	temp2 = knot;
		if(key == temp2 -> num)   //searching root's parent
		{
			return temp2;
			
		}
		  			
	   else if(key < temp2 -> num){   //key im solda
		 
			
				if(temp2 -> left != NULL && key == temp2 -> left -> num)   return temp2;
				if(temp2 -> midd != NULL && key == temp2 -> midd -> num)   return temp2;
				if(temp2 -> right != NULL && key == temp2 -> right -> num)   return temp2;
			
				temp2 = temp2 -> left;
			return parentSearch(temp2, key);
		}
    	
    	else if(key > temp2 -> num && (key <= (temp2 -> num)*(temp2 -> num) )){   //key im ortada

				if(temp2 -> left != NULL && key == temp2 -> left -> num)   return temp2;

				if(temp2 -> midd != NULL && key == temp2 -> midd -> num)   return temp2;

				if(temp2 -> right != NULL && key == temp2 -> right -> num) return temp2;
				
					temp2 = temp2 -> midd;
		        return parentSearch(temp2, key);
		
		}
		
    	else if(key > (temp2 -> num)*(temp2 -> num) ){   //key im sagda

				if(temp2 -> left != NULL && key == temp2 -> left -> num)   return temp2;
				if(temp2 -> midd != NULL && key == temp2 -> midd -> num)   return temp2;
				if(temp2 -> right != NULL && key == temp2 -> right -> num)  return temp2;
				
					temp2 = temp2 -> right;
		    return parentSearch(temp2, key);
			
		}
		
}
	
 node * findMax (node * knot){

			node * temp= knot;
			
			if(temp -> right != NULL || temp -> midd != NULL){  //sagi veya ortasi dolu
				
				while(temp -> right != NULL || temp -> midd != NULL){
			
				 	while (temp -> right != NULL) { 

			 		 	temp = temp -> right;
			 	 	}
			 	
					 while (temp -> midd != NULL) {

					   	temp = temp -> midd;
			 
		    	  	}	
								
				}
			  return temp;
		   }
		
		   else if(temp -> right == NULL && temp -> midd == NULL ){  //sagi ve ortasi bos

				  return temp;
		   }
			 	
	}
	
 node * findMin (node * knot){
		
		node * temp= knot;
			 while (temp -> left != NULL) {
			 	temp = temp -> left;  
			 }   
				 return temp;
 }
 
 void check(node * temp, int value){
 
		  if(temp -> left != NULL) 	
		    check (temp ->left, value);
			
				if(!(value < temp -> num && temp -> num <= (value*value)) ) {

						remove(iter, temp -> num);
	 					insert(root, temp -> num);
				}
				
   	     if(temp -> midd != NULL) 
		 	check (temp -> midd, value);
 } 
 
 void checkRight(node * temp, int value){
 
 		  if(temp -> left != NULL) 	
		    check (temp ->left, value);
			
				if(!(temp -> num > (value*value)) ) {

						remove(iter, temp -> num);
	 					insert(root, temp -> num);
				}
	 			
   	     if(temp -> midd != NULL) 
		 	check (temp -> midd, value);
 } 
  
 void printTree(node * head){
  	
  		if (head)
    	{
        	printTree(head->left);
        	printf("%d\n",head->num);
        	
         	printTree(head->midd);
			printTree(head->right);
    	}
    
 }
 
