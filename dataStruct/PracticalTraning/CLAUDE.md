# CLAUDE.md

本文件为 Claude Code（claude.ai/code）在此仓库中工作时提供指引。

## 编译与运行

```bash
# 编译学生管理系统
gcc -o program.exe main.c student.c

# 运行
./program.exe
```

- 编译器：MinGW-w64 GCC（`D:\MinGW\mingw64\bin\g++.exe`）
- 无 Makefile —— 直接 `gcc` 编译
- 可执行文件 `.exe` 已纳入版本管理；修改源码后需重新编译

## 项目概述

**学生管理系统** —— 基于 C 语言的控制台应用，提供学生信息的增删改查、统计、文件持久化功能。

### 文件结构

| 文件 | 作用 |
|------|------|
| `main.c` | 程序入口：菜单循环（9个选项，switch 实现） |
| `student.h` | 头文件：`student` 结构体、`school` 结构体、函数声明 |
| `student.c` | 所有功能模块的实现 |
| `student.txt` | 数据文件 —— 持久化存储的学生记录（空格分隔） |

### 数据架构

- **存储方式**：固定大小的结构体数组（`student std[1000+5]`），堆上分配
- **第 0 号位置不使用** —— 学生信息存放在 `std[1]..std[cnt]`
- **未使用链表** —— 选择数组结构体是为了实现简单
- **持久化**：纯文本文件 `student.txt`，每行一条记录，字段以空格分隔

### 结构体定义

```c
typedef struct {
    char name[25];
    int age;
    char gender[5];
    int score;
    int classNo;
    int StdNo;   // 学号（唯一）
} student;

typedef struct {
    student* std;  // 动态数组
    int cnt;       // 当前学生人数
} school;
```

### 关键约定

- **学号（StdNo）必须唯一** —— 创建时通过 `StuNoValid()` 检查
- **性别**必须为 `"男"` 或 `"女"` —— 否则拒绝输入
- **控制台编码**：`system("chcp 65001 >nul")` 启用 UTF-8 显示
- `student.txt` 字段顺序：`classNo StdNo age score name gender`
- 无单元测试框架 —— 使用 `printf` 手动验证

### 功能模块

| 函数 | 说明 |
|------|------|
| `initSys()` | 初始化系统，分配 school 和学生数组内存，返回指针 |
| `menuMain()` | 打印菜单界面 |
| `addsStd()` | 创建学生（学号唯一性检查 + 性别合法性），追加到数组末尾 |
| `PrintStd()` | 打印所有学生信息 |
| `saveStd()` | 将所有学生信息写入 `student.txt` |
| `loadStd()` | 清空当前数据，从 `student.txt` 重新读取 |
| `cntStu()` | 返回当前学生人数 |
| `serachStd()` | 按学号查找并显示学生信息 |
| `modifyStd()` | 按学号查找，然后重新输入所有字段 |
| `delStu()` | 按学号查找，通过数组前移覆盖实现删除 |
| `createStd()` (static) | 从标准输入录入学生所有字段，返回新 `student` 指针 |
| `StuNoValid()` (static) | 检查学号是否已存在 |
| `ToolSer()` (static) | 内部按学号查找辅助函数（返回数组下标） |

### 编译注意事项

- `student.h` 使用 `#pragma once` 作为头文件保护
- 静态辅助函数（`createStd`、`StuNoValid`、`ToolSer`）仅限文件内可见
- `#define maxx 1000+5` —— 注意宏展开问题：`maxx-1` 展开为 `1000+5-1` 而不是 `1004`
