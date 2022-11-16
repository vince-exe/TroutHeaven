/* Database schema ( users ) */
const userSchema = require('../schema/userSchema')

const applicationConfigs = require('../configs/application.json')

const utilities = require('../utils/utilities')

exports.handleLogin = async (req, resp) => {
    if ((!req.body.email || !req.body.password) || !utilities.Utils.checkEmail(req.body.email, applicationConfigs.domainsArray)) {
        return resp.sendStatus(422)
    }
    if (req.body.email.length > applicationConfigs.emailLen || req.body.password.length > applicationConfigs.passwordLen) {
        return resp.sendStatus(422)
    }

    const result = await userSchema.findOne({
        email: req.body.email,
        password: req.body.password
    })

    return (result) ? resp.sendStatus(200) : resp.sendStatus(401)
}