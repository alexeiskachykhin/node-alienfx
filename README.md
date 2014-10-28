#node-alienfx

NodeJS native extension for Dell AlienFX API.

## Debugging
In order to debug extension in Visual Studio, open ```build/Release/binding.sln``` go to ```Project Property Settings -> Debugging``` and put following settings:

*Command*: node.exe

*Command Arguments*: ./node_modules/nodeunit/bin/nodeunit tests

*Working Directory*: $(ProjectDir)..\

This will allow to run unit tests with Visual Studio native debugger attached every time you hit F5.
