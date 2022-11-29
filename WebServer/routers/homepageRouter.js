const express = require('express')
const router = express.Router()

const middlewareAUTH = require('../middlewares/AUTH')
const homepageController = require('../controllers/homepageController')
const { route } = require('./registrationRouter')

router.route('/api/v1/get-players').get(homepageController.getPlayers)

router.route('/api/v1/get-nickname').post(homepageController.getNickname)

router.route('/api/v1/get-fish').get(homepageController.getFish)

router.route('/api/v1/updt-player-stats').post(homepageController.updtPlayerStats)

router.route('/api/v1/get-player').post(homepageController.getPlayer)

router.route('/api/v1/updt-player-score').post(homepageController.updatePlayerScore)

router.route('/api/v1/updt-player-money').post(homepageController.updatePlayerMoney)

module.exports = router
