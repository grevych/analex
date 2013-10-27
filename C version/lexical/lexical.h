

#include "util.h"



//Controlador de analizador lexico
int lexical (const char argv []){

    debugger_print(2, "Análisis léxico >");
    source = fopen(argv, "r");
    line = 0;
	
	if ( source == NULL ) {
		debugger_print(1, "Error al leer el archivo fuente.. ");
        return 1;
	}
	
	//Loading tools
    if ( lexical_load_lexemes() ) return 1;
    if ( lexical_load_sets() ) return 1;
    if ( lexical_load_automatas() ) return 1;
    

    

    // debugger_print(4, NULL);
	
    return 0;


 
}




/***************************************************
* Leemos caracter por caracter del archivo fuente 
* hasta encontrar un token válido y se regresa el
* lexema correspondiente, en caso contrario se 
* regresa el lexema establecido como desconocido
* UNKONWN_LEXEME
****************************************************/
int lexical_next_lexeme (char *lexeme) {
    
    int index = 0;                      /* Indice del buffer de lectura del archivo fuente */
    
    char set_name[2]    = {'\0'}        /* Posible nombre de set, temporal */
       , is_lexeme      = 0             /* Bandera para indicar si el token pertenece al lenguaje */
       , is_transition  = 0             /* Bandera para indicar si la comparación de caracteres genera una transición de estado */
       , has_transition = 0             /* Bandera para indicar si el estado consultado ha tenido al menos una transición */
       , in[BUFSIZ]     = {'\0'};       /* Buffer de lectura del archivo fuente */
       
    
    NodeList *node_trans;               /* Nodo de lista genérica para convertir a nodo de transición */
    NodeList *node_char;                /* Nodo de lista genérica para convertir a nodo de caracter */
    NodeList *node_atm;                 /* Nodo de lista genérica para convertir a nodo de autómata */
    Transition *trans;                  /* Apuntador a estructura de transición de estado */
    State *st;                          /* Apuntador a estructura de estado de automata */
    
    
    node_atm = automatas -> head;       /* Obtiene head de lista de automatas */
 
    while (node_atm) {
        
        /* DEBBUG */ printf(">Buscando en automata: %s", ((Automata *)(node_atm -> elem)) -> name); /* */
        st = ((Automata *)(node_atm -> elem)) -> init;
        has_transition = 0;

        while (st) {
            
            /* DEBBUG */ printf("ESTADO: %d FINAL:%d\n", st -> index, st -> final); /* */
            node_trans = st -> transitions -> head;
            
            if (*in == '\0')  in[(index = 0)] = fgetc(source); 
            else if (is_transition) {
                
                if ( in[++index] == '\0') 
                    in[index] = fgetc(source);
            
            } else index = 0;
            
            /* DEBBUG */ printf("en indice:%d caracter:%c-> ", index, in[index]); /* */
            is_transition = 0;

            while (node_trans) {
                
                trans = (Transition *)(node_trans -> elem);
                node_char = trans -> chars -> head;
                is_transition = 0;
                
                while (node_char) {
                    
                    if ( isupper(*((char *)(node_char -> elem))) ) {
                        
                        set_name[0] = in[index];
                        
                        if ( strstr( get_set_chars( *((char *)(node_char -> elem)) ), set_name ) ) {
                            /* DEBBUG */ printf(" @ %c", *((char *)(node_char -> elem))); /* */
                            node_char = NULL;
                            node_trans = NULL;
                            is_transition = 1;
                            has_transition = 1;
                            st = trans -> to;

                        } else {
                            /* DEBBUG */ printf("%c", *((char *)(node_char -> elem))); /* */
                            node_char = node_char -> next;
                            is_transition = 0;

                        }
                        
                    } else if ( in[index] == *((char *)(node_char -> elem)) ) {
                        /* DEBBUG */ printf(" @ %c", *((char *)(node_char -> elem))); /* */
                        node_char = NULL;
                        node_trans = NULL;
                        is_transition = 1;
                        has_transition = 1;
                        st = trans -> to;
                        
                    } else {
                        /* DEBBUG */ printf("%c", *((char *)(node_char -> elem))); /* */
                        node_char = node_char -> next;
                        is_transition = 0;
                        
                    }
                    
                }
                
                /* DEBBUG */ printf(" | "); /* */
                if (node_trans) node_trans = node_trans -> next;
                
            }
            
            is_lexeme = (st -> final && !is_transition && has_transition) ? 1 : 0; 
            st = (!node_trans && !is_transition) ? NULL : st;
             
        }
        
        if (!is_lexeme) {
            /* DEBBUG */ printf("\nNO %s EN: %s\n", in, ((Automata *)(node_atm -> elem)) -> name); /* */

            switch (in[0]) {
                
                case '\n': 
                    line++;
                    
                case ' ':
                
                case '\t':
                    in[0] = '\0';
                    break;
                    
                case EOF:
                    in[0] = '\0';
                    return 0;
                    
                default:
                    node_atm = node_atm -> next;
                    break;
                    
            }

        } else {
            
            if (in[index] != EOF) fseek(source, -1, SEEK_CUR);
            in[index] = '\0';
            /* DEBUG */ printf("\nSI %s EN: %s\n", in, ((Automata *)(node_atm -> elem)) -> name); /* */
            lexeme = in;
            node_atm = NULL;
            
            return 1;
            
        }
        
    }
              
    
    memset(in, '\0', BUFSIZ);
    memcpy(in, "UNKNOWN_LEXEME", 14);
    lexeme = in;
    return 0;
}











/***************************************************
* Leemos automatas de archivo, 
* creamos y cargamos lista de grafos con automatas.
****************************************************/
int lexical_load_automatas() {
    
    FILE *file          = NULL;     /* Puntero a archivo de automatas */
    Automata *atm       = NULL;     /* Elemento automata para referenciar al grafo */
    State *st           = NULL;     /* Estado de automata (renglon en tabla) */
    State *st_head      = NULL;     /* Head de lista de estados simulada*/
    Transition *trans   = NULL;     /* Transicion (caracter o set) de estado */
    char *in_char       = NULL;     /* Char que contiene el caracter aceptado de una transicion*/
    
    char in [BUFSIZ]                    = {'\0'}    /* Buffer de entrada de archivo */
       , at_name[AUTOMATA_NAME_SIZE]    = {'\0'}    /* Nombre de automata */
       , is_comment                     = 0         /* Bandera de comentario en archivo */
       , is_table                       = 0         /* Bandera de tabla de transicion de automata en archivo */
       , is_title                       = 0;        /* Bandera de título de automata en archivo*/

    int line         = 0              /* Numero de linea que se esta leyendo */
      , index        = 0              /* Indice de caracter en el buffer */
      , state_x      = 0              /* Estado al que pasa la transicion */
      , state_y      = 0;             /* Estado en el que estamos leyendo */
     
    automatas = NULL;                 /* Lista de automatas (grafos) */
    
    
    debugger_print(3, "\tCargando autómatas..");

    if ( (file = fopen(FILE_AUTOMATA, "r")) == NULL ) {
        debugger_print(2, "Error al abrir archivo de automatas.. ");
        return 1;
    }
 
    memset(in, '\0', BUFSIZ); 
    automatas = (List *) malloc( sizeof(List) );
    list_init(automatas);
 
    while ( ( in[index] = fgetc(file) ) != EOF ) { 
            
        switch (in[index]) {
         
            case AUTOMATA_IN_NEW_LINE:
                if (is_title) {
                    is_table = 1;
                    is_title = 0;
                    memcpy(at_name, in, AUTOMATA_NAME_SIZE);
                    /* DEBUG/ printf("%s", in); /**/
                    
                } else if (is_table) {  /* Cierre de automata */ 
                    
                    if (!index) {
                        is_table = 0;
                        state_y = 0;
                        atm = NULL;
                        st_head = NULL;
                        
                    } else { /* Cierre o verificacion de cierre de estado y de ultima transicion */
                        
                        if (trans) trans -> to_state = state_x;
                        trans = NULL;
                        st = NULL;
                        state_y++;
                        state_x = 0;
                        /* DEBUG/ printf("STATE: %d\n", state_y); /**/
                        
                    }
                     
                    /* DEBUG/ printf("table: %d  tittle:%d comment:%d",  is_table, is_title, is_comment); /**/
                    /* DEBUG/ printf("%s", in); /**/
                      
                }
                
                line++;
                index = -1;
                is_comment = 0;
                memset(in, '\0', BUFSIZ);
                break;
                  
                  
            case AUTOMATA_IN_COMMENT:
                if (!index) { 
                    is_comment = 1;
                    is_title = 0;
                    is_table = 0;
                    
                } else if (!is_comment && !is_title && !is_table){
                    
                    line++;
                    printf("Error en el archivo autómatas en la línea %d\n", line); /* MANDAR A DEBUGGER */
                    return 1;
                    
                } //else if (is_table){ }Elemento de transicion
                break;
                  
                  
            case AUTOMATA_IN_SPACE:
            case AUTOMATA_IN_TAB:
                if (is_table) { /* Cierre de transicion */ 
                    if (trans) trans -> to_state = state_x;
                    trans = NULL;
                    state_x++;
                    
                }
                break;
                
                  
            case AUTOMATA_IN_TITLE:
                if (!index) is_title = 1;
                else if (!is_comment && !is_title && !is_table) {
                    
                    line++;
                    printf("Error en el archivo autómatas en la línea %d\n", line); /* MANDAR A DEBUGGER */
                    return 1;
                    
                } //else if (is_table) { } ELemento de transicion
                
                /* DEBUG/ printf("+ %s + \n", in); /**/
                break;
               
                
            default:
                if (!is_comment && !is_title && !is_table){
                    line++;
                    printf("Error en el archivo autómatas en la línea %d\n", line); /* MANDAR A DEBUGGER */
                    return 1;
                    
                } else if (is_table){
                    
                    if (!index) { 
                        /* DEBUG/ printf("ESTADO %d\n", state_y); /**/
                        st = (State *) malloc( sizeof(State) );
                        st -> index = state_y;
                        st -> transitions = (List *) malloc( sizeof(List) );
                        st -> next = st -> prev = NULL;
                        list_init(st -> transitions);
                        
                        if (!atm) {
                            /* DEBUG/ in[++index] = '$'; /**/
                            atm = (Automata *) malloc( sizeof(Automata) );
                            memset(atm -> name, '\0', AUTOMATA_NAME_SIZE);
                            memcpy(atm -> name, at_name, AUTOMATA_NAME_SIZE);
                            atm -> init = st;
                            st_head = st;
                            list_add(automatas, (void *) atm);
                            /* DEBUG/ printf("---> %s",atm -> name); /**/
                            
                        } else {
                            st -> prev = st_head;
                            st_head -> next = st;
                            st_head = st;
                            
                        }
                        
                    }
                    
                    if (!trans && in[index] != AUTOMATA_IN_EMPTY && in[index] != AUTOMATA_IN_FINAL_STATE) {
                        trans = (Transition *) malloc( sizeof(Transition) );
                        list_add(st -> transitions, (void *) trans);
                        /* DEBUG/ in[++index] = '$'; /**/
                        
                    }
                    
                    
                    switch(in[index]) {
                        
                        case AUTOMATA_IN_EMPTY:
                            break;
                            
                        case AUTOMATA_IN_FINAL_STATE:
                            st -> final = 1;
                            break;
                        
                        default:
                            if (!(trans -> chars)) {
                                trans -> chars = (List *) malloc( sizeof(List) );
                                list_init(trans -> chars);

                            }
                            
                            in_char = (char *) malloc(1);
                            *in_char = in[index];
                            printf("%c\n", in[index]);
                            list_add(trans -> chars, (void *) in_char);
                            break;
                            
                    }
                    
                }
                break;
                
        }
         
        index++;
              
    }
    
    
    switch (*in) {
        
        case '\0':
        case ' ':
        case '\t':
        case '>':
        case '!':
        case '\n':
            break;
            
        default:
            in[index] = '\0';
            printf("%s", in); //MANDAMOS A DEBUG
            memset(in, '\0', BUFSIZ);
            line++;
            index--;
            break;
            
    }
    
    
    list_display(automatas);
    sort_automatas(automatas);
    
    
    debugger_print(2, "Completo!");
    fclose ( file );
    
    return 0;
 
 
}





/*****************************************
* Leemos lexemas de archivo, 
* creamos y cargamos lista con lexemas.
******************************************/
int lexical_load_lexemes() {
    
    FILE *file;                 /**/
    Lexeme *lxm;
      
    lexemes = NULL;
    lexemes = (List *) malloc( sizeof(List) );
    list_init(lexemes);

    debugger_print(3, "\tCargando lexemas..");
    
    
    if ( (file = fopen(FILE_LEXEME, "r")) == NULL ) {
        debugger_print(0, "Error al abrir archivo de lexemas.. ");
        return 1;
    }

    while ( ! feof(file) ) { 
        
        lxm = (Lexeme *) malloc( sizeof(Lexeme) );
        memset(lxm -> name, '\0', LEXEME_NAME_SIZE);
        memset(lxm -> token, '\0', TOKEN_NAME_SIZE);
        fscanf(file, "%s", lxm -> token );
        fscanf(file, " %s", lxm -> name );

        printf("%s ", lxm -> token); /* DEBUG */
        printf("%s\n ", lxm -> name); /* DEBUG */
        
        list_add(lexemes, (void *) lxm);
    } 
    
    debugger_print(2, "Completo!");
    fclose( file );

    return 0;
    
    
}







/*****************************************
* Leemos sets de archivo, 
* creamos y cargamos lista con sets.
******************************************/
int lexical_load_sets() {
    
    FILE *file;                 /**/
    Set *set;
      
    sets = NULL;
    sets = (List *) malloc( sizeof(List) );
    list_init(sets);

    debugger_print(3, "\tCargando sets..");
    
    
    if ( (file = fopen(FILE_SET, "r")) == NULL ) {
        debugger_print(0, "Error al abrir archivo de sets.. ");
        return 1;
    }

    while ( ! feof(file) ) { 
        
        set = (Set *) malloc( sizeof(Set) );
        set -> name = '\0';
        memset(set -> chars, '\0', SET_SIZE);
        fscanf(file, "%s ", &(set -> name) );
        fscanf(file, " %s", set -> chars );
        
        if (!strcmp(set -> chars, "AUTOMATA_IN_SPACE")) {
            memset(set -> chars, '\0', SET_SIZE);
            set -> chars [0] = AUTOMATA_IN_SPACE;
        } else if (!strcmp(set -> chars, "AUTOMATA_IN_NEW_LINE")) {
            memset(set -> chars, '\0', SET_SIZE);
            set -> chars [0] = AUTOMATA_IN_NEW_LINE; 
        } else if (!strcmp(set -> chars, "AUTOMATA_IN_COMMENT")) {
            memset(set -> chars, '\0', SET_SIZE);
            set -> chars [0] = AUTOMATA_IN_COMMENT;
        } else if (!strcmp(set -> chars, "AUTOMATA_IN_TAB")) {
            memset(set -> chars, '\0', SET_SIZE);
            set -> chars [0] = AUTOMATA_IN_TAB;
        } else if (!strcmp(set -> chars, "AUTOMATA_IN_TITLE")){
            memset(set -> chars, '\0', SET_SIZE);
            set -> chars [0] = AUTOMATA_IN_TITLE;
        } else if (!strcmp(set -> chars, "AUTOMATA_IN_EMPTY")){
            memset(set -> chars, '\0', SET_SIZE);
            set -> chars [0] = AUTOMATA_IN_EMPTY;
        } else if (!strcmp(set -> chars, "AUTOMATA_IN_FINAL_STATE")){
            memset(set -> chars, '\0', SET_SIZE);
            set -> chars [0] = AUTOMATA_IN_FINAL_STATE;
        }
        
        printf("%c ", set -> name); /* DEBUG */
        printf("%s\n ", set -> chars); /* DEBUG */
        
        list_add(sets, (void *) set);
    } 

    debugger_print(2, "Completo!");
    fclose( file );

    return 0;
    
    
}
