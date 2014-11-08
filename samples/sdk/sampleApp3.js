var extension = require('bindings')('alienfx.node');


if (extension.isAvailable) {
    var result = extension.initializeSync();

    if (result === extension.Result.SUCCESS) {
        extension.reset();


        var position = extension.Position.ALL_FRONT;
        var color = extension.Color.GREEN | extension.Brightness.FULL;

        extension.light(position, color);


        var devices = {};
        extension.getNumDevicesSync(devices);

        for (var deviceIndex = 0; deviceIndex < devices.numberOfDevices; deviceIndex++) {
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


                var color = {};
                result = extension.getLightColor(deviceIndex, lightIndex, color);

                if (result !== extension.Result.SUCCESS) {
                    continue;
                }


                console.info('Light: %d\tDescription: %s\tColor: %j', lightIndex, lightDescription.result, color);
            }
        }


        extension.update();


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
