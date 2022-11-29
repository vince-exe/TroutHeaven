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

    static const QString updtPlayerScore;

    static const QString updtPlayerMoney;

    static QMap<QString, int> statsMap;

    static QMap<QString, int> storeMap;

public:
    ApplicationUtilities();

};

namespace UserStats {
    static std::chrono::duration<uint64_t, std::ratio<1, 1>> fishTime = 5s;
}

namespace ApiErrors {
    static const QString Unauthorized = "Unauthorized";

    static const QString UnprocessableEntity = "Unprocessable Entity";

    static const QString NotFound = "Not Found";

    static const QString InsufficientCredit = "Failed Dependency";
}

#endif // APPLICATIONUTILITIES_H
