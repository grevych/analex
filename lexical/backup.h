/*
*/

void lx_is_token( int * lexeme ) {

  int index = -1;
  char temp[BUFSIZ];
  
  memset(temp, '\0', BUFSIZ);
  strncpy(temp, buffer, i_bff );
  
  while ( ++index < N_LEXEMES ) {
 
    if ( strcmp(temp, lexemes[index][0]) == 0 ) {
       printf("si");
       //debugger(temp,3);
       //debugger(lexemes[index][1],1);
       *lexeme = index ;
       return;
    }
 
  }
  
  
 if ( isdigit(temp[0]) ||
      isalpha(temp[0]) ||
      temp[0] == '-'   ||
      temp[0] == '+') {
             
     debugger(temp,3);
     debugger("i",1);
     *lexeme = 'i';
     return;
 } 
             
  
  return;     
}






/***********************************
  Verifica existencia en conjuntos
***********************************/

int lx_is_set( char c, char t ) {

      /*  printf("Entramos a conjuntos!!!..........\n"); /*DEBUG*/
 
  switch(c) {
     
    case 'D': //nums
         if(isdigit(t)) return 1;
         break;
         
    case 'L': //letras
         if(isalpha(t)) return 1;
         break;
         
    case 'N': //line feed
         if(t == '\n') return 1;
         break;
         
    case 'F': //cualquier caracter - \n
         if(t != '\n') return 1;
         break;
         
    case 'B': //cualquier caracter - *
         if(t != '*') return 1;
         break;
         
    case 'T': //cualquier - "
         if(t != '"') return 1;
         break;
         
    case 'R': //cualquier - '
         if(t != '\'') return 1;
         break;
    
    case 'X': //#
         if(t == '#') return 1;
         break;
         
    default: //conjunto desconocido
         break;
  }
 
 return 0;
}








/***********************************
   Metodo maestro de AUTOMATA
***********************************/

int lx_is ( int in, int status ) {     

 char c;
 int i, j, k,
     end, hit;
 
   /* printf("Entramos automata %d con in:%c, status:%i, buffer:%s\n", i_atm, buffer[i_bff], status, buffer); /* DEBUG */
 
 c = ' ';
 i = status;
 j = k = hit = 0;
 end = ( atm[i_atm][i][ atm_sz[i_atm][0] ][0] == '*' ) ? 1: 0;  
 
   /* printf("Es estado final\n"); /* DEBUG */

 while ( j < atm_sz[i_atm][0]  ) { 
            
   c = atm[i_atm][i][j][k]; 
   
     /* printf("Tabla: %c \n", c); /* DEBUG */
   
   if ( c == ' ' ) { //CREO QUE PODEMOS QUITAR ESTE IF Y TODO LO DE ARRIBA, AL FIN SE VUELVE A EVALUAR :P tambien aumenta j alla
      j++; 
      k = 0;
   } else {
      
        /* printf("Buscamos...\n"); /* DEBUG */
      
      for ( k = 0; k < atm_sz[i_atm][1]; k++ ) { 
         
         c = atm[i_atm][i][j][k];
         
         if ( c == ' ' ) continue;
         
           /* printf("tabla: %c   --  buffer: %c \n", c, buffer[i_bff]); /* DEBUG */
         
         if ( isupper(c) ) 
            hit = ( lx_is_set( c, buffer[i_bff] ) )  ? 1 : 0;
         else 
            hit = ( atm[i_atm][i][j][k] == buffer[i_bff] ) ? 1 : 0;   
         
         if ( hit ) {
         
              /* printf("Encontramos %c \n", buffer[i_bff]); /* DEBUG */
                 
            i_bff++; 
            i = j;                                           
            end = ( atm[i_atm][i][ atm_sz[i_atm][0] ][0] == '*' ) ? 1: 0;
            hit = 0;
            
              /* printf("FIN> index %d  i %d   j %d   k %d\n", i_atm, i, j ,k); /* DEBUG */
            
            return i + 1;   
         }
                  
      }
                      
      j++;
      k = 0;
      
   }          
  
 }
 
 
 if ( end  ) {                                  

         /* printf("Aceptado en automata %d %s \n", i_atm, buffer); /* DEBUG */
   
          
   return 0;
         
 } else {
             
   switch( buffer[0] ) {
     
     case 9:
     case 10:
     case 32:
     case '\0':
          return -1;
          
     default:
          return -2;
   }
   
        /* printf("No aceptado en automata %d  .. avanza \n",i_atm ); /* DEBUG */
    /*  printf("TOKEN NO VALIDO! %s \n", buffer ); /* DEBUG */
   
   // manejo de errores
   //debugger
   
 }
          
}// Fin metodo











/************************************
    Liberamos memoria de lexemas
************************************/

int lx_ut_lexemes() {

 int index = -1;
  
 while ( index++ >= N_AUTOMATAS  ) {
   
   free( lexemes[index][0] );
   free( lexemes[index][1] );
    }
 
 debugger("Completo!", 1);
    return 0;     
}







/************************************
   Liberamos memoria de automatas
************************************/

int lx_ut_automatas() {

  int index = -1, i, j;
  
 while ( index++ >= N_AUTOMATAS  ) {
   for ( i = 0; i < atm_sz[index][0]; i++ ) {
     for ( j = 0; j < atm_sz[index][0] + 1; j++ ) 
         free( atm[index][i][j] );   
     free( atm[index][i] );
   }
   free( atm[index] );
    }
 
 debugger("Completo!", 1);
    return 0;    
}










/************************************************
   Liberamos memoria usada por utiles
*************************************************/

int lx_unload_tools() {
 
 debugger ("  Liberando memoria de autómatas.. ", 3);
 if ( lx_ut_automatas() ) return 1;
 
 debugger ("  Liberando memoria de tokens.. ", 3);
 if ( lx_ut_lexemes() ) return 1;

    return 0;
}





/************************************************
   Carga a memoria utiles que se van a ocupar
*************************************************/

int lx_load_tools() {
 
 debugger ("  Cargando autómatas.. ", 3);
 if ( lx_lt_automatas() ) return 1;
 
 debugger ("  Cargando tokens.. ", 3);
 if ( lx_lt_lexemes() ) return 1;

    return 0;
}





























while ( ( in[index] = fgetc(file) ) != EOF ) { 
        
    switch (in[index]) {
     
        case '\n':
            line++;
            index = 0;
            break;
              
        case '!':
            if (!index) { 
                while( ( in[index] = fgetc(file) ) != '\n' );  //AGREGAR SI ES EOF
                line++; 
                 
            } else { 
                printf("Error en el archivo autómatas en la línea %d\n", &line); //MANDAMOS A DEBUG
                return 1;
            }
            break;
              
        case ' ':
        case '\t':
            break;
              
        case '>':
            while( ( in[index] != '\n'   && 
                     in[index] != ' '    && 
                     in[index] != '\t' ) || 
                     index != 0) {   //AGREGAR SI ES EOF
                        
                if (in[index] == '\n') {
                    printf("%s", in); //MANDAMOS A DEBUG
                    memset(in, '\0', BUFSIZ);
                    index = -1;
                    line++;
                    
                } 
                
                //SI ES ESPACIO O TAB TE QUEDAS CON LO QUE HAY y VERIFICAS QUE PUTA MIERDA ES
                
                index++;
                in[index] = fgetc(file);
            }
            
            printf("\n");
            line++;
            index = 0;
            break;
            
        default:
            printf("Error en el archivo autómatas en la línea %d\n", line);
            return 1;
            break;
            
     }
          
}// Fin de while

