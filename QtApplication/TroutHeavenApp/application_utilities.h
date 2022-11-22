#ifndef APPLICATIONUTILITIES_H
#define APPLICATIONUTILITIES_H

#include <QString>
#include <unordered_map>

class ApplicationUtilities {
public:
    static const QString loginAPiUrl;

    static const QString registrationPageUrl;

public:
    ApplicationUtilities();

};

namespace LoginErrors {
    static const QString Unauthorized = "Unauthorized";

    static const QString UnprocessableEntity = "Unprocessable Entity";
}

#endif // APPLICATIONUTILITIES_H
