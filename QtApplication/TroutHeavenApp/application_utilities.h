#ifndef APPLICATIONUTILITIES_H
#define APPLICATIONUTILITIES_H

#include <QString>
#include <QMap>

#include <chrono>

#include "fish.h"

using namespace std::chrono_literals;

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

namespace UserStats {
    static std::chrono::duration<uint64_t, std::ratio<1, 1>> fishTime = 5s;
}

namespace LoginErrors {
    static const QString Unauthorized = "Unauthorized";

    static const QString UnprocessableEntity = "Unprocessable Entity";
}

#endif // APPLICATIONUTILITIES_H
