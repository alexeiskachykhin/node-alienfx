var extension = require('bindings')('alienfx.node');

var assert = require('assert');
var utilities = require('./utilities');


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

            utilities.ask.lightsAre('all turned off', function (answer) {
                extension.release();

                assert.ok(answer);
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

            utilities.ask.lightsAre('all turned green', function (answer) {
                extension.release();

                assert.ok(answer);
                done();
            });
        });
    });


    describe('update()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.update, 'function');
        });
    });

    describe('updateDefault()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.updateDefault, 'function');
        });

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


    describe('getNumDevices()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.getNumDevices, 'function');
        });

        it('should return a number of compatible devices', function (done) {
            utilities.ask.hasHardware(function (answer) {
                if (answer) {
                    extension.initialize();

                    assert.doesNotThrow(function () {
                        var number_of_devices = extension.getNumDevices();
                        console.info('Your system has %d AlienFX compatible devices.', number_of_devices);
                    });

                    extension.release();
                }
                else {
                    assert.ok(true);
                }

                done();
            });
        });

        it('should fail if system is not initialized', function () {
            assert.throws(function () {
                extension.getNumDevices();
            }, Error);
        });

        it('should fail if hardware not supported', function (done) {
            utilities.ask.hasHardware(function (answer) {
                if (answer) {
                    assert.ok(true);
                }
                else {
                    extension.initialize();

                    assert.throws(function () {
                        extension.getNumDevices();
                    }, Error);

                    extension.release();
                }

                done();
            });
        });
    });


    describe.only('getDeviceDescription()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.getDeviceDescription, 'function');
        });

        it('should get description of a device', function () {
            extension.initialize();
            extension.reset();

            var description = extension.getDeviceDescription(0);
            console.info('Description of your system:', description);

            assert.notEqual(description, null);
        });
    });
});
