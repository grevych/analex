


typedef struct list {  

    int length;
	struct nodeList *head
	              , *tail;

} List;



typedef struct nodeList{         // ALMACENA CARACTERES QUE SE INTRODUCEN EN EL STACK
 
    void *elem;
    struct nodeList *next
                  , *prev;
 
} NodeList;



void list_init (List *l) {
		
	l -> head = l -> tail = NULL;
	l -> length = 0;
			
}

// EL DISPLAY SE HACE DONDE LA CREAS, PARA QUE SEPAS A QUE CONVERTIR
// void list_display (Stack *s) {
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




void list_add (List *l, void *e ) {
    
    NodeList *n = (NodeList *) malloc( sizeof(NodeList) );
    
    if ( !(l -> length)++ ) l -> head = l -> tail = n;
	else {
        
	    l -> tail -> next = n;
	    n -> next = NULL;
        n -> prev = l -> tail;
        l -> tail = n;
	} 
	
    n -> elem = e;
		
}

// 
// void * st_remove(Stack *s) {
//  
//  void *aux;
//  int p;
//  
//  if ( s -> length == 0 ) {
//      printf("ERROR, COLA VACIA NO SE PUEDE REMOVER! \n");
//      return;
//  }
//      
//  // p = s -> head -> c;
//  aux = s -> head;
//  s -> head = ((Node *) s -> head) -> next;
// 
//  (*s).length--;
//  //free(aux);
//  
//  return ((void *) aux);
// 
// }
// 
// 
// void * st_seek(Stack *s) {
//  
//  return s -> head;
//  
// }
// 
// 
// 
// 
// 
// 
// 
// 
// 
