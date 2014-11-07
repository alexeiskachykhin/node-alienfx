var extension = require('bindings')('alienfx.node');


if (extension.isAvailable) {
    var result = extension.initializeSync();

    if (result === extension.Result.SUCCESS) {
        extension.reset();

        var numberOfDevices = {};
        extension.getNumDevices(numberOfDevices);

        for (var deviceIndex = 0; deviceIndex < numberOfDevices.result; deviceIndex++) {
            var numberOfLights = {};
            extension.getNumLights(deviceIndex, numberOfLights);

            for (var lightIndex = 0; lightIndex < numberOfLights.result; lightIndex++) {
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


        for (var deviceIndex = 0; deviceIndex < numberOfDevices.result; deviceIndex++) {
            var deviceDescription = {};
            extension.getDeviceDescription(deviceIndex, deviceDescription);

            console.info('Description: %s', deviceDescription.model);


            var numberOfLights = {};
            extension.getNumLights(deviceIndex, numberOfLights);

            for (var lightIndex = 0; lightIndex < numberOfLights.result; lightIndex++) {
                var lightDescription = {};
                result = extension.getLightDescription(deviceIndex, lightIndex, lightDescription);

                if (result !== extension.Result.SUCCESS) {
                    continue;
                }


                var color = {};
                result = extension.getLightColor(deviceIndex, lightIndex, color);

                if (result !== extension.Result.SUCCESS) {
                    continue;
                }


                console.info('Light: %d\tDescription: %s\tColor: %j', lightIndex, lightDescription.result, color);
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
