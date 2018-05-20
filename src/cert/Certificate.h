#include <string>

using namespace std;

class Certificate {
public:
    explicit Certificate(string location);
    string getLocation();

protected:
    string location;
};

