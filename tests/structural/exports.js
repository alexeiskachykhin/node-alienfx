var extension = require('bindings')('alienfx.node');

var assert = require('assert');


describe('exports: structural tests', function () {

    describe('getVersion()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.getVersion, 'function');
        });

        it('should require atleast 1 parameter', function () {
            assert.doesNotThrow(function () {
                extension.getVersion({});
            });

            assert.throws(function () {
                extension.getVersion();
            }, Error);
        });

        it('should require first parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.getVersion({});
            });

            assert.throws(function () {
                extension.getVersion(0);
            }, TypeError);
        });
    });


    describe('initialize()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.initialize, 'function');
        });

        it('should not require any parameters', function () {
            assert.doesNotThrow(function () {
                extension.initialize();
            });

            extension.release();
        });
    });


    describe('release()', function () {
        this.timeout(0);

        it('should be a function', function () {
            assert.equal(typeof extension.release, 'function');
        });

        it('should not require any parameters', function () {
            assert.doesNotThrow(function () {
                extension.release();
            });
        });
    });


    describe('reset()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.reset, 'function');
        });

        it('should not require any parameters', function () {
            assert.doesNotThrow(function () {
                extension.reset();
            });
        });
    });


    describe('light()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.light, 'function');
        });

        it('should require atleast 2 parameters', function () {
            assert.doesNotThrow(function () {
                extension.light(0, 0);
            });

            assert.throws(function () {
                extension.light();
            }, Error);

            assert.throws(function () {
                extension.light(0);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.light(0, 0);
            });

            assert.throws(function () {
                extension.light({}, 0);
            }, TypeError);
        });

        it('should require second parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.light(0, 0);
            });

            assert.throws(function () {
                extension.light(0, {});
            }, TypeError);
        });

        it('should allow negative numbers as second parameter', function () {
            var color = (0x80000000 | 0);

            assert.doesNotThrow(function () {
                extension.light(0, color);
            });
        });
    });


    describe('actionColor()', function () {

        it('should be a function', function () {
            assert.strictEqual(typeof extension.actionColor, 'function');
        });

        it('should require atleast 3 parameters', function () {
            assert.doesNotThrow(function () {
                extension.actionColor(0, extension.Action.COLOR, 0);
            });

            assert.throws(function () {
                extension.actionColor();
            }, Error);

            assert.throws(function () {
                extension.actionColor(0, extension.Action.COLOR);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.actionColor(0, extension.Action.COLOR, 0);
            });

            assert.throws(function () {
                extension.actionColor({}, extension.Action.COLOR, 0);
            }, TypeError);
        });

        it('should require second parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.actionColor(0, extension.Action.COLOR, 0);
            });

            assert.throws(function () {
                extension.actionColor(0, {}, 0);
            }, TypeError);
        });

        it('should require third parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.actionColor(0, extension.Action.COLOR, 0);
            });

            assert.throws(function () {
                extension.actionColor(0, extension.Action.COLOR, {});
            }, TypeError);
        });

        it('should allow negative numbers as third parameter', function () {
            var color = (0x80000000 | 0);

            assert.doesNotThrow(function () {
                extension.actionColor(0, extension.Action.COLOR, color);
            });
        });
    });


    describe('update()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.update, 'function');
        });

        it('should not require any parameters', function () {
            assert.doesNotThrow(function () {
                extension.update();
            });
        });
    });


    describe('updateDefault()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.updateDefault, 'function');
        });

        it('should not require any parameters', function () {
            assert.doesNotThrow(function () {
                extension.updateDefault();
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


    describe('DeviceType', function () {

        it('should be an object', function () {
            assert.equal(typeof extension.DeviceType, 'object');
        });

        it('should contain predefined device type constants', function () {
            assert.equal(extension.DeviceType.UNKNOWN, 0x00);
            assert.equal(extension.DeviceType.NOTEBOOK, 0x01);
            assert.equal(extension.DeviceType.DESKTOP, 0x02);
            assert.equal(extension.DeviceType.SERVER, 0x03);
            assert.equal(extension.DeviceType.DISPLAY, 0x04);
            assert.equal(extension.DeviceType.MOUSE, 0x05);
            assert.equal(extension.DeviceType.KEYBOARD, 0x06);
            assert.equal(extension.DeviceType.GAMEPAD, 0x07);
            assert.equal(extension.DeviceType.SPEAKER, 0x08);
            assert.equal(extension.DeviceType.OTHER, 0xFF);
        });
    });


    describe('Position', function () {

        it('should be an object', function () {
            assert.equal(typeof extension.Position, 'object');
        });

        it('should contain predefined position constants', function () {

            // Near Z-plane light definitions
            assert.equal(extension.Position.FRONT_LOWER_LEFT, 0x00000001);
            assert.equal(extension.Position.FRONT_LOWER_CENTER, 0x00000002);
            assert.equal(extension.Position.FRONT_LOWER_RIGHT, 0x00000004);
            assert.equal(extension.Position.FRONT_MIDDLE_LEFT, 0x00000008);
            assert.equal(extension.Position.FRONT_MIDDLE_CENTER, 0x00000010);
            assert.equal(extension.Position.FRONT_MIDDLE_RIGHT, 0x00000020);
            assert.equal(extension.Position.FRONT_UPPER_LEFT, 0x00000040);
            assert.equal(extension.Position.FRONT_UPPER_CENTER, 0x00000080);
            assert.equal(extension.Position.FRONT_UPPER_RIGHT, 0x00000100);

            // Mid Z-plane light definitions
            assert.equal(extension.Position.MIDDLE_LOWER_LEFT, 0x00000200);
            assert.equal(extension.Position.MIDDLE_LOWER_CENTER, 0x00000400);
            assert.equal(extension.Position.MIDDLE_LOWER_RIGHT, 0x00000800);
            assert.equal(extension.Position.MIDDLE_MIDDLE_LEFT, 0x00001000);
            assert.equal(extension.Position.MIDDLE_MIDDLE_CENTER, 0x00002000);
            assert.equal(extension.Position.MIDDLE_MIDDLE_RIGHT, 0x00004000);
            assert.equal(extension.Position.MIDDLE_UPPER_LEFT, 0x00008000);
            assert.equal(extension.Position.MIDDLE_UPPER_CENTER, 0x00010000);
            assert.equal(extension.Position.MIDDLE_UPPER_RIGHT, 0x00020000);

            // Far Z-plane light definitions
            assert.equal(extension.Position.REAR_LOWER_LEFT, 0x00040000);
            assert.equal(extension.Position.REAR_LOWER_CENTER, 0x00080000);
            assert.equal(extension.Position.REAR_LOWER_RIGHT, 0x00100000);
            assert.equal(extension.Position.REAR_MIDDLE_LEFT, 0x00200000);
            assert.equal(extension.Position.REAR_MIDDLE_CENTER, 0x00400000);
            assert.equal(extension.Position.REAR_MIDDLE_RIGHT, 0x00800000);
            assert.equal(extension.Position.REAR_UPPER_LEFT, 0x01000000);
            assert.equal(extension.Position.REAR_UPPER_CENTER, 0x02000000);
            assert.equal(extension.Position.REAR_UPPER_RIGHT, 0x04000000);

            // Combination bit masks
            assert.equal(extension.Position.ALL, 0x07FFFFFF);
            assert.equal(extension.Position.ALL_RIGHT, 0x04924924);
            assert.equal(extension.Position.ALL_LEFT, 0x01249249);
            assert.equal(extension.Position.ALL_UPPER, 0x070381C0);
            assert.equal(extension.Position.ALL_LOWER, 0x001C0E07);
            assert.equal(extension.Position.ALL_FRONT, 0x000001FF);
            assert.equal(extension.Position.ALL_REAR, 0x07FC0000);
        });
    });


    describe('Result', function () {

        it('should be an object', function () {
            assert.equal(typeof extension.Result, 'object');
        });

        it('should contain predefined result constants', function () {
            assert.equal(extension.Result.SUCCESS, 0x00);
            assert.equal(extension.Result.FAILURE, 0x01);
            assert.equal(extension.Result.NOINIT, 0x02);
            assert.equal(extension.Result.NODEVS, 0x03);
            assert.equal(extension.Result.NOLIGHTS, 0x04);
            assert.equal(extension.Result.BUFFSIZE, 0x05);
        });
    });


    describe('Action', function () {
        
        it('should be an object', function () {
            assert.equal(typeof extension.Action, 'object');
        });

        it('should contain predefined action constants', function () {
            assert.equal(extension.Action.MORPH, 0x00000001);
            assert.equal(extension.Action.PULSE, 0x00000002);
            assert.equal(extension.Action.COLOR, 0x00000003);
        });
    });


    describe('isAvailable', function () {

        it('should be a boolean', function () {
            assert.equal(typeof extension.isAvailable, 'boolean');
        });
    });


    describe('getNumDevices()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.getNumDevices, 'function');
        });

        it('should require atleast 1 parameter', function () {
            assert.doesNotThrow(function () {
                extension.getNumDevices({});
            });

            assert.throws(function () {
                extension.getNumDevices();
            }, Error);
        });

        it('should require first parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.getNumDevices({});
            });

            assert.throws(function () {
                extension.getNumDevices(0);
            }, TypeError);
        });
    });


    describe('getDeviceDescription()', function () {

       it('should be a function', function () {
            assert.equal(typeof extension.getDeviceDescription, 'function');
        });

        it('should require atleast 2 parameters', function () {
            assert.doesNotThrow(function () {
                extension.getDeviceDescription(0, {});
            });

            assert.throws(function () {
                extension.getDeviceDescription();
            }, Error);

            assert.throws(function () {
                extension.getDeviceDescription(0);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getDeviceDescription(0, {});
            });

            assert.throws(function () {
                extension.getDeviceDescription({}, {});
            }, TypeError);
        });

        it('should require second parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.getDeviceDescription(0, {});
            });

            assert.throws(function () {
                extension.getDeviceDescription(0, 0);
            }, TypeError);
        });
    });


    describe('getNumLights()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.getNumLights, 'function');
        });

        it('should require atleast 2 parameters', function () {
            assert.doesNotThrow(function () {
                extension.getNumLights(0, {});
            });

            assert.throws(function () {
                extension.getNumLights();
            }, Error);

            assert.throws(function () {
                extension.getNumLights(0);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getNumLights(0, {});
            });

            assert.throws(function () {
                extension.getNumLights({}, {});
            }, TypeError);
        });

        it('should require second parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.getNumLights(0, {});
            });

            assert.throws(function () {
                extension.getNumLights(0, 0);
            }, TypeError);
        });
    });


    describe('getLightDescription()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.getLightDescription, 'function');
        });

        it('should require atleast 3 parameters', function () {
            assert.doesNotThrow(function () {
                extension.getLightDescription(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightDescription();
            }, Error);

            assert.throws(function () {
                extension.getLightDescription(0);
            }, Error);

            assert.throws(function () {
                extension.getLightDescription(0, 0);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getLightDescription(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightDescription({}, 0, {});
            }, TypeError);
        });

        it('should require second parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getLightDescription(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightDescription(0, {}, {});
            }, TypeError);
        });

        it('should require third parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.getLightDescription(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightDescription(0, 0, 0);
            }, TypeError);
        });
    });


    describe('getLightLocation()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.getLightLocation, 'function');
        });

        it('should require atleast 3 parameters', function () {
            assert.doesNotThrow(function () {
                extension.getLightLocation(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightLocation();
            }, Error);

            assert.throws(function () {
                extension.getLightLocation(0);
            }, Error);

            assert.throws(function () {
                extension.getLightLocation(0, 0);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getLightLocation(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightLocation({}, 0, {});
            }, TypeError);
        });

        it('should require second parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getLightLocation(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightLocation(0, {}, {});
            }, TypeError);
        });

        it('should require third parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.getLightLocation(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightLocation(0, 0, 0);
            }, TypeError);
        });
    });


    describe('getLightColor()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.getLightColor, 'function');
        });

        it('should require atleast 3 parameters', function () {
            assert.doesNotThrow(function () {
                extension.getLightColor(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightColor();
            }, Error);

            assert.throws(function () {
                extension.getLightColor(0);
            }, Error);

            assert.throws(function () {
                extension.getLightColor(0, 0);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getLightColor(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightColor({}, 0, {});
            }, TypeError);
        });

        it('should require second parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.getLightColor(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightColor(0, {}, {});
            }, TypeError);
        });

        it('should require third parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.getLightColor(0, 0, {});
            });

            assert.throws(function () {
                extension.getLightColor(0, 0, 0);
            }, TypeError);
        });
    });


    describe('setLightColor()', function () {

        it('should be a function', function () {
            assert.equal(typeof extension.setLightColor, 'function');
        });

        it('should require atleast 3 parameters', function () {
            assert.doesNotThrow(function () {
                extension.setLightColor(0, 0, {
                    red: 0x00,
                    green: 0x00,
                    blue: 0x00,
                    brightness: 0x00,
                });
            });

            assert.throws(function () {
                extension.setLightColor();
            }, Error);

            assert.throws(function () {
                extension.setLightColor(0);
            }, Error);

            assert.throws(function () {
                extension.setLightColor(0, 0);
            }, Error);
        });

        it('should require first parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.setLightColor(0, 0, {
                    red: 0x00,
                    green: 0x00,
                    blue: 0x00,
                    brightness: 0x00,
                });
            });

            assert.throws(function () {
                extension.setLightColor({}, 0, {});
            }, TypeError);
        });

        it('should require second parameter of type number', function () {
            assert.doesNotThrow(function () {
                extension.setLightColor(0, 0, {
                    red: 0x00,
                    green: 0x00,
                    blue: 0x00,
                    brightness: 0x00,
                });
            });

            assert.throws(function () {
                extension.setLightColor(0, {}, {});
            }, TypeError);
        });

        it('should require third parameter of type object', function () {
            assert.doesNotThrow(function () {
                extension.setLightColor(0, 0, {
                    red: 0x00,
                    green: 0x00,
                    blue: 0x00,
                    brightness: 0x00,
                });
            });

            assert.throws(function () {
                extension.setLightColor(0, 0, 0);
            }, TypeError);
        });
    });

});
