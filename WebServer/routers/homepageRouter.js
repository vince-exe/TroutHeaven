const express = require('express')
const router = express.Router()

const middlewareAUTH = require('../middlewares/AUTH')
const homepageController = require('../controllers/homepageController')

router.route('/api/v1/get-players')
.get
    (
        middlewareAUTH.isAUTH,
        homepageController.getPlayers
    )

module.exports = router
