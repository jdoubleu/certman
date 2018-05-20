#include "Certificate.h"

Certificate::Certificate(string location) {
    this->location = location;
}

string Certificate::getLocation() {
    return this->location;
}
