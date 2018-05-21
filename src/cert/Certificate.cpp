#include "Certificate.h"

cert::Certificate::Certificate(string location) {
    this->location = location;
}

string cert::Certificate::getLocation() {
    return this->location;
}
