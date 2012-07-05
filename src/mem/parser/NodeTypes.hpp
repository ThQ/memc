#ifndef MEM_PARSER_NODE_TYPES
#define MEM_PARSER_NODE_TYPES

#define MEM_NODE_AND 1
#define MEM_NODE_BINARY 2
#define MEM_NODE_BINARY_ADD 3
#define MEM_NODE_BINARY_SUB 4
#define MEM_NODE_BINARY_MUL 5
#define MEM_NODE_BINARY_DIV 6
#define MEM_NODE_BLOCK 7
#define MEM_NODE_CALL 8
#define MEM_NODE_CLASS 9
#define MEM_NODE_CLASS_DECLARATION 10
#define MEM_NODE_DIV 11
#define MEM_NODE_DOT 12
#define MEM_NODE_EXPR_LIST 13
#define MEM_NODE_FIELD 14
#define MEM_NODE_FILE 15
#define MEM_NODE_FINAL_ID 16
#define MEM_NODE_FUNCTION 17
#define MEM_NODE_FUNCTION_DECLARATION 18
#define MEM_NODE_FUNCTION_PARAMETERS 19
#define MEM_NODE_FUNCTION_PARAMETER 20
#define MEM_NODE_GROUP 21
#define MEM_NODE_ID 22
#define MEM_NODE_IF 23
#define MEM_NODE_IF_ELSE 24
#define MEM_NODE_IF_ELIF 25
#define MEM_NODE_IF_ELIF_ELSE 26
#define MEM_NODE_INTERFACE_DECLARATION 27
#define MEM_NODE_LEFT_UNARY 28
#define MEM_NODE_LITERAL_STRING 29
#define MEM_NODE_LITERAL_INT 30
#define MEM_NODE_LITERAL_NUMBER 31
#define MEM_NODE_MINUS 32
#define MEM_NODE_MUL 33
#define MEM_NODE_NAMESPACE 34
#define MEM_NODE_NEW 35
#define MEM_NODE_NUMBER 36
#define MEM_NODE_POW 37
#define MEM_NODE_OBJECT_DECLARATION 38
#define MEM_NODE_OR 39
#define MEM_NODE_PATCH_DECLARATION 40
#define MEM_NODE_PLACE_HOLDER 41
#define MEM_NODE_PLUS 42
#define MEM_NODE_PRIMITIVE 43
#define MEM_NODE_RETURN 44
#define MEM_NODE_ROOT 45
#define MEM_NODE_SELF 46
#define MEM_NODE_TEXT 47
#define MEM_NODE_VARIABLE 48
#define MEM_NODE_VARIABLE_DECLARATION 49
#define MEM_NODE_USE 50
#define MEM_NODE_WHILE 51

namespace mem { namespace parser {
extern const char* node_names[];
}}

#endif
