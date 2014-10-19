#include "..\..\..\include\libipcpp\libipcpp.h"

#ifdef _MSC_VER
namespace ipc {
    ReferenceType::ReferenceType(ReferenceType&&)
    {
    }

    ReferenceType& ReferenceType::operator=(ReferenceType&&)
    {
        return *this;
    }
}
#endif
