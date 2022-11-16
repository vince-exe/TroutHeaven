const express = require('express')
const router = express.Router()

const registrationController = require('../controllers/registrationController')

router.post('/api/v1/registration', registrationController.handleRegistration)

module.exports = router
