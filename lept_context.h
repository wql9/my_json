#ifndef LEPT_CONTEXT
#define LEPT_CONTEXT

#include "globalSettings.h"
#include<string>
using namespace std;

namespace lept_json
{
    class lept_context
    {
    public:
        lept_context() {context=""; pos=0;}
        lept_context(string c):context(c){length=c.length();pos=0;}
        void set_lept_context(string c,int p) {context=c;length=c.length();pos=p;}
        void set_lept_context_pos(int p) {pos=p;}
        string get_lept_context_string() {return context;}
        int get_lept_context_length() {return length;}
        int get_lept_context_pos() {return pos;}
    protected:

    private:
        string context;
        int length;
        int pos;
    };
} // namespace lept_json

#endif
