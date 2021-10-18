#ifndef LEPT_VALUE
#define LEPT_VALUE

#include "globalSettings.h"
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

namespace lept_json
{
    class lept_value
    {
    public:
        lept_value():type(LEPT_NULL),number(0),str(""){}
        lept_value(lept_type t):type(t),number(0),str(""){}
        void set_lept_type(lept_type t) {type=t;}
        lept_type get_lept_type() {return type;}
        void set_lept_number(double n) {number=n;}
        double get_lept_number() {return number;}
        void set_lept_string(string s){str=s;}
        string get_lept_string() {return str;}
        int get_lept_array_size() {return array.size();}
        vector<lept_value> get_lept_array() {return array;}
        lept_value get_lept_array_element(int index) {assert(index<(int)array.size()); return array[index];}
        void set_lept_array_push(lept_value v) {array.push_back(v);}
        int get_lept_object_size() {return object.size();}
        vector<pair<string, lept_value>> get_lept_object() {return object;}
        pair<string, lept_value> get_lept_object_element(int index) {assert(index<(int)object.size()); return object[index];}
        void set_lept_object_push(pair<string,lept_value> p) {object.push_back(p);}

        void free_lept_value()
        {
            type=LEPT_NULL;
            number=0;
            str.clear();
            array.clear();
            object.clear();
        }
    protected:

    private:
        lept_type type;
        double number;
        string str;
        vector<lept_value> array;
        vector<pair<string, lept_value>> object;
    };
} // namespace lept_json

#endif
