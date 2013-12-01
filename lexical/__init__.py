#-*- coding:utf-8 -*-

#import data, automata


import sys
import re
import util

from collections import namedtuple


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
        
        
        TokenWithDelimiter = namedtuple('Token', ('name', 'regexp', 'regexp_at_start', ))
        Token = namedtuple('Token', ('name', 'regexp', ))
        
        self.tokens = [Token(
                            token[0], 
                            re.compile(token[1])) for token in util.TOKENS]
                            
        self.tokens_with_del = [TokenWithDelimiter(
                                    token[0], 
                                    re.compile(token[1]), 
                                    re.compile(token[2])) for token in util.TOKENS_WITH_DELIMITERS]
        #self.debugger.print_msg("Análisis léxico >")
        self.t = []
        
        
    def run(self):
        with self.source:
            buffer_str = ""
            buffer_str_del = ""
            is_token_with_del = False

            for char in iter(lambda: self.source.read(1), ''):
                #sys.stdout.write(char)
 
                if not char.isspace():
                    buffer_str += char
                    continue
                    
                
                
                if is_token_with_del:
                    buffer_str_del += buffer_str + char
                    
                    for token in self.tokens_with_del:
                        match = token.regexp.match(buffer_str_del)
                        
                        if match:
                            print match.group()
                            self.t.append(token.name)
                            buffer_str_del = buffer_str = ""
                            break
                else:
                    
                    for token in self.tokens_with_del:
                        match = token.regexp_at_start.match(buffer_str)
                        
                        if match:
                            print match.group() + " NUEVO EN DELIM"
                            is_token_with_del = True
                            buffer_str_del = buffer_str
                            buffer_str = ""
                            break
                            
                        is_token_with_del = False
                    
                    if not is_token_with_del:
                        for token in self.tokens:
                            match = token.regexp.match(buffer_str)

                            if match:
                                print match.group() + " NUEVO"
                                self.t.append(token.name)
                                buffer_str = ""
                                break
                
                print buffer_str + "|ACEPTADO?"

        print self.t



    def anasin(self):        
        #primeros y siguientes
        if not util.GRAMMAR.__len__():
            #error no existe gramatica
            return
            
        self.grammar = [{production[0]: production[1]} for production in util.GRAMMAR]
        self.first = {}
        self.next = {}
        
        
        for production in util.GRAMMAR:
            self.get_first(production[0])
            self.get_next(production[0])
            
                
        print self.grammar
        print self.first
        print self.next
    #try finally raise except assert
    
    
    
    def get_first(self, key):
        if self.first.has_key(key):
            return self.first[key]
        
        self.first[key] = []
        
        for production in self.grammar:
            if production.has_key(key):
                elements = production[key].split()
                if elements[0] != key:
                    if elements[0].islower():
                        self.first[key].append(elements[0])
                    else:
                        epsilons = 0
                        is_epsilon = False
                        
                        for element in elements:
                            for first in self.get_first(element):
                                if not first.find('epsilon'):
                                    epsilons = epsilons + 1
                                    is_epsilon = True
                                    continue
                                    
                                if not first in self.first[key]:
                                    self.first[key].append(first)
                            
                            if not is_epsilon:
                                break
                                
                            is_epsilon = False
                        
                        if epsilons == elements.__len__():
                            if not 'epsilon' in self.first[key]:
                                self.first[key].append('epsilon')
                                
        return self.first[key]
            
        

    def get_next(self, key):
        if self.next.has_key(key):
            return self.next[key]
            
        self.next[key] = []
        
        if key == 'A' and '$' not in self.next[key]:
            self.next[key].append('$')   
        
        for production in self.grammar:
            elements = production.values()[0].split()
            index = 0
            
            for element in elements:
                if element.__eq__(key):
                    if index == elements.__len__() - 1:
                        if production.keys()[0] != key:
                            for next in self.get_next(production.keys()[0]):
                                if next not in self.next[key]:
                                    self.next[key].append(next)
                    else:
                        if elements[index + 1].islower():
                            self.next[key].append(elements[index + 1])
                        else:
                            is_epsilon = False
                            for next in self.get_first(elements[index + 1]):
                                if not next.find('epsilon'):
                                    is_epsilon = True
                                    continue
                                if next not in self.next[key]:
                                    self.next[key].append(next)
                                    
                            if is_epsilon:
                                for next in self.get_next(production.keys()[0]):
                                    if next not in self.next[key]:
                                        self.next[key].append(next)
                        
                index = index + 1
                        
        return self.next[key]
        



lex = Lexical("prueba", None)
lex.run()
lex.anasin()

# if lex:
#     print lex
#     pass 
    #lex.run()
info = 'ANALEX'
if __name__ == "__main__":                 
    #print info.__doc__
    pass
    
    
    
    
