/* Database schema ( users ) */
const userSchema = require('../schema/userSchema')

const fishJson = require('../configs/fish.json')

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

exports.getFish = (req, resp) => {
    resp.json({fishList: require('../configs/fish.json').FishList})
}

exports.updtPlayerStats = async (req, resp) => {
    if (!req.body.email || !req.body.hasOwnProperty('cAcciuga') || !req.body.hasOwnProperty('cAnguilla') || !req.body.hasOwnProperty('cCalamaro') || !req.body.hasOwnProperty('cTotano') || !req.body.hasOwnProperty('cTonnetto') || !req.body.hasOwnProperty('cTrota')) {
        return resp.sendStatus(422)
    }

    let user = await userSchema.findOne({email: req.body.email})

    let userScore = user.score
    userScore 
        += (req.body.cAcciuga * fishJson.FishList[0].score) 
        + (req.body.cAnguilla * fishJson.FishList[1].score)
        + (req.body.cCalamaro * fishJson.FishList[2].score)
        + (req.body.cTotano * fishJson.FishList[3].score)
        + (req.body.cTonnetto * fishJson.FishList[4].score)
        + (req.body.cTrota * fishJson.FishList[5].score)
    
    let userMoney = user.money
    userMoney
        += (req.body.cAcciuga * fishJson.FishList[0].value)
        + (req.body.cAnguilla * fishJson.FishList[1].value)
        + (req.body.cCalamaro * fishJson.FishList[2].value)
        + (req.body.cTotano * fishJson.FishList[3].value)
        + (req.body.cTonnetto * fishJson.FishList[4].value)
        + (req.body.cTrota * fishJson.FishList[5].value)
    
    await userSchema.updateOne(
        {
            email: req.body.email
        },
        {
            $set: {
                score: userScore,
                money: userMoney
            }
        }
    )

    resp.sendStatus(200)
}