var extension = require('bindings')('alienfx.node');

var assert = require('assert');
var utilities = require('../utilities');


describe('exports: behavioral tests', function () {

    describe.only('getVersion()', function () {
        this.timeout(0);

        it('should get api version', function () {
            extension.initialize();

            var version = {};
            var result = extension.getVersion(version);

            assert.equal(result, extension.Result.SUCCESS);
            assert.equal(typeof version.result, 'string');

            console.info('API version is: %s', version.result);

            extension.release();
        });
    });


    describe('initialize()', function () {

    });


    describe('release()', function () {

    });


    describe('reset()', function () {
        this.timeout(0);

        it('should reset the lights', function () {
            extension.initialize();
            extension.reset();
            extension.update();

            assert.ok(utilities.lightsAre(extension, {
                red: 0x00,
                green: 0x00,
                blue: 0x00,
                brightness: 0xFF
            }));

            extension.release();
        });
    });


    describe('light()', function () {
        this.timeout(0);

        it('should color the lights', function () {
            extension.initialize();
            extension.reset();

            var position = extension.Position.ALL;
            var color = extension.Color.GREEN | extension.Brightness.FULL;

            extension.light(position, color);
            extension.update();

            assert.ok(utilities.lightsAre(extension, {
                red: 0x00,
                green: 0xFF,
                blue: 0x00,
                brightness: 0xFF
            }));

            extension.release();
        });
    });


    describe('update()', function () {

    });


    describe('updateDefault()', function () {
        this.timeout(0);

        it('should set system power-on state', function () {
            extension.initialize();
            extension.reset();

            var position = extension.Position.ALL;
            var color = extension.Color.RED | extension.Brightness.FULL;

            extension.light(position, color);
            extension.updateDefault();
            
            assert.ok(utilities.lightsAre(extension, {
                red: 0xFF,
                green: 0x00,
                blue: 0x00,
                brightness: 0xFF
            }));

            extension.release();
        });
    });


    describe('getNumDevices()', function () {
        this.timeout(0);

        it('should return a number of compatible devices', function () {
            extension.initialize();

            var out = {};
            var result = extension.getNumDevices(out);

            extension.release();


            assert.equal(result, extension.Result.SUCCESS);
            assert.equal(typeof out.result, 'number');

            console.info('Your system has %d AlienFX compatible devices.', out.result);
        });
    });


    describe('getDeviceDescription()', function () {
        this.timeout(0);

        it('should get description of a device', function () {
            extension.initialize();

            var out = {};
            var result = extension.getDeviceDescription(0, out);

            extension.release();


            assert.equal(result, extension.Result.SUCCESS);
            assert.equal(typeof out.model, 'string');
            assert.equal(typeof out.type, 'number');

            console.info('Description of a first device:', out);
        });
    });


    describe('getNumLights()', function () {
        this.timeout(0);

        it('should get number of lights on a device', function () {
            extension.initialize();
            
            var out = {};
            var result = extension.getNumLights(0, out);

            extension.release();


            assert.equal(result, extension.Result.SUCCESS);
            assert.equal(typeof out.result, 'number');

            console.info('Your device has %d lights.', out.result);
        });
    });


    describe('getLightDescription()', function () {
        this.timeout(0);

        it('should get description of a light', function () {
            extension.initialize();

            var out = {};
            var result = extension.getLightDescription(0, 0, out);

            extension.release();


            assert.equal(result, extension.Result.SUCCESS);
            assert.equal(typeof out.result, 'string');

            console.info('Description of the first light of the first device:', out.result);
        });
    });


    describe('getLightLocation()', function () {
        this.timeout(0);

        it('should get location of a light', function () {
            extension.initialize();

            var out = {};
            var result = extension.getLightLocation(0, 0, out);

            extension.release();


            /* Current version of AlienFX.dll doesn't provide any meningfull implementation 
             * of GetLightLocation, so for now, this test is useless. Might fallback to .NET version
             * or direct communication with HID device in the future.
             */
            assert.equal(result, result); 

            console.info('Location of the first light of the first device:', out.result);
        });
    });


    describe('getLightColor()', function () {
        this.timeout(0);

        it('should get color of a light', function () {
            extension.initialize();
            extension.reset();

            var position = extension.Position.ALL;
            var color = extension.Color.RED | extension.Brightness.FULL;

            extension.light(position, color);
            extension.update();

            var out = {};
            var result = extension.getLightColor(0, 0, out);

            extension.release();


            var actualColor = out.blue | (out.green << 8) | (out.red << 16) | (out.brightness << 24);

            assert.equal(result, extension.Result.SUCCESS);
            assert.equal(actualColor, color);

            console.info('Location of the first light of the first device:', out.result);
        });
    });


    describe('setLightColor()', function () {
        this.timeout(0);

        it('should set color of a light', function () {
            extension.initialize();
            extension.reset();

            var color = {
                red: 0xFF,
                green: 0x00,
                blue: 0x00,
                brightness: 0xFF
            };

            var result = extension.setLightColor(0, 0, color);
            extension.update();


            var out = {};
            extension.getLightColor(0, 0, out);
            extension.release();


            assert.equal(result, extension.Result.SUCCESS);
            assert.deepEqual(out, color);
        });
    });
});
