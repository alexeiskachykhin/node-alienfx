var extension = require('bindings')('alienfx.node');


if (extension.isAvailable) {
    var result = extension.initializeSync();

    if (result === extension.Result.SUCCESS) {
        extension.reset();

        var devices = {};
        extension.getNumDevicesSync(devices);

        for (var deviceIndex = 0; deviceIndex < devices.numberOfDevices; deviceIndex++) {
            var lights = {};
            extension.getNumLightsSync(deviceIndex, lights);

            for (var lightIndex = 0; lightIndex < lights.numberOfLights; lightIndex++) {
                var redColor = {
                    red: 0xFF,
                    green: 0x00,
                    blue: 0x00,
                    brightness: 0xFF
                };

                var blueColor = {
                    red: 0x00,
                    green: 0x00,
                    blue: 0xFF,
                    brightness: 0xFF
                };

                var actualColor = (lightIndex % 2 === 0) ? redColor : blueColor;

                extension.setLightColor(deviceIndex, lightIndex, actualColor);
            }
        }

        extension.update();


        for (var deviceIndex = 0; deviceIndex < devices.numberOfDevices; deviceIndex++) {
            var deviceDescription = {};
            extension.getDeviceDescriptionSync(deviceIndex, deviceDescription);

            console.info('Description: %s', deviceDescription.model);


            var lights = {};
            extension.getNumLightsSync(deviceIndex, lights);

            for (var lightIndex = 0; lightIndex < lights.numberOfLights; lightIndex++) {
                var light = {};
                result = extension.getLightDescriptionSync(deviceIndex, lightIndex, light);

                if (result !== extension.Result.SUCCESS) {
                    continue;
                }


                var color = {};
                result = extension.getLightColor(deviceIndex, lightIndex, color);

                if (result !== extension.Result.SUCCESS) {
                    continue;
                }


                console.info('Light: %d\tDescription: %s\tColor: %j', lightIndex, light.lightDescription, color);
            }
        }


        require('./utilities').waitForKeyPress(function () {
            extension.releaseSync();
        });
    }
    else {
        switch (result) {
            case extension.Result.NODEVS:
                console.error('There are no AlienFX devices available.');
                break;

            default:
                console.error('There was an error initializing the AlienFX device.');
                break;
        }
    }
}
else {
    console.error('Failed to load LightFX.dll.');
}
