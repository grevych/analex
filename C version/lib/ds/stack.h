
typedef struct stack {   // STACK

	void * head;
    int length;
	
} Stack;

typedef struct node{         // ALMACENA CARACTERES QUE SE INTRODUCEN EN EL STACK
 
 struct node *next;
 
} Node;




void st_init (Stack *s) {
		
	s -> head = NULL;
	s -> length = 0;
			
}


// void st_display (Stack *s) {
//  
//  char print[BUFSIZ];
//  Node * aux;
//  aux = (*s).head;    
//  
//  
//  while ( aux != NULL ) {
//      memset(print,'\0',BUFSIZ);
//      sprintf(print,"%d", (*aux).c );
//      debugger(print,3);
//      aux = aux -> next;
//  }
// 
//  debugger(" ", 3);
//  free (aux);
// 
// }


void st_add (Stack *s, void * n ) {

    // Node *n = (Node *) malloc( sizeof (Node) );
    // n -> next = NULL;
    // (*n).c = p;
    
	(*s).length++;
	
	if ( (*s).length == 1 ) 
		s -> head = n;
	else {

		((Node *) n) -> next = s -> head;
		s -> head = n;
		
	} 
		
}


void * st_remove(Stack *s) {
	
	void *aux;
	int p;
	
	if ( s -> length == 0 ) {
		printf("ERROR, COLA VACIA NO SE PUEDE REMOVER! \n");
		return;
	}
		
	// p = s -> head -> c;
	aux = s -> head;
	s -> head = ((Node *) s -> head) -> next;

	(*s).length--;
	//free(aux);
	
	return ((void *) aux);

}


void * st_seek(Stack *s) {
	
	return s -> head;
	
}











