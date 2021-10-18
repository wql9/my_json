#ifndef GLOBAL_SETTINGS
#define GLOBAL_SETTINGS
//json data type
typedef enum{LEPT_NULL, LEPT_TRUE, LEPT_FALSE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT} lept_type;

//possible error in parse
/*
    LEPT_PARSE_OK---no error
    LEPT_PARSE_EXPECT_VALUE---there is no value
    LEPT_PARSE_ROOT_NOT_SINGULAR---there is more than one value
    LEPT_PARSE_INVALID_VALUE---the value is invalid
    LEPT_PARSE_OUT_OF_RANGE---number can not be represented by double
    LEPT_PARSE_INVALID_STRING_ESCAPE---the format in escape character is not right
    LEPT_PARSE_MISS_QUOTATION_MARK---there is no right quotation mark
    LEPT_PARSE_INVALID_STRING_CHAR---the char is smaller than 0x20. It is invalid
    LEPT_PARSE_INVALID_UNICODE_HEX---there exists invalid char in four bit unicode hex
    LEPT_PARSE_INVALID_UNICODE_SURROGATE---the unicode surrgate is valid
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET---the array leaks comma or square bracket
    LEPT_PARSE_MISS_KEY---there is no key in a object
    LEPT_PARSE_MISS_COLON---there is no colon in a object
    LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET---there leaks comma or curly bracket
*/
typedef enum{LEPT_PARSE_OK, LEPT_PARSE_EXPECT_VALUE, LEPT_PARSE_ROOT_NOT_SINGULAR, LEPT_PARSE_INVALID_VALUE, LEPT_PARSE_OUT_OF_RANGE,\
            LEPT_PARSE_INVALID_STRING_ESCAPE, LEPT_PARSE_MISS_QUOTATION_MARK, LEPT_PARSE_INVALID_STRING_CHAR, \
            LEPT_PARSE_INVALID_UNICODE_HEX, LEPT_PARSE_INVALID_UNICODE_SURROGATE, LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, \
            LEPT_PARSE_MISS_KEY, LEPT_PARSE_MISS_COLON, LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET} lept_error;

#endif