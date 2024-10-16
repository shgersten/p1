#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// token struct: will need to print in the form <TYPE, VALUE>
typedef struct {
    char *type;
    char *value;
} Token;

// My DFA to check if the program is in the language
typedef struct {
    //the program
    char *input_string;
    int length; 

    int position;
    char current_char;

    //array of tokens
    Token *tokens;

    //number of token in program
    int token_count;

    //how big a token can be
    int token_capacity;

} LexerDFA;



Token create_token(char *type, char *value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}



void add_token(LexerDFA *lexer, char *type, char *value) {
    
    //resize the amount of tokens the lexer can keep track of if reached capacity
    if (lexer->token_count >= lexer->token_capacity) {
        lexer->token_capacity *= 2;
        lexer->tokens = realloc(lexer->tokens, lexer->token_capacity * sizeof(Token));
    }
    //add the token to the lexers' array of tokens
    lexer->tokens[lexer->token_count++] = create_token(type, value);
}

//shift to the next char after processing
void advance(LexerDFA *lexer) {

    //move to next char for processing
    lexer->position++;

    //check if at the end and null terminate
    if (lexer->position >= strlen(lexer->input_string)) {
        lexer->current_char = '\0';  // End of input
    } else {
        //point to the next char
        lexer->current_char = lexer->input_string[lexer->position];
    }
}



Token identifier(LexerDFA *lexer){

    char *var_name = malloc(100);
    int i = 0;
    while(isalnum(lexer->current_char)){
        var_name[i] = lexer->current_char;
        i++;
        advance(lexer);

    }
    Token result; 
    result.type = "IDENTIFIER";
    result.value = var_name;
    return result;
}

int story_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 5) > lexer->length ){
        return 0;
    }

    char cur = lexer->current_char;
    char n1 = lexer->input_string[lexer->position + 1];
    char n2 = lexer->input_string[lexer->position + 2];
    char n3 = lexer->input_string[lexer->position + 3];
    char n4 = lexer->input_string[lexer->position + 4];
    char n5 = lexer->input_string[lexer->position + 5];

    if(cur == 's' && 
        n1 == 't' && 
        n2 == 'o' && 
        n3 == 'r' && 
        n4 == 'y' && 
        !isalnum(n5) 
    )
     {
        return 1;
     }
     return 0;
}

int room_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 4) > lexer->length ){
        return 0;
    }

    char cur = lexer->current_char;
    char n1 = lexer->input_string[lexer->position + 1];
    char n2 = lexer->input_string[lexer->position + 2];
    char n3 = lexer->input_string[lexer->position + 3];
    char n4 = lexer->input_string[lexer->position + 4];

    if(cur == 'R' && 
        n1 == 'O' && 
        n2 == 'O' && 
        n3 == 'M' && 
        !isalnum(n4) 
    )
     {
        return 1;
     }
     return 0;
}

int while_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 6) > lexer->length ){
        return 0;
    }

    char cur = lexer->current_char;
    char n1 = lexer->input_string[lexer->position + 1];
    char n2 = lexer->input_string[lexer->position + 2];
    char n3 = lexer->input_string[lexer->position + 3];
    char n4 = lexer->input_string[lexer->position + 4];
    char n5 = lexer->input_string[lexer->position + 5];
    
    if(cur == 'w' && 
        n1 == 'h' && 
        n2 == 'i' && 
        n3 == 'l' && 
        n4 == 'e' &&
        !isalnum(n5) 
    )
     {
        return 1;
     }
     return 0;
}

int exits_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 6) > lexer->length ){
        return 0;
    }

    char cur = lexer->current_char;
    char n1 = lexer->input_string[lexer->position + 1];
    char n2 = lexer->input_string[lexer->position + 2];
    char n3 = lexer->input_string[lexer->position + 3];
    char n4 = lexer->input_string[lexer->position + 4];
    char n5 = lexer->input_string[lexer->position + 5];
    
    if(cur == 'e' && 
        n1 == 'x' && 
        n2 == 'i' && 
        n3 == 't' && 
        n4 == 's' &&
        !isalnum(n5) 
    )
     {
        return 1;
     }
     return 0;
}

int END_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 4) > lexer->length ){
        return 0;
    }

    char cur = lexer->current_char;
    char n1 = lexer->input_string[lexer->position + 1];
    char n2 = lexer->input_string[lexer->position + 2];
    char n3 = lexer->input_string[lexer->position + 3];
      
    if(cur == 'E' && 
        n1 == 'N' && 
        n2 == 'D' && 
        !isalnum(n3) 
    )
     {
        return 1;
     }
     return 0;
}

int notHas_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 7) > lexer->length ){
        return 0;
    }

    char cur = lexer->current_char;
    char n1 = lexer->input_string[lexer->position + 1];
    char n2 = lexer->input_string[lexer->position + 2];
    char n3 = lexer->input_string[lexer->position + 3];
    char n4 = lexer->input_string[lexer->position + 4];
    char n5 = lexer->input_string[lexer->position + 5];
    char n6 = lexer->input_string[lexer->position + 6];
      
    if(cur == 'n' && 
        n1 == 'o' && 
        n2 == 't' &&
        n3 == 'H' && 
        n4 == 'a' &&
        n5 == 's' && 
        !isalnum(n6) 
    )
     {
        return 1;
     }
     return 0;
}

int updateExits_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 12) > lexer->length ){
        return 0;
    }

    char cur = lexer->current_char;
    char n1 = lexer->input_string[lexer->position + 1];
    char n2 = lexer->input_string[lexer->position + 2];
    char n3 = lexer->input_string[lexer->position + 3];
    char n4 = lexer->input_string[lexer->position + 4];
    char n5 = lexer->input_string[lexer->position + 5];
    char n6 = lexer->input_string[lexer->position + 6];
    char n7 = lexer->input_string[lexer->position + 7];
    char n8 = lexer->input_string[lexer->position + 8];
    char n9 = lexer->input_string[lexer->position + 9];
    char n10 = lexer->input_string[lexer->position + 10];
    char n11 = lexer->input_string[lexer->position + 11];
    
    if(cur == 'u' && 
        n1 == 'p' && 
        n2 == 'd' && 
        n3 == 'a' && 
        n4 == 't' &&
        n5 == 'e' && 
        n6 == 'E' && 
        n7 == 'x' &&
        n8 == 'i' && 
        n9 == 't' && 
        n10 == 's' &&
        !isalnum(n11)  
    )
     {
        return 1;
     }
     return 0;
}

Token string_lookahead(LexerDFA *lexer){

    // Dynamically allocate memory for the string
    char *str_value = malloc(200); 
    if (!str_value) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    
    
    str_value[index++] = lexer->current_char;
    advance(lexer);
    // Loop until we find the next closing quote or end of input.
    while (lexer->current_char != '"' && lexer->current_char != '\0') {
        
        str_value[index++] = lexer->current_char;
        advance(lexer);

        // Resize array if necessary.
        if (index >= 200) {
            str_value = realloc(str_value, index + 200);
            if (!str_value) {
                fprintf(stderr, "Memory reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    if(lexer->current_char == '"'){
        str_value[index++] = lexer->current_char;
    }
    // If we reach the end of the input without finding a closing quote, syntax error and exit with failure.
    if (lexer->current_char == '\0') {
        fprintf(stderr, "Error: Unterminated string literal\n");
        free(str_value);  // Clean up allocated memory
        exit(EXIT_FAILURE);
    }

    // Move past the closing quote.
    advance(lexer);

    str_value[index] = '\0';  // Null-terminate the string

    // Create and return the token with type STRING and the captured value.
    return create_token("STRING", str_value);
}

void run(LexerDFA *lexer) {
    while (lexer->current_char != '\0') {
        if (isspace(lexer->current_char)) {
            advance(lexer);  // Ignore whitespace
        }  else if (lexer->current_char == '{') {
            add_token(lexer, "LBRACE", "{");
            advance(lexer);
        } else if (lexer->current_char == '}') {
            add_token(lexer, "RBRACE", "}");
            advance(lexer);
        } else if (lexer->current_char == '"') {
            //add_token(lexer, "QUOTE", "\"");
            //advance(lexer);
            Token str = string_lookahead(lexer);
            add_token(lexer, str.type, str.value);
        } else if (lexer->current_char == '.') {
            add_token(lexer, "DOT", ".");
            advance(lexer);
        } else if (story_lookahead(lexer)) {
            add_token(lexer, "STORY", "story");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (room_lookahead(lexer)) {
            add_token(lexer, "ROOM", "room");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (while_lookahead(lexer)) {
            add_token(lexer, "WHILE", "while");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (exits_lookahead(lexer)) {
            add_token(lexer, "EXITS", "exits");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (END_lookahead(lexer)) {
            add_token(lexer, "END", "END");
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (notHas_lookahead(lexer)) {
            add_token(lexer, "NOTHAS", "notHas");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (updateExits_lookahead(lexer)) {
            add_token(lexer, "UPDATEEXITS", "updateExits");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        }else if (isalpha(lexer->current_char)) {
            Token id = identifier(lexer);
            add_token(lexer, id.type, id.value);
        }  else {
            printf("Unexpected character: %c\n", lexer->current_char);
            exit(EXIT_FAILURE);
        }
    }
}

LexerDFA create_lexer(char *input_string) {
    LexerDFA lexer;
    lexer.input_string = input_string;
    lexer.position = 0;
    lexer.current_char = input_string[0];
    lexer.token_count = 0;
    lexer.token_capacity = 100; // start off with being able to have 100 tokens
    lexer.length = strlen(input_string);
    lexer.tokens = malloc(lexer.token_capacity * sizeof(Token));
    if (!lexer.tokens) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return lexer;
}

void free_lexer(LexerDFA *lexer) {
    for (int i = 0; i < lexer->token_count; i++) {
        if (strcmp(lexer->tokens[i].type, "IDENTIFIER") == 0) {
            // Only free dynamically allocated values for integer tokens
            free(lexer->tokens[i].value);
        }
    }
    free(lexer->tokens);  // Free the array of tokens
}

void print_tokens(LexerDFA *lexer) {
    for (int i = 0; i < lexer->token_count; i++) {
        printf("<%s, %s>\n", lexer->tokens[i].type, lexer->tokens[i].value);
    }
}

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory to store the file content
    char *file_content = malloc(file_size + 1);
    if (!file_content) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Read the file into the buffer
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';  // Null-terminate the string

    fclose(file);
    return file_content;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *filename = argv[1];  // Input file containing the program to be tokenized
    char *input_expression = read_file(filename);

    // Create lexer
    LexerDFA lexer = create_lexer(input_expression);

    // Run lexer
    run(&lexer);

    // Print tokens in the required format
    print_tokens(&lexer);

    // Free allocated memory
    //free_lexer(&lexer);
    free(input_expression);

    return 0;
}
