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




class Automata:
    
    def __init__(self, name):
        self.name = name
        self.states = []
    
    
    class State:
        
        def __init__(self, index):
            self.index = index
            self.is_final = False
        
        
        class Transition:
            
            def __init__(self, to):
                self.chars = [] 
                self.to = to
            
            
            
            
# typedef struct automata {
# 
#     char name [AUTOMATA_NAME_SIZE];
#     struct state *init;
# 
# } Automata;
# 
# 
# 
# typedef struct state {
# 
#     int index;
#     char final;
#     List *transitions;
#     struct state *next
#                , *prev;
# 
# } State;
# 
# 
# 
# typedef struct transition {
# 
#     State *to;
#     int to_state;
#     List *chars;
# 
# } Transition;




