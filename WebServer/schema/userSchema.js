const mongoose = require('mongoose')

const userSchema = new mongoose.Schema({
    email: { type: String, required: true },
    password: { type: String, required: true },
    nickname: {type: String, required: true},
    score: {type: Number, default: 0},
    money: {type: Number, default: 0}
})

module.exports = mongoose.model('users', userSchema, 'users')