var Mocha = require('mocha');
var utilities = require('./utilities');


var mocha = new Mocha({
    reporter: 'spec'
});

utilities.ask.whichTestsToRun([
    'Structural Tests',
    'Behavioral Tests'], function (answers) {

    var testModules = {
        'tests/structural/exports.js': answers[0],
        'tests/behavioral/exports.js': answers[1]
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

