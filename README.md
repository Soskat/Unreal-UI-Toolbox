# UI-Toolbox

Welcome at the UI Toolbox repository, where I store some useful tricks and solutions to problems related to (mostly) UI implementation in Unreal Engine. Those tricks and solutions are represented by groups of classes and content assets that form UE plugins.

Aside the plugins themselves, you can access an example project *UIToolboxPreview*, where you can learn about plugins usage in practise.

## License
This repository with all its content is licensed under the MIT License. [Learn more](https://choosealicense.com/licenses/mit/)

## Support
In case of any questions you can contact me at sosnowska.kk@gmail.com.

## Installation and usage
If you want to use one of provided plugins, it requires the standard way of using Unreal Engine plugins (just copy-paste its folder inside your project plugins folder). Additional requirements (if any) for each plugin are described on their dedicated READMEs.

In case you want to check out the UIToolboxPreview, you need 5.1-compatible version of Unreal Engine in order to run accompanied .uproject without any problems.

# Plugins description

## DebuggingUtils
This plugin contains only some sets of useful macros, that help to write shorter code. You can find examples in example project.

Learn more about this plugin [here](./UIToolboxPreview/Plugins/DebuggingUtils/README.md).

---
## CoreUIArchitecture

This plugin contains logic for building basic architecture for managing game UI elements in runtime. It is heavily inspired by Unreal's [Lyra Sample Game](https://docs.unrealengine.com/5.0/en-US/lyra-sample-game-in-unreal-engine/) project and thus is based on Unreal's CommonUI plugin.

Learn more about this plugin [here](./UIToolboxPreview/Plugins/CoreUIArchitecture/README.md).

---
## InputDevicesBrushes

This content-only plugin contains a set of UCommonInputBaseControllerData databases that can be used to retrive data of input devices buttons UI images. It is completely based on built-in Unreal's CommonUI plugin - no need to install third-party items.

Learn more about this plugin [here](https://github.com/Soskat/UE5-InputDevicesBrushes).