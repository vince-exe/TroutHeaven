/* Database schema ( users ) */
const userSchema = require('../schema/userSchema')

const fishList = require('../configs/fish.json').FishList

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
    let result = []
    fishList.forEach(fish => {
        result.push({name: fish.name, value: fish.value})
    })

    resp.status(200).json({ fishList: result })
}

exports.updtPlayerStats = async (req, resp) => {
    if (!req.body.email || !req.body.hasOwnProperty('cAcciuga') || !req.body.hasOwnProperty('cAnguilla') || !req.body.hasOwnProperty('cCalamaro') || !req.body.hasOwnProperty('cTotano') || !req.body.hasOwnProperty('cTonnetto') || !req.body.hasOwnProperty('cTrota')) {
        return resp.sendStatus(422)
    }

    let user = await userSchema.findOne({email: req.body.email})

    let userScore = user.score
    userScore 
        += (req.body.cAcciuga * fishList[0].score) 
        + (req.body.cAnguilla * fishList[1].score)
        + (req.body.cCalamaro * fishList[2].score)
        + (req.body.cTotano * fishList[3].score)
        + (req.body.cTonnetto * fishList[4].score)
        + (req.body.cTrota * fishList[5].score)
    
    let userMoney = user.money
    userMoney
        += (req.body.cAcciuga * fishList[0].value)
        + (req.body.cAnguilla * fishList[1].value)
        + (req.body.cCalamaro * fishList[2].value)
        + (req.body.cTotano * fishList[3].value)
        + (req.body.cTonnetto * fishList[4].value)
        + (req.body.cTrota * fishList[5].value)
    
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

exports.getPlayer = async (req, resp) => {
    if(!req.body.email) {
        return resp.sendStatus(422);
    }

    let user = await userSchema.findOne({email: req.body.email})
    if(!user) {
        return resp.sendStatus(404)
    }

    const final = {
        nickname: user.nickname,
        score: user.score,
        money: user.money
    }
    resp.status(200).json({user: final})
}

exports.updatePlayerScore = async (req, resp) => {
    if (!req.body.email || !req.body.hasOwnProperty('cAcciuga') || !req.body.hasOwnProperty('cAnguilla') || !req.body.hasOwnProperty('cCalamaro') || !req.body.hasOwnProperty('cTotano') || !req.body.hasOwnProperty('cTonnetto') || !req.body.hasOwnProperty('cTrota')) {
        return resp.sendStatus(422)
    }

    let user = await userSchema.findOne({email: req.body.email})
    let userScore = user.score

    userScore 
        += (req.body.cAcciuga * fishList[0].score)
        + (req.body.cAnguilla * fishList[1].score)
        + (req.body.cCalamaro * fishList[2].score)
        + (req.body.cTotano * fishList[3].score)
        + (req.body.cTonnetto * fishList[4].score)
        + (req.body.cTrota * fishList[5].score)

    await userSchema.updateOne(
        {
            email: req.body.email
        },
        {
            $set: {
                score: userScore
            }
        }
    )

    resp.sendStatus(200)
}

exports.updatePlayerMoney = async (req, resp) => {
    if (!req.body.email || !req.body.hasOwnProperty('cAcciuga') || !req.body.hasOwnProperty('cAnguilla') || !req.body.hasOwnProperty('cCalamaro') || !req.body.hasOwnProperty('cTotano') || !req.body.hasOwnProperty('cTonnetto') || !req.body.hasOwnProperty('cTrota')) {
        return resp.sendStatus(422)
    }

    let user = await userSchema.findOne({email: req.body.email})
    let userMoney = user.money
    
    userMoney 
        -= (req.body.cAcciuga * fishList[0].valueSell)
        + (req.body.cAnguilla * fishList[1].valueSell)
        + (req.body.cCalamaro * fishList[2].valueSell)
        + (req.body.cTotano * fishList[3].valueSell)
        + (req.body.cTonnetto * fishList[4].valueSell)
        + (req.body.cTrota * fishList[5].valueSell)
    
    if(userMoney < 0) {
        return resp.sendStatus(424)
    }

    await userSchema.updateOne(
        {
            email: req.body.email
        },
        {
            $set: {
                money: userMoney
            }
        }
    )

    resp.sendStatus(200)
}