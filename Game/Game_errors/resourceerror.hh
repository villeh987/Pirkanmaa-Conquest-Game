#ifndef RESOURCEERROR_HH
#define RESOURCEERROR_HH

#include "exceptions/illegalaction.h"


namespace Game {


class ResourceError : public Course::IllegalAction
{
public:
    explicit ResourceError(const std::string& msg = ""):
        IllegalAction(msg){}

    virtual ~ResourceError() = default;

};




}


#endif // RESOURCEERROR_HH
