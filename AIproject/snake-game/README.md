# 贪吃蛇游戏 (Snake Game)

这是一个用C语言编写的控制台版贪吃蛇游戏，支持Windows平台。

## 功能特性

### 基础版本 (snake.c)
- 基本的贪吃蛇游戏逻辑
- 键盘控制 (WASD)
- 分数统计
- 碰撞检测
- 食物生成

### 增强版本 (snake_enhanced.c)
- 彩色界面显示
- 难度选择 (简单/中等/困难)
- 最高分记录
- 暂停功能
- 游戏说明
- 主菜单界面

## 编译说明

### 使用Makefile编译 (推荐)
```bash
# 编译基础版本
make

# 编译增强版本
make enhanced

# 运行游戏
make run

# 清理编译文件
make clean
```

### 手动编译
```bash
# 基础版本
gcc -Wall -Wextra -std=c99 -o snake.exe snake.c

# 增强版本
gcc -Wall -Wextra -std=c99 -o snake_enhanced.exe snake_enhanced.c
```

## 游戏控制

- **W / ↑** - 向上移动
- **S / ↓** - 向下移动
- **A / ←** - 向左移动
- **D / →** - 向右移动
- **P** - 暂停游戏
- **X** - 退出游戏

## 游戏规则

1. 控制蛇吃掉食物(F)
2. 每吃一个食物得10分
3. 蛇会随着吃食物而变长
4. 撞墙或撞到自己游戏结束
5. 尽量获得高分

## 文件说明

- `snake.c` - 基础版贪吃蛇游戏
- `snake_enhanced.c` - 增强版贪吃蛇游戏
- `Makefile` - 编译脚本
- `README.md` - 说明文档

## 运行要求

- Windows操作系统
- GCC编译器 (MinGW)
- 支持ANSI转义的控制台

## 开发者信息

这个贪吃蛇游戏展示了以下C语言编程技术：
- 结构体和枚举的使用
- 控制台图形界面编程
- 键盘输入处理
- 游戏循环和状态管理
- 内存管理和数组操作
- 随机数生成

享受游戏！