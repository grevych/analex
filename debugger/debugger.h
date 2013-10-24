
#include "util.h"


int debugger (){

    debug = fopen( FILE_DEBUG, "w" );   // Archivo de debuggeo
    return debugger_ready();

}



int debugger_ready () {
    
    if ( debug  == NULL ){
		printf("Error al crear el archivo debug..");
		return	1;
	}
	
    return 0;
    
}



void debugger_print( int option, char message [] ) {
    
    if ( debugger_ready() ) {
        return;
    }
    
    
	switch (option) {
		
		case 0:
		     //Imprime en archivo y en consola
		     fprintf(debug, "%s\n", message);
			 printf("%s\n", message);
		     break;
		
		case 1:
		     //Imprime en archivo con salto de linea
			 fprintf(debug, "%s\n", message);
		     break;
		
		case 2:
		     //Imprime en archivo con espacio + salto de linea
			 fprintf(debug, "\t%s\n", message);
		     break;
			 
		case 3:
		     //Imprime en archivo con espacio
			 fprintf(debug, "\t%s", message);
		     break;
			 
		case 4:
		     //Imprime un separador en el archivo
			 fprintf(debug, "\n -------- \n"); 
		     break;
			 
		default:
			break;
			 
	}
	
	
}