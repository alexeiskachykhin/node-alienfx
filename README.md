![node-alienfx](https://cloud.githubusercontent.com/assets/2787454/4907947/d318e4e8-6465-11e4-8ab1-8e3ccb914d69.png)

node-alienfx
============

[Node.js][Node] native extension for Dell [AlienFX][AlienFX] API.


This module offers bindings for AlienFX API provided by AlienFX.dll. The main desing goal of this project is to keep JavaScript bindings close to their native counterparts as much as possible. It allows line-by-line porting of existing AlienFX enabled apps to [Node.js][Node]. Provided APIs feels bit alien to JavaScript so high-level wrapper around `node-alienfx` is comming soon. Stay tuned.

Installation
------------
First of all make sure that AlienFX.dll is installed on your system, the easiest way to do so - install Alienware Command Center.

NPM package is comming soon...

Compatibility
-------------
**Operating Systems**: Windows

**Node**: 0.10.26


Currently we are bound to operating systems that AlienFX.dll can run on. Strictly speaking it is possible to bypass [AlienFX][AlienFX] API and talk directly to the underlaying hardware, which requires us to send byte arrays to USB HID device. This will allow to support wider range of operating systems, but it is significantly harder to implement and what's more important, all of the device differences have to be handled. Awesome libraries implemented this way exist [pyalienfx][pyalienfx]. Please let me know if you really interested to see this module working on Linux. 

Example
-------
Example folder contains line-by-line ported examples from [AlienFX][AlienFX] SDK.

```javascript
var alienfx = require('alienfx');

alienfx.initialize();
alienfx.reset();

var position = alienfx.Position.ALL;
var color = alienfx.Color.GREEN | alienfx.Brightness.FULL;

alienfx.light(position, color);
alienfx.update();

alienfx.release();
```

Build & Test
-----
Install [node-gyp]:
```javascript
npm install -g node-gyp
```

Build:
```javascript
node-gyp configure
node-gyp build
```

Test:
```javascript
npm test
```

Debugging
---------
In order to debug extension in Visual Studio, open ```build/Release/binding.sln``` go to ```Project Property Settings -> Debugging``` and put following settings:

| Property          | Value                                                |
| ----------------- |------------------------------------------------------|
| Command           | node.exe                                             |
| Command Arguments | ./tests/all.js                                       |
| Working Directory | $(ProjectDir)..\                                     |


This will allow to run unit tests with Visual Studio native debugger attached every time you hit F5.


[Node]: http://nodejs.org
[AlienFX]: http://www.alienware.com/landings/alienfx/
[pyalienfx]: https://code.google.com/p/pyalienfx/
[node-gyp]: https://github.com/TooTallNate/node-gyp
