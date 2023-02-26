# Core UI Architecture

This plugin contains logic for building basic architecture for managing game UI elements in runtime. It is heavily inspired by Unreal's [Lyra Sample Game](https://docs.unrealengine.com/5.0/en-US/lyra-sample-game-in-unreal-engine/) project and thus is based on Unreal's [CommonUI](https://docs.unrealengine.com/5.0/en-US/common-ui-plugin-for-advanced-user-interfaces-in-unreal-engine/) plugin.

---
## License
This plugin with all its content is licensed under the MIT License. [Learn more](https://choosealicense.com/licenses/mit/)

---
## Support
In case of any questions you can contact me at sosnowska.kk@gmail.com.

---
## Installation and usage
Just copy-paste this plugin inside your project's `Plugins` folder.

Keep in mind that this plugin requires Unreal's CommonUI plugin enabled in you project, so you need to have compatible engine version installed. I've tested it only in Unreal 5.1.

---
## About this plugin
Below you can find a brief description of the most important elements of this  UI architecture.

### UGameUIManagerSubsystem
The brain of CoreUI is the GameInstance subsystem `UGameUIManagerSubsystem`, which takes care of adding a special widget `UUI_GameLayout` per each local player that joins current game. For detecting local player addition it uses a simple form of custom classes for `ULocalPlayer` and `APlayerController`.

### UUI_GameLayout
The `UUI_GameLayout` widget consist of a few layers represented as Common Activatable Widget containers. Each container is named with different `FGameplayTag` that also refers to group of UI elements displayed on given layer. Those containers handles for us the Input routing for their children. Order of layers in the root widget hierarchy depicts the priority of them (top-most layers are the most important at given moment - just like top-most widget in the current container gets the Input).

> There are two important things to keep in mind here:
> - firstly, `UCommonActivatableWidgetContainerBase` containers can only accept `UCommonActivatableUserWidget` for their children as they have logic for Input routing;
> - secondly, you need to set `UCommonGameViewportClient` as game viewport class in project general settings in order to have Input routing actually working in your UI.

### UCoreUIUtils
This blueprint library provides a set of utility functions for pushing and popping content to/from layers of  `UUI_GameLayout` assigned to a given player. It also containts methods for suspending and resuming UI input.

### *Messaging* subfolder
This folder contains a set of classes for displaying `UUI_BaseDialog` based dialog widgets in a structurized way.

`UMessagingSubsystem` class provides functions for displaying dialogs with a characteristics passed in form of `UGameDialogDescriptor` object.