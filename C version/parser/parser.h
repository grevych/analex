

#include "util.h"
#include "../lexical/lexical.h"




//Controlador parser / anasin
int parser(const char argv []) {
    
    debugger_print(1, "Análisis sintáctico >");
    if ( lexical(argv) ) return 1;
    
    lexeme = NULL;
    
    while ( lexical_next_lexeme(lexeme) ) {
       // debugger_print(2, *lexeme);  EL DEBUGGER DEBE RECIBIR UN PUNTERO TIPO VOID PARA CONVERTIRLO DESPUES
        printf("%d\n", lexeme);
    }
    
    
    
    
    return 0;
    
    
    //NO SE TE OLVIDE PONER ESTO AL FINAL!!!!
/*    debugger ("Analisis completo..!!", 1); 
    
    
    
    
    
    
    
    
    
	debugger ("  Cargando herramientas de Analizador Sintáctico..", 1);
	if ( ps_load_tools() ) return 1;
	
	debugger ("  Comienza analisis sintactico..", 1);
	if ( ps_init() ) return 1;
	
	debugger ("  Liberando herramientas de Analizador Sintáctico..", 1);
	if ( ps_unload_tools() ) return 1;
	
	return 0;
	
	
	if ( lexical( 0, NULL ) ) return 1; //Cargamos utilerias de lexico

	char 
		limit = {'$'},
		* action,
		print[BUFSIZ];
	int * lexeme;
	int 
		lx_status = 1,
	 	tb_status = 0;
	
	st_state = ( Stack * ) malloc( sizeof (Stack) );
	st_symbol = ( Stack * ) malloc( sizeof (Stack) );
	action = (char *) malloc (10 * sizeof (char));
	
	st_init(st_state);
	st_init(st_symbol);
	
	st_add( st_state, limit );
	st_add( st_symbol, limit );
	
	st_add(st_state, 0 );
	lexeme = (int *) malloc (sizeof (int));
	* lexeme = 0;
	
	debugger("PILA\t\t\t\t\tCADENA\t\t\tACCION", 1);
	
	while ( lexical(lx_status, lexeme) ) {
		
		//printf("%i------\n ", *lexeme);
		
		st_display(st_state);
		st_display(st_symbol);
	
		action = tb_slr[tb_status][*lexeme];			//Obtenemos cadena de tabla correspondiente
		
		memset(print,'\0',BUFSIZ);
		sprintf(print,"%d", *lexeme );
		debugger(print,3);
		
		if ( ! strcmp(action, "#") ) {
			debugger("ERROR", 1);
			return 1;
		}
		
		
		if (! strcmp(action, "*") ) {
			debugger("ACEPTADA", 1);
			return 0;
		}
		
		
		if ( isalpha(action[0]) )
			if ( action[0] == 'r' ){
				st_remove(st_state);
				st_remove(st_symbol);
				*lexeme = gm_prod[atoi(action + 1)] ;
				debugger(action, 1);
				lx_status = -1;
				tb_status = st_seek(st_state);
				
			}
			else {
				st_add(st_symbol, *lexeme);
				tb_status = atoi(action + 1);
				st_add(st_state,tb_status );
				debugger(action, 1);
				lx_status = 1;
			}
			
			
		if ( isdigit(action[0]) ){
			st_add(st_symbol, *lexeme);
			tb_status = atoi(action);
			st_add(st_state,tb_status );
			lx_status = 1;
		}
			
			
			
	}
	
	
	
	if ( lexical ( 2, NULL ) ) return 1; //Descargamos utilerias de lexico
	
	return 0;
*/
}













/************************************************
   Liberamos memoria tabla SLR1
*************************************************/

int ps_ut_tabla() {
	
	
	
	
	return 0;
}







/************************************************
   Liberamos vector de simbolos
*************************************************/

int ps_ut_simbolos() {
	
	
	
	
	
	return 0;
}







/************************************************
   Liberamos vector de producciones
*************************************************/

int ps_ut_producciones() {
	
	
	return 0;
}












/************************************************
   Cargando tabla SLR1
*************************************************/

int ps_lt_tabla() {
	
	
	
	
	return 0;
}







/************************************************
   Cargando vector de simbolos
*************************************************/

int ps_lt_simbolos() {
	
	
	
	
	
	return 0;
}







/************************************************
   Cargamos vector de producciones
*************************************************/

int ps_lt_producciones() {
	
	
	return 0;
}








/************************************************
   Liberamos memoria usada por utiles
*************************************************/

int ps_unload_tools() {
	
	debugger ("  Liberando memoria de tabla.. ", 3);
	if ( ps_ut_tabla() ) return 1;
	
	debugger ("  Liberando memoria de simbolos.. ", 3);
	if ( ps_ut_simbolos() ) return 1;
	
	debugger ("  Liberando memoria de producciones.. ", 3);
	if ( ps_ut_producciones() ) return 1;
	
    return 0;
}





/************************************************
   Carga a memoria utiles que se van a ocupar
*************************************************/

int ps_load_tools() {
	
	debugger ("  Cargando tabla SLR1.. ", 3);
	if ( ps_lt_tabla() ) return 1;
	
	debugger ("  Cargando vector de simbolos.. ", 3);
	if ( ps_lt_simbolos() ) return 1;
	
	debugger ("  Cargando vector de producciones.. ", 3);
	if ( ps_lt_producciones() ) return 1;


    return 0;
}
