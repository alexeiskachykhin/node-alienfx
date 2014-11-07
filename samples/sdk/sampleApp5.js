var extension = require('bindings')('alienfx.node');


function light() {
    var color = extension.Color.BLUE + extension.Brightness.FULL;

    extension.light(extension.Position.ALL, color);
    console.log('Setting all lights, color: %s', color.toString(16));

    extension.update();
}

function pulse() {
    var color = extension.Color.RED + extension.Brightness.FULL;

    extension.actionColor(extension.Position.ALL, extension.Action.PULSE, color);
    console.log('Pulsing all lights, color: %s', color.toString(16));

    extension.update();
}

function morph() {
    var primaryColor = extension.Color.RED + extension.Brightness.FULL;
    var secondaryColor = extension.Color.BLUE + extension.Brightness.FULL;

    extension.actionColorEx(extension.Position.ALL, extension.Action.MORPH, primaryColor, secondaryColor);
    console.log('Morphing all lights, from color: %s to color: %s', primaryColor.toString(16), secondaryColor.toString(16));

    extension.update();
}



if (extension.isAvailable) {
    var result = extension.initializeSync();

    if (result === extension.Result.SUCCESS) {
        extension.setTiming(100);
        extension.reset();

        setTimeout(light, 0);
        setTimeout(pulse, 5000);
        setTimeout(morph, 10000);

        setTimeout(function () {
            require('./utilities').waitForKeyPress(function () {
                extension.release();
            });
        }, 15000);
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
