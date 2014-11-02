var extension = require('bindings')('alienfx.node');


if (extension.isAvailable) {
    var result = extension.initialize();

    if (result === extension.Result.SUCCESS) {
        var numberOfDevices = {};
        extension.getNumDevices(numberOfDevices);

        console.info('Devices: %d', numberOfDevices.result);


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

                console.info('Light: %d\tDescription: %s', lightIndex, lightDescription.result);
            }
        }


        require('./utilities').waitForKeyPress(function () {
            extension.release();
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
