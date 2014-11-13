var inquirer = require('inquirer');


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


function promptAboutTests(choices, callback) {
    checkboxPrompt('Select tests', choices, callback);
}


function checkLightsColor(extension, color) {
    var result = true;

    var devices = {};
    extension.getNumDevicesSync(devices);

    for (var deviceIndex = 0; deviceIndex < devices.numberOfDevices; deviceIndex++) {
        var lights = {};
        extension.getNumLightsSync(deviceIndex, lights);

        for (var lightIndex = 0; lightIndex < lights.numberOfLights; lightIndex++) {
            var currentColor = {};
            extension.getLightColorSync(deviceIndex, lightIndex, currentColor);

            var isEqual =
                (currentColor.red === color.red &&
                currentColor.green === color.green &&
                currentColor.blue === color.blue &&
                currentColor.brightness === color.brightness);

            if (!isEqual) {
                return false;
            }
        }
    }

    return result;
}



module.exports = exports = {
    colors: {
        NONE: {
            red: 0,
            green: 0,
            blue: 0,
            brightness: 0
        }
    },

    functions: {
        empty: function () { }
    },

    ask: {
        whichTestsToRun: promptAboutTests
    },

    lightsAre: checkLightsColor
};