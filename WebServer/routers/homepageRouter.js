const express = require('express')
const router = express.Router()

const middlewareAUTH = require('../middlewares/AUTH')
const homepageController = require('../controllers/homepageController')

router.route('/api/v1/get-players').get(homepageController.getPlayers)

router.route('/api/v1/get-nickname').post(homepageController.getNickname)

router.route('/api/v1/get-fish').get(homepageController.getFish)

module.exports = router
