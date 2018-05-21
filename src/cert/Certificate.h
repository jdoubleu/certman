#include <string>

using namespace std;

namespace cert {

class Certificate {
public:
    explicit Certificate(string location);

    string getLocation();

protected:
    string location;
};

}
