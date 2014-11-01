var extension = require('bindings')('alienfx.node');

var assert = require('assert');


describe('exports: structural tests', function () {

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

        it('should be a function', function () {
            assert.equal(typeof extension.reset, 'function');
        });
    });


    describe('light()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.light, 'function');
        });
    });


    describe('update()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.update, 'function');
        });
    });


    describe('updateDefault()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.updateDefault, 'function');
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

        it('should be a function', function () {
            assert.equal(typeof extension.getNumDevices, 'function');
        });
    });


    describe('getDeviceDescription()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.getDeviceDescription, 'function');
        });
    });
});
