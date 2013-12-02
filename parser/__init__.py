#!/usr/bin/python
#-*- coding:utf-8 -*-

#cambiar permisos chmod +x file.py  



import lexical



    
    # debugger_print(1, "Análisis sintáctico >");
    # if ( lexical(argv) ) return 1;
   



class Parser:
    
    def __init__(self, files, debugger):
        #self.lexical = lexical.Lexical(files) 
        self.lexemes = []
        #self.lexemes = self.lexical.get_lexemes()
        self.debugger = debugger
        
        
    def analize(self):
        #for lexeme in self.lexemes:
         return True 
        
        
        


    def anasin(self):        
        
        if not util.GRAMMAR.__len__():
            print "Error en gramática -> inexistente"
            return
            
        self.__grammar = [{production[0]: production[1]} for production in util.GRAMMAR]
        self.__terminals = []
        self.__nonterminals = []
        self.__parsing_table = []
        self.__first = {}
        self.__next = {}
        
        
        for production in util.GRAMMAR:
            self.__get_first(production[0])
            self.__get_next(production[0])
            
        self.__get_terminals()
        self.__get_nonterminals()
        self.__get_parsing_table()
            
                
        print self.__grammar
        print self.__first
        print self.__next
        print self.__terminals
        print self.__nonterminals
        print self.__parsing_table
    
    
    
    def __get_terminals(self):
        for production in util.GRAMMAR:
            for element in production[1].split():
                if element.islower() and element not in self.__terminals:
                    self.__terminals.append(element)
        
        
        
    def __get_nonterminals(self):
        for production in util.GRAMMAR:
            if production[0] not in self.__nonterminals:
                self.__nonterminals.append(production[0])
        
        
        
    def __get_parsing_table(self):
        for t in self.__terminals:  
            self.__parsing_table.append([None for nt in self.__nonterminals])
            
        
        
        
    
    
    
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
        
        if key == 'A' and '$' not in self.__next[key]:
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
        



info = 'Parser'
if __name__ == "__main__":                 
    print info
    pass
    
    
        
        
        
        
        