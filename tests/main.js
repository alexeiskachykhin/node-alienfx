var extension = require('bindings')('alienfx.node');

var assert = require('assert');
var inquirer = require('inquirer');


describe('exports', function () {

    describe('initialize()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.initialize, 'function');
        });
    });


    describe('release()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.release, 'function');
        });
    });


    describe('reset()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.reset, 'function');
        });

        it('should reset the lights', function (done) {
            extension.initialize();
            extension.reset();
            extension.update();

            inquirer.prompt([{
                type: 'confirm',
                name: 'result',
                message: 'Can you confirm that your AlienFX lights are turned off?'
            }], function (answers) {
                extension.release();

                assert.ok(answers.result);
                done();
            });
        });
    });


    describe('light()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.light, 'function');
        });

        it('should color the lights', function (done) {
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
                extension.release();

                assert.ok(answers.result);
                done();
            });
        });
    });


    describe('Color', function () {

        it('should be an object', function () {
            assert.equal(typeof extension.Color, 'object');
        });

        it('should contain predefined colors constants', function () {
            assert.equal(extension.Color.OFF, 0x00000000);
            assert.equal(extension.Color.BLACK, 0x00000000);
            assert.equal(extension.Color.RED, 0x00FF0000);
            assert.equal(extension.Color.GREEN, 0x0000FF00);
            assert.equal(extension.Color.BLUE, 0x000000FF);
            assert.equal(extension.Color.WHITE, 0x00FFFFFF);
            assert.equal(extension.Color.YELLOW, 0x00FFFF00);
            assert.equal(extension.Color.ORANGE, 0x00FF8000);
            assert.equal(extension.Color.PINK, 0x00FF80FF);
            assert.equal(extension.Color.CYAN, 0x0000FFFF);
        });
    });


    describe('Brightness', function () {

        it('should be an object', function () {
            assert.equal(typeof extension.Brightness, 'object');
        });

        it('should contain predefined brightness constants', function () {
            assert.equal(extension.Brightness.FULL, 0xFF000000);
            assert.equal(extension.Brightness.HALF, 0x80000000);
            assert.equal(extension.Brightness.MIN, 0x00000000);
        });
    });
});
