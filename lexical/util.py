

DELIMITERS = r'\s'


#Lexema (nombre, regexp)
LEXEMES = (
    {'name':'AUTO', 'token': r'auto'},
    {'name':'BREAK', 'token': r'break'},
    {'name':'CASE', 'token': r'case'},
    {'name':'CHAR', 'token': r'char'},
    {'name':'CONST', 'token': r'const'},
    {'name':'CONTINUE', 'token': r'continue'},
    {'name':'DEFAULT', 'token': r'default'},
    {'name':'DO', 'token': r'do'},
    {'name':'DOUBLE', 'token': r'double'},
    {'name':'ELSE', 'token': r'else'},
    {'name':'ASIG_SUM', 'token': r'+='},
    {'name':'ASIG_RES', 'token': r'-='},
    {'name':'ASIG_MUL', 'token': r'*='},
    {'name':'ASIG_DIV', 'token': r'/='},
    {'name':'ASIG_MOD', 'token': r'%='},
    {'name':'DIV', 'token': r'/'},
    {'name':'MUL', 'token': r'*'},
    {'name':'SUM', 'token': r'+'},
    {'name':'RES', 'token': r'-'},
    {'name':'MOD', 'token': r'%'},
    {'name':'ASIG', 'token': r'='},
    {'name':'ID', 'token': r'[a-zA-Z0_][\w]*'},

    
)


EXT_LEXEMES = (
    {'name':'STRING', 'token': r'',  'start':r'', 'end':r''},
    {'name':'COMMENT_BL', 'token': r'', 'start':r'', 'end':r''},
    {'name':'COMMENT_LN', 'token': r'', 'start':r'', 'end':r''},
    
)

