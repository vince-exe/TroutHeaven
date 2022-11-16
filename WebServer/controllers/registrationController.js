/* Database schema ( users ) */
const userSchema = require('../schema/userSchema')

const applicationConfigs = require('../configs/application.json')

const utilities = require('../utils/utilities')

exports.handleRegistration = async (req, resp) => {
    if ((!req.body.email || !req.body.password || !req.body.nickname) || !utilities.Utils.checkEmail(req.body.email, applicationConfigs.domainsArray)) {
        return resp.sendStatus(422)
    }
    /* check the email and the nickname */
    if ((await userSchema.find({ email: req.body.email })).length != 0) {
        return resp.sendStatus(409)
    }
    if ((await userSchema.find({ nickname: req.body.nickname })).length != 0) {
        return resp.sendStatus(410)
    }

    try {
        await userSchema.create({
            email: req.body.email,
            password: req.body.password,
            nickname: req.body.nickname
        })
        return resp.sendStatus(200)
    }
    catch (err) {
        console.error(err)
        resp.sendStatus(500)
    }
}
