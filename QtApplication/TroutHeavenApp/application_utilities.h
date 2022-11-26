#ifndef APPLICATIONUTILITIES_H
#define APPLICATIONUTILITIES_H

#include <QString>
#include <QMap>

#include <string>

#include "fish.h"

class ApplicationUtilities {
public:
    static const QString loginAPiUrl;

    static const QString registrationPageUrl;

    static const QString getNicknameApiUrl;

    static const QString getPlayersList;

    static const QString getFishApiUrl;

    static const QString updtPlayerStatsAPIUrl;

    static QMap<QString, Fish> fishMap;

public:
    ApplicationUtilities();

};

namespace LoginErrors {
    static const QString Unauthorized = "Unauthorized";

    static const QString UnprocessableEntity = "Unprocessable Entity";
}

#endif // APPLICATIONUTILITIES_H
