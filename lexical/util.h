
/*
*   Nombres de archivos de lectura de 
*   automatas y lexemas
*/
#define FILE_AUTOMATA "lexical/automatas.in"
#define FILE_LEXEME "lexical/lexemes.in"
#define FILE_SET "lexical/sets.in"



/*
*   Caracteres usados en el archivo
*   de entrada de automatas
*/
#define AUTOMATA_IN_NEW_LINE    '\n'
#define AUTOMATA_IN_COMMENT     '!'
#define AUTOMATA_IN_SPACE       ' '
#define AUTOMATA_IN_TAB         '\t'
#define AUTOMATA_IN_TITLE       '>'
#define AUTOMATA_IN_EMPTY       '#'
#define AUTOMATA_IN_FINAL_STATE '*'



/*
*   Caracteristicas de automata
*/
#define AUTOMATA_NAME_SIZE 50



/*
*   Caracteristicas de lexema
*/
#define LEXEME_NAME_SIZE 50
#define TOKEN_NAME_SIZE 50



/*
*   Caracteristicas de set
*/
#define SET_SIZE 255





/*

SE TIENE QUE HACER GLOBALES PARA LAS VARIABLES DE LOS LEXEMAS ARRAYS
SE TIENE QUE HACER GLOBALES PARA LAS LISTAS DE LOS SETS
PARSER ES EL QUE ABRE EL ARCHIVO
*/





List *automatas;
List *lexemes;
List *sets;







typedef struct lexeme {
    
    char token [TOKEN_NAME_SIZE];
    char name [LEXEME_NAME_SIZE];
    
} Lexeme;





typedef struct set {
    
    char name;
    char chars[SET_SIZE];
    
} Set;







typedef struct automata {
    
    char name [AUTOMATA_NAME_SIZE];
    struct state *init;
    
} Automata;



typedef struct state {
    
    int index;
    char final;
    List *transitions;
    struct state *next
               , *prev;
    
} State;



typedef struct transition {

    State *to;
    int to_state;
    List *chars;

} Transition;










/***************************************************
* Desplegamos lista de automatas, 
* cada grafo despliega sus propios estados y
* estos su lista de transiciones y estas su lista de
* caracteres aceptados o sets.
****************************************************/
void list_display(List *l) {
    NodeList *m;
    NodeList *n;
    NodeList *o;
    Transition *t;
    State *s;
    
    n = l -> head;
    
    while(n) {
        printf("%s\n", ((Automata *)(n -> elem)) -> name);
        s = ((Automata *)(n -> elem)) -> init;
        
        while(s) {
            printf("\t ESTADO: %d FINAL:%d\n", s -> index, s -> final);
            m = s -> transitions -> head;
            
            while(m) {
                t = (Transition *)(m -> elem);
                printf("\t\tA estado -> %d\n", t -> to_state);
                o = t -> chars -> head; 
                
                while(o) {
                    printf("\t\t\tCon char -> %c\n", *((char *)(o -> elem)));
                    o = o -> next;
                }
                
                m = m -> next;
            }
                        
            s = s -> next;
        }
        
        n = n -> next;
    }
    
}



State* get_automata_state(Automata *a, int n) {
    State *s;
    
    s = a -> init;
        
    while(s && n--) s = s -> next;
    
    return s;
    
}

char * get_set_chars(char c) {
    NodeList *n;
    
    n = sets -> head;
    
    while(n) {
        if (c == ((Set *) n -> elem) -> name)
            return ((Set *) n -> elem) -> chars;
        n = n -> next;
    }
    
    return 0;
}




void sort_automatas(List *l) {
    NodeList *m;
    NodeList *n;
    NodeList *o;
    Transition *t;
    State *s;
    
    n = l -> head;
    
    while(n) {
        printf("%s\n", ((Automata *)(n -> elem)) -> name);
        s = ((Automata *)(n -> elem)) -> init;
        
        while(s) {
            printf("\t ESTADO: %d FINAL:%d\n", s -> index, s -> final);
            m = s -> transitions -> head;
            
            while(m) {
                t = (Transition *)(m -> elem);
                t -> to = get_automata_state(((Automata *)(n -> elem)), t -> to_state);
                printf("\t\tA estado -> %d\n", t -> to -> index);
  
                o = t -> chars -> head; 
                
                while(o) {
                    printf("\t\t\tCon char -> %c\n", *((char *)(o -> elem)));
                    o = o -> next;
                }
                
                
                m = m -> next;
            }
                        
            s = s -> next;
        }
        
        
        /*
            Limpiamos prevs y next de estados
        */
        s = ((Automata *)(n -> elem)) -> init;
        
        while((s = s -> next)) {
            printf("\tLIMPIANDO ESTADO: %d\n", s -> prev -> index);            
            s -> prev -> prev = NULL;
            s -> prev -> next = NULL;
            s -> prev = NULL;
        }
        
        n = n -> next;
    }
    
}










