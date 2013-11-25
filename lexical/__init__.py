#-*- coding:utf-8 -*-

#import data, automata


import sys
import re
import util



class Lexical:
    
    def __init__(self, filenames, debugger):
        self.source = None #sources
        self.filenames = filenames

        try:
            self.source = open(self.filenames) # or "a+", whatever you need
            
        except IOError:
            print "Could not open file!"
            #mandar llamar instancia de error y terminar
        
        self.line = 0
        self.status = ""
        self.flags = {}
        self.debugger = debugger
        self.lexemes_re = [re.compile(lxm['token']) for lxm in LEXEMES]
        self.lexemes_ext_re = [re.compile(lxm['token']) for lxm in LEXEMES_EXT]
        #self.debugger.print_msg("Análisis léxico >")
        
        
    def run(self):
        with self.source:
            buffer_str = ""
            
            for char in iter(lambda: self.source.read(1), ''):
                sys.stdout.write(char)
                
    






    #try finally raise except assert



lex = Lexical("prueba", None)

if lex:
    print lex
    pass 
    #lex.run()

if __name__ == "__main__":                 
    print info.__doc__

    
    
    
    
