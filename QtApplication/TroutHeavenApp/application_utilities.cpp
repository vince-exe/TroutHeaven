#include "application_utilities.h"

const QString ApplicationUtilities::loginAPiUrl = "http://localhost:3000/login/api/v1/login";

const QString ApplicationUtilities::registrationPageUrl = "http://localhost:3000/views/registration.html";

const QString ApplicationUtilities::getNicknameApiUrl = "http://localhost:3000/homepage/api/v1/get-nickname";

const QString ApplicationUtilities::getPlayersList = "http://localhost:3000/homepage/api/v1/get-players";

const std::unordered_map<std::string, Fish> ApplicationUtilities::fishMap;

ApplicationUtilities::ApplicationUtilities() {};
