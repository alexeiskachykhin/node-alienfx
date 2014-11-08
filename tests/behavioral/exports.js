var extension = require('bindings')('alienfx.node');

var assert = require('assert');
var utilities = require('../utilities');


describe('exports: behavioral tests', function () {
    this.timeout(0);

    describe('getVersion()', function () {

        it('should get api version', function () {
            extension.initializeSync();

            var version = {};
            var result = extension.getVersion(version);

            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof version.result, 'string');

            console.info('API version is: %s', version.result);

            extension.releaseSync();
        });
    });


    describe('initialize()', function () {

        it('should initialize a system', function (done) {
            extension.initialize(function (err, data) {
                extension.releaseSync();

                assert.strictEqual(data.result, extension.Result.SUCCESS);
                done();
            });
        });
    });


    describe('initializeSync()', function () {

        it('should initialize a system', function () {
            var result = extension.initializeSync();
            extension.releaseSync();

            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });


    describe('release()', function () {

        it('should release a system', function (done) {
            extension.initializeSync();

            extension.release(function (err, data) {
                assert.strictEqual(data.result, extension.Result.SUCCESS);
                done();
            });
        });
    });


    describe('releaseSync()', function () {

        it('should release a system', function () {
            extension.initializeSync();
            var result = extension.releaseSync();

            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });


    describe('reset()', function () {

        it('should reset the lights', function () {
            extension.initializeSync();
            extension.reset();
            extension.update();

            assert.ok(utilities.lightsAre(extension, {
                red: 0x00,
                green: 0x00,
                blue: 0x00,
                brightness: 0xFF
            }));

            extension.releaseSync();
        });
    });


    describe('light()', function () {

        it('should color the lights', function () {
            extension.initializeSync();
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

            extension.releaseSync();
        });
    });


    describe('actionColor()', function () {

        it('should set action for lights', function () {
            extension.initializeSync();
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

            extension.releaseSync();
        });
    });


    describe('actionColorEx()', function () {

        it('should set action and both colors for lights', function () {
            extension.initializeSync();
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

            extension.releaseSync();
        });
    });


    describe('update()', function () {

        it('should send updates to a hardware', function () {
            extension.initializeSync();
            var result = extension.update();
            extension.releaseSync();

            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });


    describe('updateDefault()', function () {

        it('should set system power-on state', function () {
            extension.initializeSync();
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

            extension.releaseSync();
        });
    });


    describe('getNumDevices()', function () {

        it('should return a number of compatible devices', function (done) {
            extension.initializeSync();

            extension.getNumDevices(function (err, data) {
                extension.releaseSync();

                assert.strictEqual(data.result, extension.Result.SUCCESS);
                assert.strictEqual(typeof data.numberOfDevices, 'number');

                console.info('Your system has %d AlienFX compatible devices.', data.numberOfDevices);
                
                done();
            });
        });
    });


    describe('getNumDevicesSync()', function () {

        it('should return a number of compatible devices', function () {
            extension.initializeSync();

            var out = {};
            var result = extension.getNumDevicesSync(out);

            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.numberOfDevices, 'number');

            console.info('Your system has %d AlienFX compatible devices.', out.numberOfDevices);
        });
    });


    describe('getDeviceDescription()', function () {

        it('should get description of a device', function (done) {
            extension.initializeSync();

            extension.getDeviceDescription(0, function (err, data) {
                extension.releaseSync();

                assert.strictEqual(data.result, extension.Result.SUCCESS);
                assert.strictEqual(typeof data.model, 'string');
                assert.strictEqual(typeof data.type, 'number');

                console.info('Description of a first device:', data);

                done();
            });
        });
    });


    describe('getDeviceDescriptionSync()', function () {

        it('should get description of a device', function () {
            extension.initializeSync();

            var out = {};
            var result = extension.getDeviceDescriptionSync(0, out);

            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.model, 'string');
            assert.strictEqual(typeof out.type, 'number');

            console.info('Description of a first device:', out);
        });
    });


    describe('getNumLights()', function () {

        it('should get number of lights on a device', function (done) {
            extension.initializeSync();

            extension.getNumLights(0, function (err, data) {
                extension.releaseSync();

                assert.strictEqual(data.result, extension.Result.SUCCESS);
                assert.strictEqual(typeof data.numberOfLights, 'number');

                console.info('Your device has %d lights.', data.numberOfLights);

                done();
            });
        });
    });


    describe('getNumLightsSync()', function () {

        it('should get number of lights on a device', function () {
            extension.initializeSync();
            
            var out = {};
            var result = extension.getNumLightsSync(0, out);

            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.numberOfLights, 'number');

            console.info('Your device has %d lights.', out.numberOfLights);
        });
    });


    describe('getLightDescription()', function () {

        it('should get description of a light', function () {
            extension.initializeSync();

            var out = {};
            var result = extension.getLightDescription(0, 0, out);

            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(typeof out.result, 'string');

            console.info('Description of the first light of the first device:', out.result);
        });
    });


    describe('getLightLocation()', function () {

        it('should get location of a light', function () {
            extension.initializeSync();

            var out = {};
            var result = extension.getLightLocation(0, 0, out);

            extension.releaseSync();


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
            extension.initializeSync();
            extension.reset();

            var position = extension.Position.ALL;
            var color = extension.Color.RED | extension.Brightness.FULL;

            extension.light(position, color);
            extension.update();

            var out = {};
            var result = extension.getLightColor(0, 0, out);

            extension.releaseSync();


            var actualColor = out.blue | (out.green << 8) | (out.red << 16) | (out.brightness << 24);

            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.strictEqual(actualColor, color);
        });
    });


    describe('setLightColor()', function () {

        it('should set color of a light', function () {
            extension.initializeSync();
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
            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.deepEqual(out, color);
        });
    });


    describe('setLightActionColor()', function () {

        it('should set action of a light', function () {
            extension.initializeSync();
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
            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.deepEqual(out, color);
        });
    });


    describe('setLightActionColorEx()', function () {

        it('should set action and both colors of a light', function () {
            extension.initializeSync();
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
            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
            assert.deepEqual(out, primaryColor);
        });
    });


    describe('setTiming()', function () {

        it('should set timing of an action', function () {
            extension.initializeSync();
            extension.reset();

            var result = extension.setTiming(200);

            extension.update();
            extension.releaseSync();


            assert.strictEqual(result, extension.Result.SUCCESS);
        });
    });
});
