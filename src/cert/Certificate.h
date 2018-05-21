#include <string>

using std::string;

namespace cert {

    class Certificate {
    public:
        explicit Certificate(string location);

        string getLocation();

    protected:
        string location;
    };

}
