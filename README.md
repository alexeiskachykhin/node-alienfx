![node-alienfx](https://cloud.githubusercontent.com/assets/2787454/4907947/d318e4e8-6465-11e4-8ab1-8e3ccb914d69.png)

node-alienfx
============

[Node.js][Node] native extension for Dell [AlienFX][AlienFX] API.


This module offers bindings for AlienFX API provided by AlienFX.dll. The main desing goal of this project is to keep JavaScript bindings close to their native counterparts as much as possible. It allows line-by-line porting of existing AlienFX enabled apps to [Node.js][Node]. Provided APIs feels bit alien to JavaScript so high-level wrapper around [node-alienfx][node-alienfx] is comming soon. Stay tuned.

Installation
------------
NPM package is comming soon...

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
[node-alienfx]: https://github.com/alexeiskachykhin/node-alienfx
