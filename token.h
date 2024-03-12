// token.h
typedef struct {
    int tokenID;
    char* tokenInstance;
    int lineNumber;
    int charNumber;
} Token;

enum TokenType {
    ID_TK,
    KEYWORD_TK,
    INT_TK,
    OPERATOR_TK,
    EOF_TK
};