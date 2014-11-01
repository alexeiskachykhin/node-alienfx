var extension = require('bindings')('alienfx.node');

var assert = require('assert');


describe('exports: incompatible hardware tests', function () {

    describe('initialize()', function () {

    });


    describe('release()', function () {

    });


    describe('reset()', function () {

    });


    describe('light()', function () {

    });


    describe('update()', function () {

    });

    describe('updateDefault()', function () {

    });


    describe('getNumDevices()', function () {
        this.timeout(0);

        it('should fail if hardware not supported', function () {
            extension.initialize();

            assert.throws(function () {
                extension.getNumDevices();
            }, Error);

            extension.release();
        });
    });


    describe('getDeviceDescription()', function () {

    });

    describe('getNumLights()', function () {
        this.timeout(0);

        it('should fail if hardware not supported', function () {
            extension.initialize();

            assert.throws(function () {
                extension.getNumLights(0);
            }, Error);

            extension.release();
        });
    });
});
