#-*- coding:utf-8 -*-

#import data, automata
#try finally raise except assert

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
        
        if not util.GRAMMAR.__len__():
            print "Error en gramática -> inexistente"
            return
            
        self.__grammar = [{production[0]: production[1]} for production in util.GRAMMAR]
        self.__next = {}
        self.__first = {}
        self.__terminals = []
        self.__nonterminals = []
        self.__parsing_table = []
        
        
        for production in util.GRAMMAR:
            self.__get_first(production[0])
            self.__get_next(production[0])
            
        self.__get_terminals()
        self.__get_nonterminals()
        self.__set_parsing_table()
            
                
        print 'GRAMATICA -> ', self.__grammar
        print 'PRIMEROS -> ', self.__first
        print 'SIGUIENTES -> ', self.__next
        print 'TERMINALES -> ', self.__terminals
        print 'NO TERMINALES -> ', self.__nonterminals
        print '\n\n\nTABLA ->'
        for i in  self.__parsing_table:
            print i
    
    
    
    def __get_terminals(self):
        for production in util.GRAMMAR:
            for element in production[1].split():
                if element.islower() and element not in self.__terminals and element.find('epsilon'):
                    self.__terminals.append(element)
        
        self.__terminals.append('$')
        
        
        
    def __get_nonterminals(self):
        for production in util.GRAMMAR:
            if production[0] not in self.__nonterminals:
                self.__nonterminals.append(production[0])
        
        
        
    def __set_parsing_table(self):
        for nonterminal in self.__nonterminals:  
            self.__parsing_table.append([-1 for terminal in self.__terminals])
            
        index_table = 0
            
        for production in util.GRAMMAR:
            x = self.__nonterminals.index(production[0])
            element = production[1].split()[0]
            
            if not element.find('epsilon'):
                y = [self.__terminals.index(element) for element in self.__next[production[0]] if element != 'epsilon'] #diferente de epsilon
                
                for index in y:
                    if self.__parsing_table[x][index] == -1:
                        self.__parsing_table[x][index] =  'epsilon' #'epsilon'
                    else:
                        print "Error en tabla de parsing__ %d" % (index_table, )
                        return
                        
            elif element in self.__terminals:
                y = self.__terminals.index(element)
                if self.__parsing_table[x][y] == -1:
                    self.__parsing_table[x][y] =  index_table
                else:
                    print "Error en tabla de parsing__ %d" % (index_table, )
                    return
                
            else:
                y = [self.__terminals.index(element) for element in self.__first[production[0]] if element != 'epsilon'] #diferente de epsilon
                
                for index in y:
                    if self.__parsing_table[x][index] == -1:
                        self.__parsing_table[x][index] = index_table
                    else:
                        print "Error en tabla de parsing %d" % (index_table, )
                        return
                        
            index_table = index_table + 1
                        
    
    
    def __get_first(self, key):
        if self.__first.has_key(key):
            return self.__first[key]
        
        self.__first[key] = []
        
        for production in self.__grammar:
            if production.has_key(key):
                elements = production[key].split()
                if elements[0] != key:
                    if elements[0].islower():
                        self.__first[key].append(elements[0])
                    else:
                        epsilons = 0
                        is_epsilon = False
                        
                        for element in elements:
                            for first in self.__get_first(element):
                                if not first.find('epsilon'):
                                    epsilons = epsilons + 1
                                    is_epsilon = True
                                    continue
                                    
                                if not first in self.__first[key]:
                                    self.__first[key].append(first)
                            
                            if not is_epsilon:
                                break
                                
                            is_epsilon = False
                        
                        if epsilons == elements.__len__():
                            if not 'epsilon' in self.__first[key]:
                                self.__first[key].append('epsilon')
                                
        return self.__first[key]
            
        

    def __get_next(self, key):
        if self.__next.has_key(key):
            return self.__next[key]
            
        self.__next[key] = []
        
        if key == util.GRAMMAR[0][0] and '$' not in self.__next[key]:
            self.__next[key].append('$')   
        
        for production in self.__grammar:
            elements = production.values()[0].split()
            index = 0
            
            for element in elements:
                if element.__eq__(key):
                    if index == elements.__len__() - 1:
                        if production.keys()[0] != key:
                            for next in self.__get_next(production.keys()[0]):
                                if next not in self.__next[key]:
                                    self.__next[key].append(next)
                    else:
                        if elements[index + 1].islower():
                            self.__next[key].append(elements[index + 1])
                        else:
                            is_epsilon = False
                            for next in self.__get_first(elements[index + 1]):
                                if not next.find('epsilon'):
                                    is_epsilon = True
                                    continue
                                if next not in self.__next[key]:
                                    self.__next[key].append(next)
                                    
                            if is_epsilon:
                                for next in self.__get_next(production.keys()[0]):
                                    if next not in self.__next[key]:
                                        self.__next[key].append(next)
                        
                index = index + 1
                        
        return self.__next[key]
        



lex = Lexical("prueba", None)
lex.run()
#lex.anasin()

# if lex:
#     print lex
#     pass 
    #lex.run()
info = 'ANALEX'
if __name__ == "__main__":                 
    #print info.__doc__
    pass
    
    
    
    
