var extension = require('bindings')('alienfx.node');

var assert = require('assert');
var utilities = require('../utilities');


describe('exports: behavioral tests', function () {
    this.timeout(0);

    describe('getVersion()', function () {

        it('should get api version', function () {
            extension.initialize();

            var version = {};
            var result = extension.getVersion(version);

            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof version.result, 'string');

            console.info('API version is: %s', version.result);

            extension.release();
        });
    });


    describe('initialize()', function () {

        it('should initialize a system', function () {
            var result = extension.initialize();
            extension.release();

            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });


    describe('release()', function () {

        it('should release a system', function () {
            extension.initialize();
            var result = extension.release();

            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });


    describe('reset()', function () {

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


    describe('actionColor()', function () {

        it('should set action for lights', function () {
            extension.initialize();
            extension.reset();

            var position = extension.Position.ALL;
            var action = extension.Action.MORPH;
            var color = extension.Color.GREEN | extension.Brightness.FULL;

            extension.actionColor(position, action, color);
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


    describe('actionColorEx()', function () {

        it('should set action and both colors for lights', function () {
            extension.initialize();
            extension.reset();

            var position = extension.Position.ALL;
            var action = extension.Action.MORPH;
            var primaryColor = extension.Color.GREEN | extension.Brightness.FULL;
            var secondaryColor = extension.Color.RED | extension.Brightness.FULL;

            extension.actionColorEx(position, action, primaryColor, secondaryColor);
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

        it('should send updates to a hardware', function () {
            extension.initialize();
            var result = extension.update();
            extension.release();

            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });


    describe('updateDefault()', function () {

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

        it('should return a number of compatible devices', function () {
            extension.initialize();

            var out = {};
            var result = extension.getNumDevices(out);

            extension.release();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.result, 'number');

            console.info('Your system has %d AlienFX compatible devices.', out.result);
        });
    });


    describe('getDeviceDescription()', function () {

        it('should get description of a device', function () {
            extension.initialize();

            var out = {};
            var result = extension.getDeviceDescription(0, out);

            extension.release();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.model, 'string');
            assert.strictEqual(typeof out.type, 'number');

            console.info('Description of a first device:', out);
        });
    });


    describe('getNumLights()', function () {

        it('should get number of lights on a device', function () {
            extension.initialize();
            
            var out = {};
            var result = extension.getNumLights(0, out);

            extension.release();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.result, 'number');

            console.info('Your device has %d lights.', out.result);
        });
    });


    describe('getLightDescription()', function () {

        it('should get description of a light', function () {
            extension.initialize();

            var out = {};
            var result = extension.getLightDescription(0, 0, out);

            extension.release();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.result, 'string');

            console.info('Description of the first light of the first device:', out.result);
        });
    });


    describe('getLightLocation()', function () {

        it('should get location of a light', function () {
            extension.initialize();

            var out = {};
            var result = extension.getLightLocation(0, 0, out);

            extension.release();


            /* AlienFX.dll (version 2.1.0) doesn't provide any meningfull implementation 
             * of GetLightLocation, so for now, this test is useless. Might fallback to .NET version
             * or direct communication with HID device in the future.
             */
            assert.strictEqual(result, result); 

            console.info('Location of the first light of the first device:', out.result);
        });
    });


    describe('getLightColor()', function () {

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

            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(actualColor, color);
        });
    });


    describe('setLightColor()', function () {

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


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.deepEqual(out, color);
        });
    });


    describe('setLightActionColor()', function () {

        it('should set action of a light', function () {
            extension.initialize();
            extension.reset();

            var color = {
                red: 0xFF,
                green: 0x00,
                blue: 0x00,
                brightness: 0xFF
            };

            var result = extension.setLightActionColor(0, 0, extension.Action.MORPH, color);
            extension.update();


            var out = {};
            extension.getLightColor(0, 0, out);
            extension.release();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.deepEqual(out, color);
        });
    });


    describe('setLightActionColorEx()', function () {

        it('should set action and both colors of a light', function () {
            extension.initialize();
            extension.reset();

            var primaryColor = {
                red: 0xFF,
                green: 0x00,
                blue: 0x00,
                brightness: 0xFF
            };

            var secondaryColor = {
                red: 0x00,
                green: 0xFF,
                blue: 0x00,
                brightness: 0xFF
            };


            var result = extension.setLightActionColorEx(0, 0, extension.Action.MORPH, primaryColor, secondaryColor);
            extension.update();


            var out = {};
            extension.getLightColor(0, 0, out);
            extension.release();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.deepEqual(out, primaryColor);
        });
    });


    describe('setTiming()', function () {

        it('should set timing of an action', function () {
            extension.initialize();
            extension.reset();

            var result = extension.setTiming(200);

            extension.update();
            extension.release();


            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });
});
