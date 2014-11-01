var extension = require('bindings')('alienfx.node');

var assert = require('assert');
var utilities = require('../utilities');


describe('exports: compatible hardware tests', function () {

    describe('initialize()', function () {

    });


    describe('release()', function () {

    });


    describe('reset()', function () {
        this.timeout(0);

        it('should reset the lights', function (done) {
            extension.initialize();
            extension.reset();
            extension.update();

            utilities.ask.lightsAre('all turned off', function (answer) {
                extension.release();

                assert.ok(answer);
                done();
            });
        });
    });


    describe('light()', function () {
        this.timeout(0);

        it('should color the lights', function (done) {
            extension.initialize();
            extension.reset();

            var position = 0x07FFFFFF; // All lights
            var color = extension.Color.GREEN | extension.Brightness.FULL;

            extension.light(position, color);
            extension.update();

            utilities.ask.lightsAre('all turned green', function (answer) {
                extension.release();

                assert.ok(answer);
                done();
            });
        });
    });


    describe('update()', function () {

    });


    describe('updateDefault()', function () {
        this.timeout(0);

        it('should set system power-on state', function (done) {
            extension.initialize();
            extension.reset();

            var position = 0x07FFFFFF; // All lights
            var color = extension.Color.RED | extension.Brightness.FULL;

            extension.light(position, color);
            extension.updateDefault();
            extension.release();

            utilities.ask.lightsAre('all turned red (it may not work on some hardware)', function (answer) {
                assert.ok(answer);
                done();
            });
        });
    });


    describe('getNumDevices()', function () {
        this.timeout(0);

        it('should return a number of compatible devices', function () {
            extension.initialize();

            assert.doesNotThrow(function () {
                var number_of_devices = extension.getNumDevices();
                console.info('Your system has %d AlienFX compatible devices.', number_of_devices);
            });

            extension.release();
        });

        it('should fail if system is not initialized', function () {
            assert.throws(function () {
                extension.getNumDevices();
            }, Error);
        });
    });


    describe('getDeviceDescription()', function () {
        this.timeout(0);

        it('should get description of a device', function () {
            extension.initialize();
            extension.reset();

            var description = extension.getDeviceDescription(0);
            console.info('Description of your system:', description);

            extension.release();

            assert.notEqual(description, null);
        });
    });
});
