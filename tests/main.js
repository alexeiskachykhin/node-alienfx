var extension = require('../build/Release/alienfx');

exports.index = {
    hello: function (test) {
        var actualResult = extension.hello();
        var expectedResult = 'world';

        test.equal(actualResult, expectedResult);
        test.done();
    }
};
