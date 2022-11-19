const express = require('express')
const router = express.Router()

router.get('/test', (req, resp) => {
    resp.sendStatus(200)
})

module.exports = router
