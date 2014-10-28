var extension = require('bindings')('alienfx.node');
var inquirer = require('inquirer');

exports.index = {
    'has initialize': function (test) {
        test.equal('function', typeof extension.initialize);
        test.done();
    },


    'has release': function (test) {
        test.equal('function', typeof extension.release);
        test.done();
    },


    'has reset': function (test) {
        test.equal('function', typeof extension.reset);
        test.done();
    },

    'reset should reset the lights': function (test) {
        extension.initialize();
        extension.reset();
        extension.update();

        inquirer.prompt([{
            type: 'confirm',
            name: 'result',
            message: 'Can you confirm that your AlienFX lights are turned off?'
        }], function (answers) {
            test.ok(answers.result);
            test.done();

            extension.release();
        });
    },


    'has light': function (test) {
        test.equal('function', typeof extension.light);
        test.done();
    },

    'light should color the lights': function (test) {
        extension.initialize();
        extension.reset();

        var position = 0x07FFFFFF; // All lights
        var color = 0xFF00FF00; // Green color + Full brightness

        extension.light(position, color);
        extension.update();

        inquirer.prompt([{
            type: 'confirm',
            name: 'result',
            message: 'Can you confirm that your AlienFX lights are all turned green?'
        }], function (answers) {
            test.ok(answers.result);
            test.done();

            extension.release();
        });
    }
};
