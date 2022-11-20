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