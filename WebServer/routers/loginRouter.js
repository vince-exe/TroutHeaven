const express = require('express')
const router = express.Router()

const loginCotroller = require('../controllers/loginControllers')

router.post('/api/v1/login', loginCotroller.handleLogin)

module.exports = router
