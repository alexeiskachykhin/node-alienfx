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
        var color = extension.Color.GREEN | extension.Brightness.FULL;

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
    },


    'has color': function (test) {
        test.equal('object', typeof extension.Color);
        test.done();
    },

    'has predefined colors': function (test) {
        test.equal(0x00000000, extension.Color.OFF);
        test.equal(0x00000000, extension.Color.BLACK);
        test.equal(0x00FF0000, extension.Color.RED);
        test.equal(0x0000FF00, extension.Color.GREEN);
        test.equal(0x000000FF, extension.Color.BLUE);
        test.equal(0x00FFFFFF, extension.Color.WHITE);
        test.equal(0x00FFFF00, extension.Color.YELLOW);
        test.equal(0x00FF8000, extension.Color.ORANGE);
        test.equal(0x00FF80FF, extension.Color.PINK);
        test.equal(0x0000FFFF, extension.Color.CYAN);

        test.done();
    },


    'has brightness': function (test) {
        test.equal('object', typeof extension.Brightness);
        test.done();
    },

    'has predefined brightness': function (test) {
        test.equal(0xFF000000, extension.Brightness.FULL);
        test.equal(0x80000000, extension.Brightness.HALF);
        test.equal(0x00000000, extension.Brightness.MIN);
        test.done();
    }
};
