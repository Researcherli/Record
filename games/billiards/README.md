# 🎱 Billiards Game | 桌球游戏 🎱

Welcome to this classic billiards game, built with a modern modular JavaScript architecture. This project showcases a clean separation of concerns, making the code easy to understand, maintain, and extend.

欢迎来到这款经典的桌球游戏，它采用现代模块化 JavaScript 架构构建。该项目展示了清晰的关注点分离，使代码易于理解、维护和扩展。

## 🏗️ Modular Architecture | 模块化架构

The game is divided into several modules, each with a specific responsibility:

游戏被划分为几个模块，每个模块都有特定的职责：

-   **`config.js`**: Centralized configuration for physics, controls, and appearance. | 用于物理、控制和外观的集中配置。
-   **`ball.js`**: Represents the `Ball` class, managing its properties and state. | 代表 `Ball` 类，管理其属性和状态。
-   **`physics.js`**: The physics engine, handling collisions, movement, and pocketing. | 物理引擎，处理碰撞、运动和入袋。
-   **`renderer.js`**: The rendering system, responsible for drawing the game on the canvas. | 渲染系统，负责在画布上绘制游戏。
-   **`input.js`**: Manages all user input, from aiming to shooting. | 管理所有用户输入，从瞄准到击球。
-   **`game-modular.js`**: The main game coordinator, bringing all the modules together. | 主游戏协调器，将所有模块整合在一起。

This modular design promotes code reusability and simplifies the development process.

这种模块化设计提高了代码的可重用性并简化了开发过程。

## 🎯 Key Features | 主要特点

-   **Realistic Physics**: Experience authentic ball collisions, friction, and pocketing behavior. | **逼真的物理效果**: 体验真实的球体碰撞、摩擦和入袋行为。
-   **Stunning Visuals**: High-quality rendering of the table, balls, and cue stick. | **精美的视觉效果**: 高质量渲染的球桌、球和球杆。
-   **Predictive Aiming**: A trajectory prediction system helps you line up the perfect shot. | **预测性瞄准**: 轨迹预测系统可帮助您排好完美的击球线路。
-   **Debug Mode**: A comprehensive debug overlay for inspecting the game's internal state. | **调试模式**: 全面的调试覆盖层，用于检查游戏的内部状态。

## 🎮 How to Play | 如何游戏

1.  **Aim**: Click and drag the cue stick to aim. | **瞄准**: 单击并拖动球杆进行瞄准。
2.  **Power**: The farther you drag, the more powerful the shot. | **力度**: 拖动的距离越远，击球的力量就越大。
3.  **Shoot**: Release the mouse button to strike the cue ball. | **击球**: 松开鼠标按钮，击打母球。

It's that simple! Enjoy the game. | 就这么简单！祝您游戏愉快。

## 🚀 Future Enhancements | 未来增强

This project provides a solid foundation for future development. Some potential ideas include:

该项目为未来的开发提供了坚实的基础。一些可能的想法包括：

-   **Sound Effects**: Adding audio for collisions, pocketing, and other game events. | **音效**: 为碰撞、入袋和其他游戏事件添加音频。
-   **AI Opponent**: Implementing an artificial intelligence to play against. | **人工智能对手**: 实现一个可与之对战的人工智能。
-   **Game Rules**: Incorporating official rules for 8-ball or 9-ball. | **游戏规则**: 引入8球或9球的官方规则。
-   **Multiplayer**: Adding support for online multiplayer matches. | **多人游戏**: 添加对在线多人比赛的支持。

---

This project is a testament to the power of modular design in creating clean, scalable, and maintainable web applications. Feel free to explore the code and build upon it.

该项目证明了模块化设计在创建简洁、可扩展和可维护的Web应用程序方面的强大作用。欢迎您探索代码并在此基础上进行构建。
