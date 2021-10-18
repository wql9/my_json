#include "globalSettings.h"
#include "lept_value.h"
#include "lept_context.h"

namespace lept_json
{
    class lept_stringify
    {
    public:
        void lept_stringify_all(lept_value& value, lept_context& context);
        void lept_stringify_value(lept_value& value, lept_context& context);
        string lept_stringify_number(lept_value& value);
        string lept_stringify_str(string str);
        string lept_stringify_array(lept_value& value,lept_context& context);
        string lept_stringify_object(lept_value& value,lept_context& context);
    protected:

    private:

    };
} // namespace lept_json
