#include "application_utilities.h"

const QString ApplicationUtilities::loginAPiUrl = "http://localhost:3000/login/api/v1/login";

const QString ApplicationUtilities::registrationPageUrl = "http://localhost:3000/views/registration.html";

const QString ApplicationUtilities::getNicknameApiUrl = "http://localhost:3000/homepage/api/v1/get-nickname";

const QString ApplicationUtilities::getPlayersList = "http://localhost:3000/homepage/api/v1/get-players";

const QString ApplicationUtilities::getFishApiUrl = "http://localhost:3000/homepage/api/v1/get-fish";

const QString ApplicationUtilities::updtPlayerStatsAPIUrl = "http://localhost:3000/homepage/api/v1/updt-player-stats";

const QString ApplicationUtilities::getPlayerStats = "http://localhost:3000/homepage/api/v1/get-player";

QMap<QString, int> ApplicationUtilities::statsMap;

ApplicationUtilities::ApplicationUtilities() {};
