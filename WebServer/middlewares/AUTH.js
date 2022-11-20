const isAUTH = (req, resp, next) => {
    if(req.session.isAuth) {
        return next();
    }

    return resp.sendStatus(401)
}

module.exports = { isAUTH }
