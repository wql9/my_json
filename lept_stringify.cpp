#include "lept_stringify.h"
#include <sstream>

void lept_json::lept_stringify::lept_stringify_all(lept_value& value, lept_context& context)
{
    lept_stringify_value(value,context);
}

void lept_json::lept_stringify::lept_stringify_value(lept_value& value, lept_context& context)
{
    int type=value.get_lept_type();
    string str=context.get_lept_context_string();
    switch(type)
    {
    case LEPT_NULL: str+="null"; break;
    case LEPT_TRUE: str+="true"; break;
    case LEPT_FALSE: str+="false"; break;
    case LEPT_NUMBER: str+=lept_stringify_number(value); break;
    case LEPT_STRING: str+=lept_stringify_str(value.get_lept_string()); break;
    case LEPT_ARRAY: str+=lept_stringify_array(value,context); break;
    case LEPT_OBJECT: str+=lept_stringify_object(value,context); break;
    default:break;
    }
    context.set_lept_context(str,0);
}

string lept_json::lept_stringify::lept_stringify_number(lept_value& value)
{
    string res("");
    double num=value.get_lept_number();
    stringstream ss("");
    ss<<num;
    ss>>res;
    return res;
}

string lept_json::lept_stringify::lept_stringify_str(string str)
{
    string res("\"");
    int index=0;
    const char digits[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    while(index<str.size())
    {
        switch(str[index])
        {
        case '\"': res=res+'\\'+'\"'; break;
        case '\\': res=res+'\\'+'\\'; break;
        case '\b': res=res+'\\'+'b'; break;
        case '\f': res=res+'\\'+'f'; break;
        case '\n': res=res+'\\'+'n'; break;
        case '\r': res=res+'\\'+'r'; break;
        case '\t': res=res+'\\'+'t'; break;
        default:
            if(str[index]<0x20)
                res=res+'\\'+'u'+'0'+'0'+digits[str[index]>>4]+digits[(str[index]&15)];
            else res+=str[index];
            break;
        }
        index++;
    }
    res+='\"';
    return res;
}

string lept_json::lept_stringify::lept_stringify_array(lept_value& value,lept_context& context)
{
    string res("[");
    vector<lept_value> a=value.get_lept_array();
    for(int i=0;i<a.size();i++)
    {
        if(i>0) res+=',';
        lept_context tmp(res);
        lept_stringify_value(a[i],tmp);
        res=tmp.get_lept_context_string();
    }
    res+=']';
    return res;
}

string lept_json::lept_stringify::lept_stringify_object(lept_value& value,lept_context& context)
{
    string res("{");
    vector<pair<string,lept_value>> o=value.get_lept_object();
    for(int i=0;i<o.size();i++)
    {
        if(i>0) res+=',';
        res+=lept_stringify_str(o[i].first);
        res+=':';
        lept_context tmp(res);
        lept_stringify_value(o[i].second,tmp);
        res=tmp.get_lept_context_string();
    }
    res+='}';
    return res;
}