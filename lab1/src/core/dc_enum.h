#ifndef DC_CORE_DC_ENUM_H_
#define DC_CORE_DC_ENUM_H_

namespace DC{
    namespace TYPE{
        enum TYPE{DC_INT, DC_BOOL, DC_STRING, DC_NAMED, DC_ARRAY, DC_VOID};
    };
    namespace CATEGORY{
        enum CATEGORY{DC_CLASS, DC_FUN, DC_VAR};
    };
};

#endif