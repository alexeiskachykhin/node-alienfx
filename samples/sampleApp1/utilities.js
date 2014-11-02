function waitForKeyPress(callback) {
    var readline = require('readline');

    var rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    rl.question("Press any key to continue...", function () {
        rl.close();

        if (typeof callback === 'function') {
            callback();
        }
    });
}

module.exports = exports = {
    waitForKeyPress: waitForKeyPress
};
