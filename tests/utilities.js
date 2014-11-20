var inquirer = require('inquirer');
var assert = require('assert');


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
    var devices = {};
    extension.getNumDevicesSync(devices);

    for (var deviceIndex = 0; deviceIndex < devices.numberOfDevices; deviceIndex++) {
        var lights = {};
        extension.getNumLightsSync(deviceIndex, lights);

        for (var lightIndex = 0; lightIndex < lights.numberOfLights; lightIndex++) {
            checkLightColor(extension, color, deviceIndex, lightIndex);
        }
    }
}

function checkLightColor(extension, color, deviceIndex, lightIndex) {
    var currentColor = {};
    extension.getLightColorSync(deviceIndex, lightIndex, currentColor);

    assert.deepEqual(currentColor.lightColor, normalizeColor(color));
}

function normalizeColor(color) {
    var normalizedColor;

    switch (typeof color) {
        case 'object': {
            normalizedColor = color;
            break;
        }

        case 'number': {
            normalizedColor = {
                brightness: (color & 0xFF000000) >>> 24,
                red: (color & 0x00FF0000) >>> 16,
                green: (color & 0x0000FF00) >>> 8,
                blue: (color & 0x000000FF) >>> 0
            };

            break;
        }
    }

    return normalizedColor;
}

function isEqualColors(a, b) {
    var normalized_a = normalizeColor(a);
    var normalized_b = normalizeColor(b);

    assert.deepEqual(normalized_a, normalized_b);
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

    lightsAre: checkLightsColor,
    lightIs: checkLightColor,

    equalColors: isEqualColors
};