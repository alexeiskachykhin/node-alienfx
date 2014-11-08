var extension = require('bindings')('alienfx.node');


if (extension.isAvailable) {
    var result = extension.initializeSync();

    if (result === extension.Result.SUCCESS) {
        var out = {};
        extension.getNumDevicesSync(out);

        console.info('Devices: %d', out.numberOfDevices);


        for (var deviceIndex = 0; deviceIndex < out.numberOfDevices; deviceIndex++) {
            var deviceDescription = {};
            extension.getDeviceDescriptionSync(deviceIndex, deviceDescription);

            console.info('Description: %s', deviceDescription.model);


            var lights = {};
            extension.getNumLightsSync(deviceIndex, lights);

            for (var lightIndex = 0; lightIndex < lights.numberOfLights; lightIndex++) {
                var lightDescription = {};
                result = extension.getLightDescription(deviceIndex, lightIndex, lightDescription);

                if (result !== extension.Result.SUCCESS) {
                    continue;
                }

                console.info('Light: %d\tDescription: %s', lightIndex, lightDescription.result);
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
