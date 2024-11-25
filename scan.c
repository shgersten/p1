#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ROOM_ID_LENGTH     256
#define DESCRIPTION_LENGTH 1024

/*
Program -> RoomDeclarations startingItems { Items }

RoomDeclarations -> epsilon | RoomDeclaration RoomDeclarations

RoomDeclaration -> ROOM id { story "STRING" items { Items } exits { ExitOptions } }

Items-> epsilon | id Items

ExitOptions -> epsilon | id ExitOptions

Terminals:
ROOM
id
{
}
story
STRING
exits
epsilon
*/

enum TokenType{
    IDENTIFIER,
    ROOM,
    STRING,
    LBRACE, 
    RBRACE, 
    EXITS, 
    ITEMS, 
    STORY, 
    END, 
    STARTINGITEMS 
};

// token struct: will need to print in the form <TYPE, VALUE>
typedef struct {
    enum TokenType type;
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


char *toString(enum TokenType t);

struct Program;
void print_Program(struct Program *);

struct RoomDeclarations;
void print_RoomDeclarations(struct RoomDeclarations *);

struct RoomDeclaration;
void print_RoomDeclaration(struct RoomDeclaration *);

struct ExitOptions;
void print_ExitOptions(struct ExitOptions *);

struct Items_parse_result;
struct Items;
void print_Items(struct Items *items);

struct Program_parse_result program_parse(Token *tokens, int num_tokens, int cur);
struct RoomDeclaration_parse_result parse_RoomDeclaration(Token * tokens, int num_tokens, int cur);
struct RoomDeclarations_parse_result parse_RoomDeclarations(Token * tokens, int num_tokens, int cur);
struct ExitOptions_parse_result parse_ExitOptions(Token *tokens, int num_tokens, int cur);

struct Items_parse_result parse_Items(Token *tokens, int num_tokens, int cur);
struct ExitOptions_parse_result;
struct RoomDeclaration_parse_result;
struct Program_parse_result;

struct Program {
    struct RoomDeclarations *roomDeclarations;
    struct Items *starting_items;
};

                //0   1
enum Result {SUCCESS, FAIL};

char * result_toString(enum Result r){
    if(r == SUCCESS)
    {return "SUCCESS";}

   
    return "FAIL";

}

struct ExitOptions_parse_result{
    enum Result result;
    struct ExitOptions *exitOptions;
    int tokens_consumed;
};

struct Items_parse_result {
    enum Result result;
    struct Items *items;
    int tokens_consumed;

};

struct Items {
    enum { EMPTY_ITEMS, NONEMPTY_ITEMS } kind;
    char *firstItemID;
    struct Items *rest;
};


struct RoomDeclarations {
    enum { EMPTY_DECLS, NONEMPTY_DECLS } kind;
    struct RoomDeclaration * first;
    struct RoomDeclarations * rest;
};

struct RoomDeclaration {
    char* roomId;
    char* description;
    struct Items *items;
    struct ExitOptions *exitOptions;
};

struct ExitOptions {
    enum { EMPTY_OPTS, NONEMPTY_OPTS } kind;
    char *firstRoomId;
    struct ExitOptions * rest;
};

struct RoomDeclaration_parse_result {
    enum Result result;
    struct RoomDeclaration *roomDeclaration;
    int tokens_consumed;
};

struct RoomDeclarations_parse_result {
    enum Result result;
    struct RoomDeclarations *roomDeclarations;
    int tokens_consumed;
};

struct Program_parse_result{
    enum Result result;
    struct Program *program;
    int tokens_consumed;
};

struct Program_parse_result program_parse(Token *tokens, int num_tokens, int cur) 
{
    //Program -> RoomDeclarations startingItems { Items }

    struct RoomDeclarations_parse_result room_result;
    struct Items_parse_result st_items_result;
    room_result = parse_RoomDeclarations(tokens, num_tokens, cur);

    if(room_result.result == SUCCESS && 
        tokens[room_result.tokens_consumed].type == STARTINGITEMS &&
        tokens[room_result.tokens_consumed + 1].type == LBRACE ){
        
        st_items_result = parse_Items(tokens, num_tokens, room_result.tokens_consumed + 2);

        if(st_items_result.result == SUCCESS &&
            tokens[room_result.tokens_consumed + 2 + st_items_result.tokens_consumed].type == RBRACE){



            struct Program *p = malloc(sizeof(struct Program));
            p->roomDeclarations = room_result.roomDeclarations;
            p->starting_items = st_items_result.items;
            struct Program_parse_result p_res;
            p_res.result = SUCCESS;
            p_res.program = p;
            p_res.tokens_consumed = room_result.tokens_consumed + 2 + st_items_result.tokens_consumed + 1;
        return p_res;
    }
        }
    struct Program_parse_result fail;
    fail.result = FAIL;
    printf("failed at point program_parse\n");
    return fail;
}

void print_Program(struct Program *program) {
    printf("\nProgram:\n");
    print_RoomDeclarations(program->roomDeclarations);
    printf("\tStarting Items: "); print_Items(program->starting_items); printf("\n");
    printf("\n\n");
}

/*
program:
    roomDec
        story
        items
        exits
    roomDec
        story
        items
        exits
    startingItems
        items

*/


void print_RoomDeclarations(struct RoomDeclarations *roomDeclarations) {
    switch (roomDeclarations->kind) {
        case EMPTY_DECLS:
            break;

        case NONEMPTY_DECLS:
            print_RoomDeclaration(roomDeclarations->first);
            printf("\n");
            print_RoomDeclarations(roomDeclarations->rest);
            break;
    }
}

void print_RoomDeclaration(struct RoomDeclaration *roomDeclaration) {
    printf("\troomDec:\n");
    printf("\t\troomID: %s\n", roomDeclaration->roomId);
    printf("\t\tSTORY: %s\n", roomDeclaration->description);
    printf("\t\troomItems: "); print_Items(roomDeclaration->items); printf("\n");
    printf("\t\texits: "); print_ExitOptions(roomDeclaration->exitOptions); printf("\n");

}

void print_ExitOptions(struct ExitOptions *exitOptions) {
    switch (exitOptions->kind) {
        case EMPTY_OPTS:
            break;

        case NONEMPTY_OPTS:
            printf("%s ", exitOptions->firstRoomId);
            print_ExitOptions(exitOptions->rest);
            break;
    }
}

void print_Items(struct Items *items) {
    switch (items->kind) {
        case EMPTY_ITEMS:
            break;

        case NONEMPTY_ITEMS:
            printf("%s ", items->firstItemID);
            print_Items(items->rest);
            break;
    }
}






Token create_token(enum TokenType type, char *value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

struct RoomDeclaration_parse_result parse_RoomDeclaration(Token * tokens, int num_tokens, int cur) {

    if (
        //function to check if:    ROOM id { story string exits { ExitOptions } }

        num_tokens >= cur + 6 &&

        tokens[cur + 0].type == ROOM &&
        tokens[cur + 1].type == IDENTIFIER &&
        tokens[cur + 2].type == LBRACE &&
        tokens[cur + 3].type == STORY &&
        tokens[cur + 4].type == STRING &&
        tokens[cur + 5].type == ITEMS &&
        tokens[cur + 6].type == LBRACE
    ) 
    //parsing items
   // items success
   {
    struct Items_parse_result items_res = parse_Items(tokens, num_tokens, cur + 7);
    //SUCCESS - it has items
        //RBRACE at end of items
       
          if (
            items_res.result == SUCCESS &&

            (cur + 7 + items_res.tokens_consumed + 1 <= num_tokens) &&

            ((tokens[cur + 6 + items_res.tokens_consumed + 1].type) == RBRACE) &&
            ((tokens[cur + 6 + items_res.tokens_consumed + 2].type) == EXITS) &&
            ((tokens[cur + 6 + items_res.tokens_consumed + 3].type) == LBRACE) )  {

         
            struct ExitOptions_parse_result parse_res = parse_ExitOptions(tokens, num_tokens, cur + 7 + items_res.tokens_consumed + 3);

            if( parse_res.result == SUCCESS && 
                 tokens[cur + 6 + items_res.tokens_consumed + 3 + parse_res.tokens_consumed + 1].type == RBRACE && 
                 tokens[cur + 6 + items_res.tokens_consumed + 3 + parse_res.tokens_consumed + 2].type == RBRACE )
            {
                //SUCCESS - it has exit options
                //RBRACE at end of ExitOptions
               

            struct RoomDeclaration * r = malloc(sizeof(struct RoomDeclaration));
            r -> roomId = tokens[cur + 1].value;
            r -> description = tokens[cur + 4].value;
            r->items = items_res.items;
            r -> exitOptions = parse_res.exitOptions;


            struct RoomDeclaration_parse_result result;
            result.result = SUCCESS;
            result.roomDeclaration = r; 
            result.tokens_consumed = 7 + items_res.tokens_consumed + 3 + parse_res.tokens_consumed + 2;

            return result;
            } 
            
        }

   }
    struct RoomDeclaration_parse_result err;
    err.roomDeclaration = NULL;
    err.result = FAIL;
    err.tokens_consumed = 0;
    printf("Failed to create a Room Declaration. Incomplete/Missing variables\nA Room must have story, items, exits and there must be a 'startingItems' array\n");
    return err;
    
} //end function

//plural
struct RoomDeclarations_parse_result parse_RoomDeclarations(Token * tokens, int num_tokens, int cur) {
    //finished parsing
    if( tokens[cur].type == STARTINGITEMS)  //no rooms left in the program to parse
    {
        struct RoomDeclarations *room_dec = malloc(sizeof(struct RoomDeclarations));
        room_dec->kind = EMPTY_DECLS;

        struct RoomDeclarations_parse_result result;
        result.result = SUCCESS;
        result.roomDeclarations = room_dec;
        result.tokens_consumed = 0;
        return result;
    }
    //nonempty, tokens to consume
    //roomDeclarations to parse so first parse singluar then plural

    //parse one room
    struct RoomDeclaration_parse_result room_parse = parse_RoomDeclaration(tokens, num_tokens, cur);
    if(room_parse.result == SUCCESS){
    
        struct RoomDeclarations_parse_result rest_result = parse_RoomDeclarations(tokens, num_tokens, cur + room_parse.tokens_consumed);
        if(rest_result.result == SUCCESS){
            
            struct RoomDeclarations *room_dec = malloc(sizeof(struct RoomDeclarations));
            room_dec->kind = NONEMPTY_DECLS;
            room_dec->first = room_parse.roomDeclaration;
            room_dec->rest = rest_result.roomDeclarations;
            
            struct RoomDeclarations_parse_result result;
            result.result = SUCCESS;
            result.roomDeclarations = room_dec;
                                        //first                     //all the rest unknown amount
            result.tokens_consumed = room_parse.tokens_consumed + rest_result.tokens_consumed ;
            return result;        
        }

    }

    struct RoomDeclarations_parse_result fail;
    fail.result = FAIL;
    printf("failed at parse_RoomDeclarations \n");
    return fail;
} //end function

struct ExitOptions_parse_result parse_ExitOptions(Token *tokens, int num_tokens, int cur){
    
    //no token to get


    if(cur >= num_tokens){
        struct ExitOptions_parse_result err;
        err.exitOptions = NULL;
        err.result = FAIL;
        err.tokens_consumed = 0;
        printf("failed - no tokens to get in parse_ExitOptions\n");
        return err;
    }

    Token cur_token = tokens[cur];
    if(cur_token.type == RBRACE)
    {
        //printf("Reached an 'R brace'.\nThere are no exit options\nExiting this iteration of parse_ExitOptions...\n\n");
        //ending of exit options - empty
        struct ExitOptions *e = malloc(sizeof(struct ExitOptions));
        e->kind = EMPTY_OPTS; 
        struct ExitOptions_parse_result res;
        res.exitOptions = e;
        res.tokens_consumed = 0;
        res.result = SUCCESS;

        return res;   
    }
    
    // case where there are exit options
    if(cur_token.type == IDENTIFIER){
        //{ roomA roomB ...}

        struct ExitOptions *e = malloc(sizeof(struct ExitOptions));
        e->firstRoomId = cur_token.value;
        e->kind = NONEMPTY_OPTS;
        struct ExitOptions_parse_result r =  parse_ExitOptions(tokens, num_tokens, cur+1);
        if(r.result == SUCCESS)
        {
            e->rest = r.exitOptions;
            struct ExitOptions_parse_result res_par;
            res_par.exitOptions = e;
            res_par.result = SUCCESS;
            res_par.tokens_consumed = 1 + r.tokens_consumed; //potential off by one
            return res_par;
        }
    }

    //if not exit options, the catch all
    //parse error
    struct ExitOptions_parse_result parse_else;
    parse_else.exitOptions = NULL;
    parse_else.result = FAIL;
    parse_else.tokens_consumed = 0;
    printf("unexpected token: %s\n", toString(cur_token.type));
    return parse_else;
}



struct Items_parse_result parse_Items(Token *tokens, int num_tokens, int cur){
    
    //no token to get

    if(cur >= num_tokens){
        struct Items_parse_result err;
        err.items = NULL;
        err.result = FAIL;
        err.tokens_consumed = 0;
        printf("failed - no tokens to get in parse_ExitOptions\n");
        return err;
    }

    Token cur_token = tokens[cur];
    if(cur_token.type == RBRACE)
    {
        //printf("Reached an 'R brace'.\nThere are no items \nExiting this iteration of parse_Items...\n\n");
        //ending of exit options - empty
        struct Items *e = malloc(sizeof(struct Items));
        e->kind = EMPTY_OPTS; 
        struct Items_parse_result res;
        res.items = e;
        res.tokens_consumed = 0;
        res.result = SUCCESS;

        return res;   
    }
    
    // case where there are exit options
    if(cur_token.type == IDENTIFIER){
        //{ itemA itemB ...}

        struct Items *e = malloc(sizeof(struct Items));
        e->firstItemID = cur_token.value;
        e->kind = NONEMPTY_ITEMS;
        struct Items_parse_result r =  parse_Items(tokens, num_tokens, cur+1);
        if(r.result == SUCCESS)
        {
            e->rest = r.items;
            struct Items_parse_result res_par;
            res_par.items = e;
            res_par.result = SUCCESS;
            res_par.tokens_consumed = 1 + r.tokens_consumed; //potential off by one
            return res_par;
        }
    }

    //if not exit options, the catch all
    //parse error
    struct Items_parse_result parse_else;
    parse_else.items = NULL;
    parse_else.result = FAIL;
    parse_else.tokens_consumed = 0;
    printf("unexpected token: %s\n", toString(cur_token.type));
    return parse_else;
}


void add_token(LexerDFA *lexer, enum TokenType type, char *value) {
    
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
    result.type = IDENTIFIER;
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


int items_lookahead(LexerDFA *lexer){

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

    if(cur == 'i' && 
        n1 == 't' && 
        n2 == 'e' && 
        n3 == 'm' && 
        n4 == 's' && 
        !isalnum(n5) 
    )
     {
        return 1;
     }
     return 0;
}
int startingItems_lookahead(LexerDFA *lexer){

    //position = 10
    //length = 11
    if( (lexer->position + 13) > lexer->length ){
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
    char n12 = lexer->input_string[lexer->position + 12];
    char n13 = lexer->input_string[lexer->position + 13];

    if(cur == 's' && 
        n1 == 't' && 
        n2 == 'a' && 
        n3 == 'r' && 
        n4 == 't' && 
        n5 == 'i' && 
        n6 == 'n' && 
        n7 == 'g' && 
        n8 == 'I' && 
        n9 == 't' && 
        n10 == 'e' && 
        n11 == 'm' && 
        n12 == 's' && 
        !isalnum(n13) 
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
    return create_token(STRING, str_value);
}

void run(LexerDFA *lexer) {
    while (lexer->current_char != '\0') {
        if (isspace(lexer->current_char)) {
            advance(lexer);  // Ignore whitespace
        }  else if (lexer->current_char == '{') {
            add_token(lexer, LBRACE, "{");
            advance(lexer);
        } else if (lexer->current_char == '}') {
            add_token(lexer, RBRACE, "}");
            advance(lexer);
        } else if (lexer->current_char == '"') {
            //add_token(lexer, "QUOTE", "\"");
            //advance(lexer);
            Token str = string_lookahead(lexer);
            add_token(lexer, str.type, str.value);
        } else if (story_lookahead(lexer)) {
            add_token(lexer, STORY, "story");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (room_lookahead(lexer)) {
            add_token(lexer, ROOM, "room");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } 
         else if (exits_lookahead(lexer)) {
            add_token(lexer, EXITS, "exits");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (END_lookahead(lexer)) {
            add_token(lexer, END, "END");
            advance(lexer);
            advance(lexer);
            advance(lexer);
        } else if (items_lookahead(lexer)) {
            add_token(lexer, ITEMS, "items");
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
            advance(lexer);
        }else if (startingItems_lookahead(lexer)) {
            add_token(lexer, STARTINGITEMS, "startingItems");
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
            advance(lexer);
            advance(lexer);
        } else if (isalpha(lexer->current_char)) {
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
        if (lexer->tokens[i].type == IDENTIFIER ) {
            // Only free dynamically allocated values for integer tokens
            free(lexer->tokens[i].value);
        }
    }
    free(lexer->tokens);  // Free the array of tokens
}

void print_tokens(LexerDFA *lexer) {
    for (int i = 0; i < lexer->token_count; i++) {
        printf("<%s, %s> index: %d\n", toString(lexer->tokens[i].type), lexer->tokens[i].value, i);
    }
}

char *toString(enum TokenType t){
    switch (t){

    case ROOM:
        return "ROOM";
    
    case STORY:
        return "STORY";

    case STRING:
        return "STRING";


    case IDENTIFIER:
        return "IDENTIFIER";
    
    case LBRACE:
        return "LBRACE";
    case RBRACE:
        return "RBRACE";
    case EXITS:
        return "EXITS"; 
    case END:
        return "END";
    case ITEMS:
        return "ITEMS";
    case STARTINGITEMS:
        return "STARTINGITEMS";
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
/*int count_items(struct Items *items) {
    int count = 0;
    while (items != NULL && items->kind == NONEMPTY_ITEMS) {
        count++;
        items = items->rest;
    }
    return count;
}*/

void print_java(struct Program *program, const char *output_file) {
    
    FILE *file = fopen(output_file, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s for writing.\n", output_file);
        exit(EXIT_FAILURE);
    }

    // Collect all used room IDs from ExitOptions
    char *used_rooms[1000];
    int used_count = 0;

    struct RoomDeclarations *rooms_stored = program->roomDeclarations;
    while (rooms_stored != NULL && rooms_stored->kind == NONEMPTY_DECLS) {
        struct ExitOptions *current_exit = rooms_stored->first->exitOptions;
        while (current_exit != NULL && current_exit->kind == NONEMPTY_OPTS) {
            used_rooms[used_count++] = current_exit->firstRoomId;
            current_exit = current_exit->rest;
        }
        rooms_stored = rooms_stored->rest;
    }

    //java imports
    fprintf(file, "import java.util.Scanner;\n");
    fprintf(file, "import java.util.HashSet;\n");
    fprintf(file, "import java.util.Set;\n\n");
    
    /**************** GET THE NAME OF THE CLASS **************************/

    
    char class_name[256]; 
    const char *base_name = strrchr(output_file, '/'); 
    if (base_name == NULL) {
        base_name = output_file;
    } else {
        base_name++; 
    }

    // Copy the file name without extension
    strncpy(class_name, base_name, sizeof(class_name) - 1);
    class_name[sizeof(class_name) - 1] = '\0';
    char *dot = strrchr(class_name, '.');
    if (dot != NULL) {
        *dot = '\0'; // Remove the extension
    }

    /**********************************************/

    fprintf(file, "public class %s {\n\n", class_name);

    // Print room declarations
    struct RoomDeclarations *roomDeclarations = program->roomDeclarations;
    while (roomDeclarations != NULL && roomDeclarations->kind == NONEMPTY_DECLS) {
        struct RoomDeclaration *room = roomDeclarations->first;
        int is_used = 0;

        //check if the specific room is used as an exit
        for (int i = 0; i < used_count; i++) {
            if (strcmp(used_rooms[i], room->roomId) == 0) {
                is_used = 1;
                break;
            }
        }

        if(is_used){
            fprintf(file, "\tpublic static void %s(Set<String> starting_items) {\n\n", room->roomId);
            fprintf(file, "\t\tSystem.out.println(%s);\n", room->description);
            // Add exit options
            struct ExitOptions *current_exit = room->exitOptions;
            int exit_count = 0;
            char *exit_list[100];
            while (current_exit != NULL && current_exit->kind == NONEMPTY_OPTS) {
                if (exit_count < 100) {
                    exit_list[exit_count++] = current_exit->firstRoomId;
                }
                current_exit = current_exit->rest;
            }

        /******** END OF MAZE: IF THERE ARE ITEMS, ADD THEM ***********************/

        if(exit_count == 0){
            fprintf(file, "\n");
            
            struct Items *current_item = room->items;
             while (current_item != NULL && current_item->kind == NONEMPTY_ITEMS) {
                fprintf(file, "\n\t\tSystem.out.println();");
                // Start defining the keys set
                fprintf(file, "\n\t\tSet<String> keys = Set.of(");
                // Add items
                int first = 1; // Flag to handle commas
                while (current_item != NULL && current_item->kind == NONEMPTY_ITEMS) {
                    if (!first) {
                        fprintf(file, ", ");
                    }
                    fprintf(file, "\"%s\"", current_item->firstItemID);
                    first = 0;
                    current_item = current_item->rest;
                }

                // Close the Set.of definition
                fprintf(file, ");\n");
                current_item = current_item->rest;
            }
            // Check if starting_items contains all keys and print messages
            fprintf(file, "\n\t\tif (starting_items.containsAll(keys)) {\n");
            fprintf(file, "\t\t\tSystem.out.println(\"Congratulations! You have all the required items.\");\n");
            fprintf(file, "\t\t\tSystem.out.println(\"Keys required: \" + keys);\n");

            fprintf(file, "\t\t} else {\n");
            fprintf(file, "\t\t\tSystem.out.println(\"Failed to Escape!\");\n");
            fprintf(file, "\t\t\tSystem.out.println(\"You are missing some keys.\");\n");
            fprintf(file, "\t\t\tSystem.out.println(\"Keys required: \" + keys);\n");
            fprintf(file, "\t\t\tSystem.out.println(\"Your items: \" + starting_items);\n");
            fprintf(file, "\t\t}\n");

            fprintf(file, "\t\t\tSystem.out.println();\n");
        }

        /******** NOT END OF MAZE **************************/


        /******* TAKE IN INPUT FOR EXIT ROOM *****************/

        if(exit_count > 0){
            fprintf(file, "\n\t\tScanner scanner = new Scanner(System.in);\n");
            fprintf(file, "\t\tString input = scanner.nextLine();\n\n");

            // Add items
            struct Items *current_item = room->items;
            while (current_item != NULL && current_item->kind == NONEMPTY_ITEMS) {
                fprintf(file, "\t\tstarting_items.add(\"%s\");\n", current_item->firstItemID);
                fprintf(file, "\n\t\tSystem.out.println();");
                fprintf(file, "\n\t\tSystem.out.println(\"Acquired: %s\");\n", current_item->firstItemID);
                current_item = current_item->rest;
            }

        

            if (exit_count == 1) { //only one exit option
                fprintf(file, "\n\t\twhile (!input.equals(\"%s\")) {\n", exit_list[0]);
                fprintf(file, "\t\t\tSystem.out.println();\n");
                fprintf(file, "\t\t\tSystem.out.println(\"Please choose the only available exit: %s\");\n", exit_list[0]);
                fprintf(file, "\t\t\tSystem.out.println();\n");
                fprintf(file, "\t\t\tinput = scanner.nextLine();\n");
                fprintf(file, "\t\t\tSystem.out.println();\n");
                fprintf(file, "\t\t}\n");

                 // Print Current Items on one line enclosed in brackets
                    fprintf(file, "\t\t\tSystem.out.println();\n");
                    fprintf(file, "\t\tSystem.out.print(\"Current Items: [\");\n");
                    fprintf(file, "\t\tint count = 0;\n");
                    fprintf(file, "\t\tfor (String item : starting_items) {\n");
                    fprintf(file, "\t\t\tif (count > 0) {\n");
                    fprintf(file, "\t\t\t\tSystem.out.print(\", \");\n");
                    fprintf(file, "\t\t\t}\n");
                    fprintf(file, "\t\t\tSystem.out.print(item);\n");
                    fprintf(file, "\t\t\tcount++;\n");
                    fprintf(file, "\t\t}\n");
                    fprintf(file, "\t\tSystem.out.println(\"]\");\n");
                    fprintf(file, "\t\t\tSystem.out.println();\n");

                fprintf(file, "\n\t\t%s(starting_items);\n", exit_list[0]);
            } 
            else if (exit_count > 1) { //more than one exit option
                fprintf(file, "\n\t\twhile (");
                for (int i = 0; i < exit_count; i++) {
                    fprintf(file, "!input.equals(\"%s\")", exit_list[i]);
                    if (i < exit_count - 1) {
                        fprintf(file, " && ");
                    }
                }
                fprintf(file, ") {\n");
                fprintf(file, "\t\t\tSystem.out.println();\n");
                fprintf(file, "\t\t\tSystem.out.println(\"Please choose one of the available exits: ");
                for (int i = 0; i < exit_count; i++) {
                    fprintf(file, "%s", exit_list[i]);
                    if (i < exit_count - 1) {
                        fprintf(file, ", ");
                    }
                }
                fprintf(file, "\");\n");
                fprintf(file, "\t\t\tSystem.out.println();\n");
                fprintf(file, "\t\t\tinput = scanner.nextLine();\n");
                fprintf(file, "\t\t}\n");

                for (int i = 0; i < exit_count; i++) {
                    fprintf(file, "\t\tif (input.equals(\"%s\")) {\n", exit_list[i]);
                    // Print Current Items on one line enclosed in brackets
                    fprintf(file, "\t\t\tSystem.out.println();\n");
                    fprintf(file, "\t\tSystem.out.print(\"Current Items: [\");\n");
                    fprintf(file, "\t\tint count = 0;\n");
                    fprintf(file, "\t\tfor (String item : starting_items) {\n");
                    fprintf(file, "\t\t\tif (count > 0) {\n");
                    fprintf(file, "\t\t\t\tSystem.out.print(\", \");\n");
                    fprintf(file, "\t\t\t}\n");
                    fprintf(file, "\t\t\tSystem.out.print(item);\n");
                    fprintf(file, "\t\t\tcount++;\n");
                    fprintf(file, "\t\t}\n");
                    fprintf(file, "\t\tSystem.out.println(\"]\");\n");
                    fprintf(file, "\t\t\tSystem.out.println();\n");

                    fprintf(file, "\t\t\t%s(starting_items);\n", exit_list[i]);
                    fprintf(file, "\t\t\treturn;\n");
                    fprintf(file, "\t\t}\n");
                }
            } 
        }
        fprintf(file, "\t}\n");
        }
        roomDeclarations = roomDeclarations->rest;
    }

    // Main function
    fprintf(file, "\n\tpublic static void main(String[] args) {\n");
    fprintf(file, "\n\t\tSet<String> starting_items = new HashSet<>();\n");

    char *first_room_id = NULL;
    if (program->roomDeclarations != NULL && program->roomDeclarations->kind == NONEMPTY_DECLS) {
        first_room_id = program->roomDeclarations->first->roomId;
    }

    if (first_room_id != NULL) {
        fprintf(file, "\t\t%s(starting_items);\n", first_room_id);
    } else {
        fprintf(file, "\t\tSystem.out.println(\"No rooms available.\");\n");
    }

    fprintf(file, "\t}\n");
    fprintf(file, "}\n");

    fclose(file);
    
}


int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *filename = argv[1];  // Input file containing the program to be tokenized
    char *input_expression = read_file(filename);
    const char *output_file = argv[2];

    // Create lexer
    LexerDFA lexer = create_lexer(input_expression);

    // Run lexer
    run(&lexer);

    // Print tokens in the required format
   // print_tokens(&lexer);

                                                                                 //first index
    struct Program_parse_result result = program_parse(lexer.tokens, lexer.token_count, 0);
    if(result.result == SUCCESS){
        print_Program(result.program);
        print_java(result.program, output_file);    
    }
    else{ 
        printf("Parsing failed. Follow preceding fail statements to track it down.\n");
        /*
       
        possible errors:
            1. did not see expected terminal symbol
            2. not enough tokens to consume  
            3. child call failed  
            
        */
    }


    // Free allocated memory
    //free_lexer(&lexer);
    free(input_expression);

    return 0;
}


