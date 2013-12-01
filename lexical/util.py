
DELIMITERS = r'\s'


#Lexema (nombre, regexp)
TOKENS = (
    ('DECIMAL',  r'[+-]?[0-9]*(\.)[0-9]+(E[+-]?[0-9]+)?'),
    ('ENTERO',  r'[+-]?[0-9]+'),
    ('AUTO',  r'auto'),
    ('BREAK',  r'break'),
    ('CASE',  r'case'),
    ('CHAR',  r'char'),
    ('CONST',  r'const'),
    ('CONTINUE',  r'continue'),
    ('DEFAULT',  r'default'),
    ('DO',  r'do'),
    ('DOUBLE',  r'double'),
    ('ELSE',  r'else'),
    ('ASIG_SUM',  r'\+='),
    ('ASIG_RES',  r'\-='),
    ('ASIG_MUL',  r'\*='),
    ('ASIG_DIV',  r'/='),
    ('ASIG_MOD',  r'%='),
    ('DIV',  r'/'),
    ('MUL',  r'\*'),
    ('SUM',  r'\+'),
    ('RES',  r'\-'),
    ('MOD',  r'%'),
    ('ASIG',  r'='),
    ('ID',  r'[a-zA-Z0_][\w]*'),


    
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
    ('A', 'id asig E'),
    ('E', 'T R'),
    ('R', 'mas E'),
    ('R', 'epsilon'),
    ('T', 'F Q'),
    ('Q', 'mul T'),
    ('Q', 'epsilon'),
    ('F', 'id'),
    ('F', 'cte'),
    
)


