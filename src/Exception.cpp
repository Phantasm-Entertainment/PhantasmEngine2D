#include "PhEngine/Exception.h"

namespace PHENGINE_NAMESPACE
{
    std::ostream& operator<<(std::ostream& os, const PHENGINE_NAMESPACE::Exception& e)
    {
        os << "PhEngine::Exception!\n\nMessage: " << e.GetMessage() << "\n\nOccured at: "
        << e.GetLocation().file_name() << ' ' << e.GetLocation().function_name() <<
        ':' << std::to_string(e.GetLocation().line()) << ':' << std::to_string(e.GetLocation().column())
        << std::endl;
        return os;
    }
}