var inquirer = require('inquirer');


function prompt(message, callback) {
    inquirer.prompt([{
        type: 'confirm',
        name: 'result',
        message: message
    }], function (answers) {
        callback(answers.result);
    });
}

function promptAboutHardware(callback) {
    prompt('Can you confirm that your hardware is compatible with AlienFX?', callback);
}

function promptAboutLights(color, callback) {
    prompt('Can you confirm that your AlienFX lights are ' + color + '?', callback);
}


module.exports = exports = {
    ask: {
        lightsAre: promptAboutLights,
        hasHardware: promptAboutHardware
    }
};