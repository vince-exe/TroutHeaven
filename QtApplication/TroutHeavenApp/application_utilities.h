#ifndef APPLICATIONUTILITIES_H
#define APPLICATIONUTILITIES_H

#include <QString>
#include <QMap>

#include <chrono>

using namespace std::chrono_literals;

class ApplicationUtilities {
public:
    static const QString loginAPiUrl;

    static const QString registrationPageUrl;

    static const QString getNicknameApiUrl;

    static const QString getPlayersList;

    static const QString getFishApiUrl;

    static const QString updtPlayerStatsAPIUrl;

    static const QString getPlayerStats;

    static QMap<QString, int> statsMap;

public:
    ApplicationUtilities();

};

namespace UserStats {
    static std::chrono::duration<uint64_t, std::ratio<1, 1>> fishTime = 5s;
}

namespace LoginErrors {
    static const QString Unauthorized = "Unauthorized";

    static const QString UnprocessableEntity = "Unprocessable Entity";

    static const QString NotFound = "Not Found";
}

#endif // APPLICATIONUTILITIES_H
