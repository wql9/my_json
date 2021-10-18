#include "lept_parse.h"
#include <stdexcept>      // std::out_of_range
#include<iostream>

int lept_json::lept_parse::lept_parse_all(lept_value& value, lept_context& context)
{
    assert(&value != NULL);
    lept_free(value);
    lept_parse_whitespace(context);
    int ret;
    if((ret=lept_parse_value(value, context))==LEPT_PARSE_OK)
    {
        lept_parse_whitespace(context);
        if(context.get_lept_context_pos()<context.get_lept_context_length())
            ret=LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

int lept_json::lept_parse::lept_parse_value(lept_value& value, lept_context& context)
{
    string str=context.get_lept_context_string();
    int pos=context.get_lept_context_pos();
    int length=context.get_lept_context_length();
    if(pos>=length)  return LEPT_PARSE_EXPECT_VALUE;
    switch (str[pos])
    {
        case 'n':  return lept_parse_NTF(value, context, "null");break;
        case 't':  return lept_parse_NTF(value, context, "true");break;
        case 'f':  return lept_parse_NTF(value, context, "false");break;
        case '\"': return lept_parse_string(value, context);break;
        case '[': return lept_parse_array(value, context);break;
        case '{': return lept_parse_object(value,context);break;
        default:  return lept_parse_number(value, context);break;
    }
}
//judge null,true,false
int lept_json::lept_parse::lept_parse_NTF(lept_value& value, lept_context& context, string expect)
{
    string str=context.get_lept_context_string();
    int pos=context.get_lept_context_pos();
    for(int i=0;i<expect.length();i++)
    {
        if(str[pos++]!=expect[i])
            return LEPT_PARSE_INVALID_VALUE;
    }
    if(expect[0]=='n')  value.set_lept_type(LEPT_NULL);
    else if(expect[0]=='t')  value.set_lept_type(LEPT_TRUE);
    else if(expect[0]=='f')  value.set_lept_type(LEPT_FALSE);
    context.set_lept_context_pos(pos);
    return LEPT_PARSE_OK;
}

void lept_json::lept_parse::lept_parse_whitespace(lept_context& context)
{
    string str=context.get_lept_context_string();
    int pos=context.get_lept_context_pos();
    int length=context.get_lept_context_length();
    while(pos<length && (str[pos]==' ' || str[pos]=='\n' || str[pos]=='\r' || str[pos]=='\t'))
        pos++;    
    context.set_lept_context_pos(pos);
}

void lept_json::lept_parse::lept_free(lept_value& value)
{
    value.free_lept_value();
}

#define ISDIGIT(ch) ((ch)>='0' && (ch)<='9')
#define ISDIGIT0to9(ch) ((ch)>='1' && (ch)<='9')

int lept_json::lept_parse::lept_parse_number(lept_value& value, lept_context& context)
{
    string str=context.get_lept_context_string();
    int pos=context.get_lept_context_pos();
    int subpos=pos;
    //get rid of some exceptions
    if(str[pos] == '-')  pos++;
    if(str[pos] == '0')  pos++;
    else
    {
        if(!ISDIGIT0to9(str[pos]))
            return LEPT_PARSE_INVALID_VALUE;
        while(ISDIGIT(str[pos])){pos++;}
    }
    if(str[pos] == '.')
    {
        pos++;
        if(!ISDIGIT(str[pos]))  return LEPT_PARSE_INVALID_VALUE;
        while(ISDIGIT(str[pos])){pos++;}
    }
    if(str[pos] == 'e' || str[pos] == 'E')
    {
        pos++;
        if(str[pos] == '+' || str[pos] == '-')  pos++;
        if(!ISDIGIT(str[pos]))  return LEPT_PARSE_INVALID_VALUE;
        while(ISDIGIT(str[pos])){pos++;}
    }
    //conversion
    try
    {
        value.set_lept_number(stod(str.substr(subpos)));
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "Out of Range error: " << e.what() << '\n';
        return LEPT_PARSE_OUT_OF_RANGE;
    }
    context.set_lept_context_pos(pos);
    value.set_lept_type(LEPT_NUMBER);
    return LEPT_PARSE_OK;
}

int lept_json::lept_parse::lept_parse_string(lept_value& value, lept_context& context)
{
    string strIn=context.get_lept_context_string();
    int posIn=context.get_lept_context_pos();
    string strOut("");
    if(strIn[posIn]=='\"')  posIn++;
    //start conversion
    while(1)
    {
        switch(strIn[posIn])
        {
            case '\"': value.set_lept_string(strOut);
                       value.set_lept_type(LEPT_STRING);
                       context.set_lept_context_pos(++posIn);
                       return LEPT_PARSE_OK;
            case '\\':
                posIn++;//next
                switch(strIn[posIn]){
                    case '\"': strOut += '\"';break;
                    case '\\': strOut += '\\';break;
                    case '/': strOut += '/';break;
                    case 'b': strOut += '\b';break;
                    case 'f': strOut += '\f';break;
                    case 'n': strOut += '\n';break;
                    case 'r': strOut += '\r';break;
                    case 't': strOut += '\t';break;
                    case 'u':
                        //unicode
                        posIn++;//next
                        int ret;
                        if((ret = lept_parse_unicode(strIn, strOut, posIn))!=LEPT_PARSE_OK)
                            return ret;
                        break;
                    default: return LEPT_PARSE_INVALID_STRING_ESCAPE;break;
                }
                break;
            case '\0': return LEPT_PARSE_MISS_QUOTATION_MARK;break;
            default:
                if(strIn[posIn]<0x20)
                    return LEPT_PARSE_INVALID_STRING_CHAR;
                else
                    strOut += strIn[posIn];
        }
        posIn++;
    }
}

int lept_json::lept_parse::lept_parse_unicode(string& strIn, string& strOut, int& posIn)
{
    unsigned int u1=0;
    unsigned int u2=0;
    if(!lept_parse_unicode_hex4(strIn, posIn, u1))
        return LEPT_PARSE_INVALID_UNICODE_HEX;
    //surrogate pair
    if(u1>= 0xD800 && u1 <= 0xDBFF)
    {
        if(strIn[posIn++]!='\\')  return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
        if(strIn[posIn++]!='u')  return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
        if(!lept_parse_unicode_hex4(strIn, posIn, u2))  return LEPT_PARSE_INVALID_UNICODE_HEX;
        if(u2<0xDC00 || u2>0xDFFF)  return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
        u1=(((u1-0xD800)<<10) | (u2-0xDC00))+0X10000;
    }
    lept_encode_utf8(strOut, u1);
    posIn--;
    return LEPT_PARSE_OK;
}

bool lept_json::lept_parse::lept_parse_unicode_hex4(string& strIn, int& posIn, unsigned int& u)
{
    for(int i=0;i<4;i++)
    {
        u<<=4;
        char c=strIn[posIn++];
        if(c>='0' && c<='9')  u |= c-'0';
        else if(c>='A' && c<='F')  u |= c-'A'+10;
        else if(c>='a' && c<='f')  u |= c-'a'+10;
        else  return false;
    }
    return true;
}

void lept_json::lept_parse::lept_encode_utf8(string& strOut, unsigned int& u)
{
    if(u <= 0x7F)
    {
        if(u==0x00) {
            strOut.push_back('\\');
            strOut.push_back('0');  
        }
        else  strOut += (char)(u & 0xFF);
    }
    else if(u <= 0x7FF)
    {
        strOut += (char)(0xC0 | ((u>>6) & 0xFF));
        strOut += (char)(0x80 | (u & 0x3F));
    }
    else if(u <= 0xFFFF)
    {
        strOut += (char)(0xE0 | ((u>>12) & 0xFF));
        strOut += (char)(0x80 | ((u>>6) & 0x3F));
        strOut += (char)(0x80 | (u & 0x3F));
    }
    else
    {
        assert(u <= 0x10FFFF);
        strOut += (char)(0xF0 | ((u>>18) & 0xFF));
        strOut += (char)(0X80 | ((u>>12) & 0x3F));
        strOut += (char)(0x80 | ((u>>6) & 0x3F));
        strOut += (char)(0x80 | (u & 0x3F));
    }
}

int lept_json::lept_parse::lept_parse_array(lept_value& value, lept_context& context)
{
    string str=context.get_lept_context_string();
    int pos=context.get_lept_context_pos();
    assert(str[pos++] == '[');
    context.set_lept_context_pos(pos);
    lept_parse_whitespace(context);
    pos=context.get_lept_context_pos();
    if(str[pos]==']')
    {
        context.set_lept_context_pos(++pos);
        value.set_lept_type(LEPT_ARRAY);
        return LEPT_PARSE_OK;
    }
    int ret;
    lept_value tmp;
    while (1)
    {
        if((ret=lept_parse_value(tmp,context))!=LEPT_PARSE_OK)
            return ret;
        value.set_lept_array_push(tmp);lept_free(tmp);
        lept_parse_whitespace(context);
        pos=context.get_lept_context_pos();
        if(str[pos] == ',')
        {
            context.set_lept_context_pos(++pos);
            lept_parse_whitespace(context);
            pos=context.get_lept_context_pos();
        }
        else if(str[pos] == ']')
        {
            context.set_lept_context_pos(++pos);
            value.set_lept_type(LEPT_ARRAY);
            return LEPT_PARSE_OK;
        }
        else  return LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET;
    }
}

int lept_json::lept_parse::lept_parse_object(lept_value& value, lept_context& context)
{
    int ret;
    string str=context.get_lept_context_string();
    int pos=context.get_lept_context_pos();
    assert(str[pos++]=='{');
    context.set_lept_context_pos(pos);
    lept_parse_whitespace(context);
    pos=context.get_lept_context_pos();
    if(str[pos]=='}')
    {
        context.set_lept_context_pos(++pos);
        value.set_lept_type(LEPT_OBJECT);
        return LEPT_PARSE_OK;
    }
    while(1)
    {
        if(str[pos]!='\"')  return LEPT_PARSE_MISS_KEY;
        lept_value tmp;
        if((ret=lept_parse_string(tmp,context))!=LEPT_PARSE_OK)  return ret;
        string key=tmp.get_lept_string();  lept_free(tmp);

        lept_parse_whitespace(context);
        pos=context.get_lept_context_pos();
        if(str[pos]!=':')  return LEPT_PARSE_MISS_COLON;
        context.set_lept_context_pos(++pos);
        lept_parse_whitespace(context);
        pos=context.get_lept_context_pos();

        if((ret=lept_parse_value(tmp,context))!=LEPT_PARSE_OK)  return ret;
        value.set_lept_object_push(make_pair(key,tmp));  lept_free(tmp);
        
        lept_parse_whitespace(context);
        pos=context.get_lept_context_pos();
        
        if(str[pos]==',')
        {
            context.set_lept_context_pos(++pos);
            lept_parse_whitespace(context);
            pos=context.get_lept_context_pos();
        }
        else if(str[pos]=='}')
        {
            context.set_lept_context_pos(++pos);
            value.set_lept_type(LEPT_OBJECT);
            return LEPT_PARSE_OK;
        }
        else  return LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET;
    }
}






