#include <iostream>
#include "globalSettings.h"
#include "lept_parse.h"
#include "lept_stringify.h"
//#include "lept_value.h"
//#include "lept_context.h"
using namespace std;

int main_ret=0;
int test_pass=0;
int test_count=0;

void test_parse(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_stringify(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify);

void test_parse_null(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_true(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_false(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_number(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_string(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_array(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_object(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_InvalidValue(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_ExpectValue(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_errpr_RootNotSingular(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_errpr_OutofRange(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_MissingQuotationMark(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_InvalidStringEscape(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_InvalidStringChar(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_InvalidUnicodeHex(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_InvalidUnicodeSurrogate(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_MissCommaOrSquareBracket(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_MissKey(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_MissColon(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_parse_error_MissCommaOrCurlyBracket(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_stringify_NTF(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify);
void test_stringify_number(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify);
void test_stringify_string(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify);
void test_stringify_array(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify);
void test_stringify_object(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify);


void test_number(double expect, string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_string(string expect, string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_error(lept_error e, string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse);
void test_roundtrip(string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse, lept_json::lept_stringify& stringify);


int main()
{
    lept_json::lept_value v;
    lept_json::lept_context c;
    lept_json::lept_parse p;
    lept_json::lept_stringify s;
    test_parse(v,c,p);
    test_parse_error(v,c,p);
    test_stringify(v,c,p,s);
    cout<<test_pass<<"/"<<test_count<<"  pass rate: "<<test_pass*1.0/test_count*100<<"%"<<endl;
    return 0;
}

void test_parse(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    test_parse_null(value,context,parse);
    test_parse_true(value,context,parse);
    test_parse_false(value,context,parse);
    test_parse_number(value,context,parse);
    test_parse_string(value,context,parse);
    test_parse_array(value,context,parse);
    test_parse_object(value,context,parse);
}

void test_parse_error(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    test_parse_error_ExpectValue(value,context,parse);
    test_parse_error_InvalidValue(value,context,parse);
    test_parse_errpr_RootNotSingular(value,context,parse);
    test_parse_errpr_OutofRange(value,context,parse);
    test_parse_error_MissingQuotationMark(value,context,parse);
    test_parse_error_InvalidStringEscape(value,context,parse);
    test_parse_error_InvalidStringChar(value,context,parse);
    test_parse_error_InvalidUnicodeHex(value,context,parse);
    test_parse_error_InvalidUnicodeSurrogate(value,context,parse);
    test_parse_error_MissCommaOrSquareBracket(value,context,parse);
    test_parse_error_MissKey(value,context,parse);
    test_parse_error_MissColon(value,context,parse);
    test_parse_error_MissCommaOrCurlyBracket(value,context,parse);
}

void test_stringify(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify)
{
    test_stringify_NTF(value,context,parse,stringify);
    test_stringify_number(value,context,parse,stringify);
    test_stringify_string(value,context,parse,stringify);
    test_stringify_array(value,context,parse,stringify);
    test_stringify_object(value,context,parse,stringify);
}

void test_parse_null(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context("null",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_OK || value.get_lept_type()!=LEPT_NULL)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
    
    context.set_lept_context("   null    ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_OK || value.get_lept_type()!=LEPT_NULL)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
}

void test_parse_true(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context("true",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_OK || value.get_lept_type()!=LEPT_TRUE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
    
    context.set_lept_context("   true    ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_OK || value.get_lept_type()!=LEPT_TRUE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
}

void test_parse_false(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context("false",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_OK || value.get_lept_type()!=LEPT_FALSE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
    
    context.set_lept_context("   false    ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_OK || value.get_lept_type()!=LEPT_FALSE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
}

void test_parse_error_InvalidValue(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    //null
    context.set_lept_context("  nul   ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_INVALID_VALUE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
    //true
    context.set_lept_context("  tr   ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_INVALID_VALUE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
    //false
    context.set_lept_context("  fal   ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_INVALID_VALUE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
    //others
    context.set_lept_context("  ok   ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_INVALID_VALUE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;

    //invalid number
    test_error(LEPT_PARSE_INVALID_VALUE, "+0",value,context,parse);
    test_error(LEPT_PARSE_INVALID_VALUE, "+1",value,context,parse);
    test_error(LEPT_PARSE_INVALID_VALUE, ".123",value,context,parse); /* at least one digit before '.' */
    test_error(LEPT_PARSE_INVALID_VALUE, "1.",value,context,parse);   /* at least one digit after '.' */
    test_error(LEPT_PARSE_INVALID_VALUE, "INF",value,context,parse);
    test_error(LEPT_PARSE_INVALID_VALUE, "inf",value,context,parse);
    test_error(LEPT_PARSE_INVALID_VALUE, "NAN",value,context,parse);
    test_error(LEPT_PARSE_INVALID_VALUE, "nan",value,context,parse);

    //invalid array element
    test_error(LEPT_PARSE_INVALID_VALUE, "[1,]",value,context,parse);
    test_error(LEPT_PARSE_INVALID_VALUE, "[\"a\", nul]",value,context,parse);
}

void test_parse_error_ExpectValue(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context("  ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_EXPECT_VALUE)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
}

void test_parse_errpr_RootNotSingular(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context("  true null  ",0);
    test_count++;
    if(parse.lept_parse_all(value,context)!=LEPT_PARSE_ROOT_NOT_SINGULAR)
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    else
        test_pass++;
    
    /* invalid number */
    test_error(LEPT_PARSE_ROOT_NOT_SINGULAR, "0123",value,context,parse); /* after zero should be '.' , 'E' , 'e' or nothing */
    test_error(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x0",value,context,parse);
    test_error(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x123",value,context,parse);
}

void test_number(double expect, string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context(str,0);
    test_count++;
    int ret;
    if((ret = parse.lept_parse_all(value,context)) == LEPT_PARSE_OK && value.get_lept_type() == LEPT_NUMBER && value.get_lept_number()==expect)
        test_pass++;
    else 
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs at"<<str<<endl;
}

void test_parse_number(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    test_number(0.0, "0",value,context,parse);
    test_number(0.0, "-0",value,context,parse);
    test_number(0.0, "-0.0",value,context,parse);
    test_number(1.0, "1",value,context,parse);
    test_number(-1.0, "-1",value,context,parse);
    test_number(1.5, "1.5",value,context,parse);
    test_number(-1.5, "-1.5",value,context,parse);
    test_number(3.1416, "3.1416",value,context,parse);
    test_number(1E10, "1E10",value,context,parse);
    test_number(1e10, "1e10",value,context,parse);
    test_number(1E+10, "1E+10",value,context,parse);
    test_number(1E-10, "1E-10",value,context,parse);
    test_number(-1E10, "-1E10",value,context,parse);
    test_number(-1e10, "-1e10",value,context,parse);
    test_number(-1E+10, "-1E+10",value,context,parse);
    test_number(-1E-10, "-1E-10",value,context,parse);
    test_number(1.234E+10, "1.234E+10",value,context,parse);
    test_number(1.234E-10, "1.234E-10",value,context,parse);
    //test_number(0.0, "1e-10000",value,context,parse); //smaller than minimum out of range
}

void test_parse_errpr_OutofRange(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
#if 0
    test_error(LEPT_PARSE_OUT_OF_RANGE, "1e309",value,context,parse);
    test_error(LEPT_PARSE_OUT_OF_RANGE, "-1e309",value,context,parse);
#endif
}

void test_error(lept_error e, string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context(str,0);
    test_count++;
    if(e != parse.lept_parse_all(value,context))
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs at  "<<str<<endl;
    else
        test_pass++;
}

void test_string(string expect, string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    context.set_lept_context(str,0);
    test_count++;
    if(parse.lept_parse_all(value,context)==LEPT_PARSE_OK && value.get_lept_type()==LEPT_STRING && expect==value.get_lept_string())
        test_pass++;
    else
        cout<<__FILE__<<"  "<<__LINE__<<"  error occurs at  "<<str<<endl;
}

void test_parse_string(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    test_string("", "\"\"",value,context,parse);
    test_string("Hello", "\"Hello\"",value,context,parse);
    test_string("Hello\nWorld", "\"Hello\\nWorld\"",value,context,parse);
    test_string("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"",value,context,parse);
    //test_string("Hello\\0World", "\"Hello\\u0000World\"",value,context,parse);  //string can not read in '\0'
    test_string("\x24", "\"\\u0024\"",value,context,parse);         /* Dollar sign U+0024 */
    test_string("\xC2\xA2", "\"\\u00A2\"",value,context,parse);     /* Cents sign U+00A2 */
    test_string("\xE2\x82\xAC", "\"\\u20AC\"",value,context,parse); /* Euro sign U+20AC */
    test_string("\xF0\x9D\x84\x9E", "\"\\uD834\\uDD1E\"",value,context,parse);  /* G clef sign U+1D11E */
    test_string("\xF0\x9D\x84\x9E", "\"\\ud834\\udd1e\"",value,context,parse);  /* G clef sign U+1D11E */
}

void test_parse_error_MissingQuotationMark(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_MISS_QUOTATION_MARK, "\"",value,context,parse);
    test_error(LEPT_PARSE_MISS_QUOTATION_MARK, "\"abc",value,context,parse);
}

void test_parse_error_InvalidStringEscape(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\v\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\'\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\0\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\x12\"",value,context,parse);
}

void test_parse_error_InvalidStringChar(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_INVALID_STRING_CHAR, "\"\x01\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_STRING_CHAR, "\"\x1F\"",value,context,parse);
}

void test_parse_error_InvalidUnicodeHex(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u0\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u01\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u012\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u/000\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\uG000\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u0/00\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u0G00\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u00/0\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u00G0\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u000/\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u000G\"",value,context,parse);
}

void test_parse_error_InvalidUnicodeSurrogate(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uDBFF\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\\\\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uDBFF\"",value,context,parse);
    test_error(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uE000\"",value,context,parse);
}

void test_parse_array(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    //first
    test_count++;
    context.set_lept_context("[ ]",0);
    if(parse.lept_parse_all(value,context) == LEPT_PARSE_OK && value.get_lept_type() == LEPT_ARRAY && value.get_lept_array_size()==0)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<" error occurs"<<endl;

    //second
    test_count++;
    context.set_lept_context("[ null , false , true , 123 , \"abc\" ]",0);
    if(parse.lept_parse_all(value,context) == LEPT_PARSE_OK && value.get_lept_type() == LEPT_ARRAY && value.get_lept_array_size()==5)
    {
        if(((value.get_lept_array_element(0)).get_lept_type()==LEPT_NULL) &&\
            ((value.get_lept_array_element(1)).get_lept_type()==LEPT_FALSE) &&\
            ((value.get_lept_array_element(2)).get_lept_type()==LEPT_TRUE) &&\
            ((value.get_lept_array_element(3)).get_lept_type()==LEPT_NUMBER) &&\
            ((value.get_lept_array_element(4)).get_lept_type()==LEPT_STRING))
            {
                test_pass++;
            }
        else  cout<<__FILE__<<"  "<<__LINE__<<" error occurs"<<endl;
    }
    else  cout<<__FILE__<<"  "<<__LINE__<<" error occurs"<<endl;

    test_count++;
    if((value.get_lept_array_element(3)).get_lept_number()==123.0)
        test_pass++;
    else cout<<__FILE__<<"  "<<__LINE__<<" error occurs"<<endl;

    test_count++;
    if((value.get_lept_array_element(4)).get_lept_string() == "abc")
        test_pass++;
    else cout<<__FILE__<<"  "<<__LINE__<<" error occurs"<<endl;

    //third
    context.set_lept_context("[ [ ] , [ 0 ] , [ 0 , 1 ] , [ 0 , 1 , 2 ] ]",0);
    test_count++;
    if((parse.lept_parse_all(value,context))==LEPT_PARSE_OK && (value.get_lept_type())==LEPT_ARRAY && (int)(value.get_lept_array_size())==4)
        test_pass++;
    else cout<<__FILE__<<"  "<<__LINE__<<" error occurs"<<endl;

    for(int i=0;i<4;i++)
    {
        test_count++;
        lept_json::lept_value tmp=value.get_lept_array_element(i);
        if(tmp.get_lept_type()==LEPT_ARRAY && (int)(tmp.get_lept_array_size())==i)
            test_pass++;
        else cout<<__FILE__<<"  "<<__LINE__<<" error occurs at  "<<i<<endl;

        for(int j=0;j<i;j++)
        {
            test_count++;
            if((tmp.get_lept_array_element(j)).get_lept_type()==LEPT_NUMBER && (tmp.get_lept_array_element(j)).get_lept_number()==(double)j)
                test_pass++;
            else cout<<__FILE__<<"  "<<__LINE__<<" error occurs at  "<<i<<"  "<<j<<endl;
        }
    }
}

void test_parse_error_MissCommaOrSquareBracket(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) {
    test_error(LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1",value,context,parse);
    test_error(LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1}",value,context,parse);
    test_error(LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1 2",value,context,parse);
    test_error(LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[[]",value,context,parse);
}

void test_parse_object(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse)
{
    //first
    context.set_lept_context(" { } ",0);
    test_count++;
    if((parse.lept_parse_all(value,context))==LEPT_PARSE_OK && (value.get_lept_type())==LEPT_OBJECT && (value.get_lept_object_size())==0)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;

    //second
    context.set_lept_context(
        " { "
        "\"n\" : null , "
        "\"f\" : false , "
        "\"t\" : true , "
        "\"i\" : 123 , "
        "\"s\" : \"abc\", "
        "\"a\" : [ 1, 2, 3 ],"
        "\"o\" : { \"1\" : 1, \"2\" : 2, \"3\" : 3 }"
        " } ",0);
    test_count++;
    if((parse.lept_parse_all(value,context))==LEPT_PARSE_OK && (value.get_lept_type())==LEPT_OBJECT && (value.get_lept_object_size())==7)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;

    test_count++;
    pair<string,lept_json::lept_value> tmp;
    tmp=value.get_lept_object_element(0);
    if(tmp.first=="n" && (tmp.second).get_lept_type()==LEPT_NULL)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;

    test_count++;
    tmp=value.get_lept_object_element(1);
    if(tmp.first=="f" && (tmp.second).get_lept_type()==LEPT_FALSE)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;

    test_count++;
    tmp=value.get_lept_object_element(2);
    if(tmp.first=="t" && (tmp.second).get_lept_type()==LEPT_TRUE)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;

    test_count++;
    tmp=value.get_lept_object_element(3);
    if(tmp.first=="i" && (tmp.second).get_lept_type()==LEPT_NUMBER && (tmp.second).get_lept_number()==123.0)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;

    test_count++;
    tmp=value.get_lept_object_element(4);
    if(tmp.first=="s" && (tmp.second).get_lept_type()==LEPT_STRING && (tmp.second).get_lept_string()=="abc")
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    
    test_count++;
    tmp=value.get_lept_object_element(5);
    if(tmp.first=="a" && (tmp.second).get_lept_type()==LEPT_ARRAY && (tmp.second).get_lept_array_size()==3)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    for(int i=0;i<3;i++)
    {
        lept_json::lept_value v=(tmp.second).get_lept_array_element(i);
        test_count++;
        if(v.get_lept_type()==LEPT_NUMBER && v.get_lept_number()==(i+1))
            test_pass++;
        else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs at  "<<i<<endl;
    }

    test_count++;
    tmp=value.get_lept_object_element(6);
    if(tmp.first=="o" && (tmp.second).get_lept_type()==LEPT_OBJECT && (tmp.second).get_lept_object_size()==3)
        test_pass++;
    else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs"<<endl;
    for(int i=0;i<3;i++)
    {
        pair<string,lept_json::lept_value> p=(tmp.second).get_lept_object_element(i);
        test_count++;
        if((p.second).get_lept_type()==LEPT_NUMBER && (p.second).get_lept_number()==(i+1))
            test_pass++;
        else  cout<<__FILE__<<"  "<<__LINE__<<"  error occurs at  "<<i<<endl;
    }
}

void test_parse_error_MissKey(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_MISS_KEY, "{:1,",value,context,parse);
    test_error(LEPT_PARSE_MISS_KEY, "{1:1,",value,context,parse);
    test_error(LEPT_PARSE_MISS_KEY, "{true:1,",value,context,parse);
    test_error(LEPT_PARSE_MISS_KEY, "{false:1,",value,context,parse);
    test_error(LEPT_PARSE_MISS_KEY, "{null:1,",value,context,parse);
    test_error(LEPT_PARSE_MISS_KEY, "{[]:1,",value,context,parse);
    test_error(LEPT_PARSE_MISS_KEY, "{{}:1,",value,context,parse);
    test_error(LEPT_PARSE_MISS_KEY, "{\"a\":1,",value,context,parse);
}

void test_parse_error_MissColon(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_MISS_COLON, "{\"a\"}",value,context,parse);
    test_error(LEPT_PARSE_MISS_COLON, "{\"a\",\"b\"}",value,context,parse);
}

void test_parse_error_MissCommaOrCurlyBracket(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse) 
{
    test_error(LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1",value,context,parse);
    test_error(LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1]",value,context,parse);
    test_error(LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1 \"b\"",value,context,parse);
    test_error(LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":{}",value,context,parse);
}

void test_stringify_NTF(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify)
{
    test_roundtrip("null",value,context,parse,stringify);
    test_roundtrip("false",value,context,parse,stringify);
    test_roundtrip("true",value,context,parse,stringify);
}

void test_stringify_number(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify)
{
    test_roundtrip("0",value,context,parse,stringify);
    test_roundtrip("-0",value,context,parse,stringify);
    test_roundtrip("1",value,context,parse,stringify);
    test_roundtrip("-1",value,context,parse,stringify);
    test_roundtrip("1.5",value,context,parse,stringify);
    test_roundtrip("-1.5",value,context,parse,stringify);
    test_roundtrip("3.25",value,context,parse,stringify);
    test_roundtrip("1e+20",value,context,parse,stringify);
    test_roundtrip("1.234e+20",value,context,parse,stringify);
    test_roundtrip("1.234e-20",value,context,parse,stringify);
#if 0 //out of range
    test_roundtrip("1.0000000000000002",value,context,parse,stringify); /* the smallest number > 1 */
    test_roundtrip("4.9406564584124654e-324",value,context,parse,stringify); /* minimum denormal */
    test_roundtrip("-4.9406564584124654e-324",value,context,parse,stringify);
    test_roundtrip("2.2250738585072009e-308",value,context,parse,stringify);  /* Max subnormal double */
    test_roundtrip("-2.2250738585072009e-308",value,context,parse,stringify);
    test_roundtrip("2.2250738585072014e-308",value,context,parse,stringify);  /* Min normal positive double */
    test_roundtrip("-2.2250738585072014e-308",value,context,parse,stringify);
    test_roundtrip("1.7976931348623157e+308",value,context,parse,stringify);  /* Max double */
    test_roundtrip("-1.7976931348623157e+308",value,context,parse,stringify);
#endif
}

void test_stringify_string(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify)
{
    test_roundtrip("\"\"",value,context,parse,stringify);
    test_roundtrip("\"Hello\"",value,context,parse,stringify);
    test_roundtrip("\"Hello\\nWorld\"",value,context,parse,stringify);
    test_roundtrip("\"\\\" \\\\ / \\b \\f \\n \\r \\t\"",value,context,parse,stringify);
#if 0
    test_roundtrip("\"Hello\\u0000World\"",value,context,parse,stringify);
#endif
}

void test_stringify_array(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify)
{
    test_roundtrip("[]",value,context,parse,stringify);
    test_roundtrip("[null,false,true,123,\"abc\",[1,2,3]]",value,context,parse,stringify);
}

void test_stringify_object(lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify)
{
    test_roundtrip("{}",value,context,parse,stringify);
    test_roundtrip("{\"n\":null,\"f\":false,\"t\":true,\"i\":123,\"s\":\"abc\",\"a\":[1,2,3],\"o\":{\"1\":1,\"2\":2,\"3\":3}}",value,context,parse,stringify);
}

void test_roundtrip(string str, lept_json::lept_value& value, lept_json::lept_context& context, lept_json::lept_parse& parse,lept_json::lept_stringify& stringify)
{
    context.set_lept_context(str,0);
    test_count++;
    if((parse.lept_parse_all(value,context))==LEPT_PARSE_OK)
    {
        lept_json::lept_context tmp;
        stringify.lept_stringify_all(value,tmp);
        if(tmp.get_lept_context_string()==str)
            test_pass++;
        else cout<<__FILE__<<"  "<<__LINE__<<"  error occurs at  "<<str<<endl;
    }
    else cout<<__FILE__<<"  "<<__LINE__<<"  error occurs at  "<<str<<endl;
}


