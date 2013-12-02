
DELIMITERS = r'\s'


#Lexema (nombre, regexp)
TOKENS = (
    # ('DECIMAL',  r'[+-]?[0-9]*(\.)[0-9]+(E[+-]?[0-9]+)?'),
    # ('ENTERO',  r'[+-]?[0-9]+'),
    # ('AUTO',  r'auto'),
    # ('BREAK',  r'break'),
    # ('CASE',  r'case'),
    # ('CHAR',  r'char'),
    # ('CONST',  r'const'),
    # ('CONTINUE',  r'continue'),
    # ('DEFAULT',  r'default'),
    # ('DO',  r'do'),
    # ('DOUBLE',  r'double'),
    # ('ELSE',  r'else'),
    # ('ASIG_SUM',  r'\+='),
    # ('ASIG_RES',  r'\-='),
    # ('ASIG_MUL',  r'\*='),
    # ('ASIG_DIV',  r'/='),
    # ('ASIG_MOD',  r'%='),
    # ('DIV',  r'/'),
    # ('MUL',  r'\*'),
    # ('SUM',  r'\+'),
    # ('RES',  r'\-'),
    # ('MOD',  r'%'),
    # ('ASIG',  r'='),
    # ('ID',  r'[a-zA-Z0_][\w]*'),
    
    ('INISET',  r'\#set'),
    ('NAMETAG', r'\:'),
    ('SET',     r'set'),
    ('STYLE',   r'style'),
    ('EQUALS',  r'\='),
    ('ENDSET',  r'\#endset'),
    ('LPAR',    r'\('),
    ('RPAR',    r'\)'),
    ('COMMA',   r'\,'),
    ('APOS',    r'\''),
    ('DOTCOMMA',r'\;'),
    ('INITEMP', r'\#template'),
    ('ENDTEMP', r'\#endtemplate'),
    ('ININEST', r'\{\%'),
    ('ENDNEST', r'\%\}'),
    ('FOR',     r'for'),
    ('SELE',    r'\#|\.\w+'),
    ('NUM',     r'[1-9][0-9]*'),
    ('ID',      r'(-|\w)+'),
    ('LKEY',    r'\{'),
    ('RKEY',    r'\}'),


    
)

#r'/\*([^*]|[\s]|(\*+([^*/]|[\s])))*\*+/'


TOKENS_WITH_DELIMITERS = (
#    ('STRING', r'a', r'a'),
    ('COMMENT_BLOCK', r'/\*([^*]|[\s]|(\*+([^/]|[\s])))*\*+/', r'/\*([^*]|[\s]|(\*+([^/]|[\s])))*\*+/'),
    ('COMMENT_BLOCK', r'/\*([^*]|[\s]|(\*+([^/]|[\s])))*\*+/', r'/\*([^*]|[\s]|(\*+([^/]|[\s])))*'),
    ('COMMENT_BLOCK', r'/\*([^*]|[\s]|(\*+([^/]|[\s])))*\*+/', r'/\*'),
#    ('COMMENT_NEW_LINE', r'a', r'a'),
    
)




GRAMMAR = (

    ('A', 'S C'),
    ('S', 'C'),
    ('S', 'iniset nametag id D'),
    ('D', 'set id equals E D'),
    ('D', 'style equals id Y D'),
    ('D', 'endset'),
    ('E', 'set rpar id J'),
    ('Y', 'style lpar apos sele apos J'),
    ('J', 'comma id nametag id J'),
    ('J', 'rpar dotcomma'),
    ('C', 'initemp nametag id T'),
    ('T', 'B endtemp'),
    ('T', 'endtemp'),
    ('B', 'ininest id I'),
    ('B', 'for lpar num comma num rpar lkey B rkey'),
    ('I', 'B endnest'),
    ('I', 'endnest'),


    # ('A', 'id asig E'),
    # ('E', 'T R'),
    # ('R', 'mas E'),
    # ('R', 'epsilon'),
    # ('T', 'F Q'),
    # ('Q', 'mul T'),
    # ('Q', 'epsilon'),
    # ('F', 'id'),
    # ('F', 'cte'),
    
    
    # ('S', 'STAT SPRIM'),
    # ('S', 'WHILE SPRIM'),
    # ('S', 'IF SPRIM'),
    # ('SPRIM', 'S'),
    # ('SPRIM', 'epsilon'),
    # ('STAT', 'var asig TYPE STATPRIM') ,
    # ('STATPRIM', 'OPERATIONS TYPE STATPRIM'),
    # ('STATPRIM', 'puntocoma'),
    # ('TYPE', 'var'),
    # ('TYPE', 'num'),
    # ('WHILE', 'while TYPE compare TYPE llavea S llavec'),
    # ('IF', 'if TYPE compare TYPE llavea S llavec OR'),
    # ('OR', 'or ORPRIM'),
    # ('OR', 'epsilon'),
    # ('ORPRIM', 'llavea S llavec'),
    # ('ORPRIM', 'IF'),
    
    # ('E', 'T Z'),
    # ('Z', 'mas T Z'),
    # ('Z', 'epsilon'),
    # ('T', 'F Y'),
    # ('Y', 'mul F Y'),
    # ('Y', 'epsilon'),
    # ('F', 'parentesisa E parentesisc'),
    # ('F', 'num'),
    
)


