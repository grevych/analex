
/*

Analizador Léxico
Compiladores
ITESM QRO
Domingo 15 septiembre 2013
Integrantes:
  Ricardo Ivan Valencia
  Gerardo Reyes

Modificacion 1: Sabado 11 Febrero 2012  - Orden, definicion de funciones, lector de automatas
Modificacion 2: Domingo 12 Febrero 2012 - Creacion de automata generalizado

-----------------------------------------------------------------------------------

Analizador Sintáctico LL(1)
Jueves 15 Marzo 2012
Integrantes: 
	Gerardo Reyes
	
	
Analizador Sintáctico SLR(1)
Lunes 16 Mayo 2012
Integrantes:
	Gerardo Reyes
	
	

TODO:
 - URGE CAMBIAR EL ANALEX POR ALGO MENOS MOUNSTROSO, ESTRUCTURAS DINÁMICAS
 - MEJORAR LA LECTURA DE LAS HERRAMIENTAS DEL ANALEX

 
*/







#include "util.h"
#include "lib/ds/stack.h"
#include "lib/ds/list.h"
#include "debugger/debugger.h"
#include "parser/parser.h"






int main (int argc, const char* argv[]){ 
	
	//DEFINIR FORMA DE USO EN LOS PARAMETROS DE ENTRADA
	
    return ( debugger() ) ? 1 :
           ( parser(argv[1]) ) ? 1 :
           0;
	
    // if ( debugger() ) return 1;
    // if ( parser(argv[1]) ) return 1;    // Comienza análisis sintáctico
	
	
    //return 0;
}



