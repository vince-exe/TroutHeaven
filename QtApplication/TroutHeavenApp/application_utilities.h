#ifndef APPLICATIONUTILITIES_H
#define APPLICATIONUTILITIES_H

#include <QString>
#include <unordered_map>

#include <unordered_map>
#include <string>

#include "fish.h"

class ApplicationUtilities {
public:
    static const QString loginAPiUrl;

    static const QString registrationPageUrl;

    static const QString getNicknameApiUrl;

    static const QString getPlayersList;

    static const std::unordered_map<std::string, Fish> fishMap;

public:
    ApplicationUtilities();

};

namespace LoginErrors {
    static const QString Unauthorized = "Unauthorized";

    static const QString UnprocessableEntity = "Unprocessable Entity";
}

#endif // APPLICATIONUTILITIES_H
