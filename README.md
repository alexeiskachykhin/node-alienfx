![node-alienfx](https://cloud.githubusercontent.com/assets/2787454/4907835/c203d0e2-6464-11e4-8895-a855b1fc9897.jpg "node-alienfx")

#node-alienfx

NodeJS native extension for Dell AlienFX API.

## Debugging
In order to debug extension in Visual Studio, open ```build/Release/binding.sln``` go to ```Project Property Settings -> Debugging``` and put following settings:

| Property          | Value                                                |
| ----------------- |------------------------------------------------------|
| Command           | node.exe                                             |
| Command Arguments | ./tests/all.js                                       |
| Working Directory | $(ProjectDir)..\                                     |


This will allow to run unit tests with Visual Studio native debugger attached every time you hit F5.
