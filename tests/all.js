var Mocha = require('mocha');
var utilities = require('./utilities');


var mocha = new Mocha({
    reporter: 'spec'
});

utilities.ask.whichTestsToRun([
    'Structural Tests',
    'Tests for Compatible Hardware',
    'Tests for Incompatible Hardware'], function (answers) {

    var testModules = {
        'tests/structural/exports.js': answers[0],
        'tests/compatible/exports.js': answers[1],
        'tests/incompatible/exports.js': answers[2]
    };


    Object.keys(testModules).forEach(function (testModule) {
        if (testModules[testModule]) {
            mocha.addFile(testModule);
        }
    });


    mocha.run(function (failures) {
        process.on('exit', function () {
            process.exit(failures);
        });
    });
});

