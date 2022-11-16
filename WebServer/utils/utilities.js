class Utils {
    static checkEmail = (email, domains) => {
        let check = false
        domains.forEach(domain => {
            if (email.includes(domain)) {
                check = true
            }
        })

        return check
    }
}

module.exports = { Utils }