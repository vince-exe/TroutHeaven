/* Database schema ( users ) */
const userSchema = require('../schema/userSchema')

exports.getPlayers = async (req, resp) => {
    let playersArray = await userSchema.find({})

    let response = []
    playersArray.forEach(player => {
        response.push(
            { 
                nickname: player.nickname,
                score: player.score,
                money: player.money
            })
    })
    resp.status(200).json({playersList: response})
}

exports.getNickname = async (req, resp) => {
    if(!req.body || !req.body.email) { return resp.sendStatus(422) }

    let user = await userSchema.findOne({email: req.body.email})

    if(!user) { return resp.sendStatus(404) }

    resp.status(200).json({nickname: user.nickname})
}
