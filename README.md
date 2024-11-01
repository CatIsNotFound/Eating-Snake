# EATING SNAKE - 贪吃蛇

----

```
-------------------------------------------------------------------------
  EEEEE   A   TTTTT III N   N  GGG         SSSS N   N   A   K   K EEEEE 
  E      A A    T    I  NN  N G           S     NN  N  A A  K  K  E     
  EEEE  AAAAA   T    I  N N N G GG         SSS  N N N AAAAA KKK   EEEE  
  E     A   A   T    I  N  NN G   G           S N  NN A   A K  K  E     
  EEEEE A   A   T   III N   N  GGG        SSSS  N   N A   A K   K EEEEE
-------------------------------------------------------------------------
```

## 简介

这是我的第一个基于 C++ 编写的自制命令行小游戏。

欢迎各位新手小白前来游玩~ o(\*￣▽￣\*)o~

代码是开源的，欢迎各位小白前来借鉴~

## 下载安装

前往 [Github Release](https://github.com/CatIsNotFound/Eating-Snake/releases/latest) 页面即可直接下载到游戏本体。

## 下载源代码并编译

1. 首先，你需要先安装 Git；

   > 关于 Git 的下载，可以前往这个网站：https://git-scm.com/downloads

2. 执行克隆命令：

    ```shell
    git clone https://github.com/CatIsNotFound/Eating-Snake.git
    ```

3. 编译项目

    ```shell
    cd Eating-Snake
    make
    ```

    如果没有 cmake 编译器, 也可以执行 g++ 进行编译：
    
    ```shell
    cd Eating-Snake
    g++ ./Funcs/* main.cpp -o Game
    ./Game
    ```
   
## 怎么玩？

### 简介 

- 你的目标：**控制蛇吃满 99 个零食**
  - 你需要控制蛇吃掉零食，并在蛇吃掉 99 个零食后，游戏结束。
- 期间蛇可以获得：
  - `H` 生命值：小概率产生，每吃掉一个，可增加一点生命值；
  - `*` 零食：吃掉后，可增加蛇的长度；

### 操作控制

- <kbd>W</kbd> <kbd>A</kbd> <kbd>S</kbd> <kbd>D</kbd>：控制蛇的方向
- <kbd>Space</kbd>：暂停 / 继续游戏
- <kbd>R</kbd>：重新开始游戏（仅在蛇的命已全部用完之后可用）
- <kbd>Esc</kbd>：退出游戏

## 游戏界面截图

### 游戏首页

```

 -----------------------------------------------------------------------
  EEEEE   A   TTTTT III N   N  GGG         SSSS N   N   A   K   K EEEEE
  E      A A    T    I  NN  N G           S     NN  N  A A  K  K  E
  EEEE  AAAAA   T    I  N N N G GG         SSS  N N N AAAAA KKK   EEEE
  E     A   A   T    I  N  NN G   G           S N  NN A   A K  K  E
  EEEEE A   A   T   III N   N  GGG        SSSS  N   N A   A K   K EEEEE
 -----------------------------------------------------------------------
                           Eating Snake Ver 1.0
                       >> Press SPACE key to start. <<

                      Copyright (C) 2024 CatIsNotFound

 ------------------------------- How To play ---------------------------
                              Press ESC to quit.
                       Press SPACE to pause or resume.
                Press 'w' 'a' 's' 'd' to control snake direction.
 -----------------------------------------------------------------------

 ---------------------------- YOUR DESTINATION -------------------------
                      Please help the snake eat 99 snacks.
 -----------------------------------------------------------------------
```

### 游戏界面

其中的 `H` 表示蛇的生命值， `E` 表示蛇的长度；

```
  H: 11 E: 69/99
 +------------------------------------------------------------+
 |                                                            |
 |                                                            |
 |                                                            |
 |                                                            |
 |                                                            |
 |      oooooooo0                                             |
 |      o                                                     |
 |      oooooooo                                              |
 |             o                                              |
 |             o                                              |
 |             o                                              |
 |             o                                              |
 |             ooooo                                          |
 |                 o                                          |
 |                 o                       ooo                |
 |                 ooooo                   o                  |
 |                     o               ooooo                  |
 |                     o               o                      |
 |                     ooooo           o                      |
 |                         o    oooooooo                      |
 |                         o    o                             |
 |                         oooooo                             |
 |                                                            |
 |                                                            |
 |                                                            |
 |          *                                                 |
 +------------------------------------------------------------+

```

## 关于项目开源

本开源项目使用 GPL-3.0 license 保护，详细见 [LICENSE](./LICENSE) 文件。
