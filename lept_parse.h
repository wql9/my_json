#include "globalSettings.h"
#include "lept_context.h"
#include "lept_value.h"
#include <assert.h>

namespace lept_json
{
    class lept_parse
    {
    public:
        int lept_parse_all(lept_value& value, lept_context& context);
        int lept_parse_NTF(lept_value& value, lept_context& context, string expect);
        void lept_parse_whitespace(lept_context& context);
        int lept_parse_value(lept_value& value, lept_context& context);
        void lept_free(lept_value& value);
        int lept_parse_number(lept_value& value, lept_context& context);
        int lept_parse_string(lept_value& value, lept_context& context);
        int lept_parse_unicode(string& strIn, string& strOut, int& posIn);
        bool lept_parse_unicode_hex4(string& strIn, int& posIn,unsigned int& u);
        void lept_encode_utf8(string& strOut, unsigned int& u);
        int lept_parse_array(lept_value& value, lept_context& context);
        int lept_parse_object(lept_value& value, lept_context& context);
    protected:

    private:

    };
} // namespace lept_json
