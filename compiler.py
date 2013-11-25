#!/usr/bin/python
#-*- coding:utf-8 -*-

#cambiar permisos chmod +x file.py  


#Versión python
#Compiladores
#ITESM QRO
#Domingo 25 octubre 2013
#Integrantes:
#  Ricardo Ivan Valencia
#  Gerardo Reyes



import config
import debugger
import error
import lexical
import parser



line = None
source = None
syntaxis_tree = None
symbol_table = None



    
#self.options.. 
files = settings.sys.argv[1]
print files
#self.debugger = debugger.Debugger
#self.parser = parser.Parser
    
parser.Parser(files, None)









# 
# 
# int main (int argc, const char* argv[]){ 
#   
#   //DEFINIR FORMA DE USO EN LOS PARAMETROS DE ENTRADA
#   
#     return ( debugger() ) ? 1 :
#            ( parser(argv[1]) ) ? 1 :
#            0;
#   
#     // if ( debugger() ) return 1;
#     // if ( parser(argv[1]) ) return 1;    // Comienza análisis sintáctico
#   
#   
#     //return 0;
# }
# 
# 
# 
