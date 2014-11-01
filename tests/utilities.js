var inquirer = require('inquirer');


function confirmPrompt(message, callback) {
    inquirer.prompt([{
        type: 'confirm',
        name: 'result',
        message: message
    }], function (answers) {
        callback(answers.result);
    });
}

function checkboxPrompt(message, choices, callback) {
    inquirer.prompt([{
        type: 'checkbox',
        name: 'result',
        message: message,
        choices: choices
    }], function (answers) {
        var result = [];

        choices.forEach(function (choice, choiceIndex) {
            result[choiceIndex] = false;

            answers.result.forEach(function (answer) {
                if (choice === answer) {
                    result[choiceIndex] = true;
                }
            });
        });

        callback(result);
    });
}


function promptAboutLights(color, callback) {
    confirmPrompt('Can you confirm that your AlienFX lights are ' + color + '?', callback);
}

function promptAboutTests(choices, callback) {
    checkboxPrompt('Select tests', choices, callback);
}



module.exports = exports = {
    ask: {
        lightsAre: promptAboutLights,
        whichTestsToRun: promptAboutTests
    }
};