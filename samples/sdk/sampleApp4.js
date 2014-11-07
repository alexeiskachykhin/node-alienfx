var extension = require('bindings')('alienfx.node');


function light(colorComponent, callback) {
    if (colorComponent === 0) {
        callback();
        return;
    }


    var color =
        ((0xFF - colorComponent) << 16) +
        colorComponent +
        extension.Brightness.FULL;

    extension.light(extension.Position.ALL, color);
    extension.update();

    console.info('Color: %s', color.toString(16));


    setTimeout(function () {
        light(colorComponent - 1, callback);
    }, 100);
}



if (extension.isAvailable) {
    var result = extension.initializeSync();

    if (result === extension.Result.SUCCESS) {
        var version = {};
        extension.getVersion(version);
        console.info('SDK version: %s', version.result);

        extension.reset();

        light(255, function () {
            require('./utilities').waitForKeyPress(function () {
                extension.releaseSync();
            });
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
