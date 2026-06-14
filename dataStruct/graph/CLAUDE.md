# CLAUDE.md

本文件为 Claude Code（claude.ai/code）在此仓库中工作时提供指引。

## 构建与运行

```bash
# 实验编译与运行
gcc -o exp8-1.exe exp8-1.c adjacencyList/adjacencyList.c maxtrixGraph/maxtrixGraph.c && ./exp8-1.exe
gcc -o exp8-2.exe exp8-2.c adjacencyList/adjacencyList.c && ./exp8-2.exe
gcc -o exp8-3.exe exp8-3.c adjacencyList/adjacencyList.c && ./exp8-3.exe
gcc -o exp8-5.exe exp8-5.c maxtrixGraph/maxtrixGraph.c && ./exp8-5.exe
gcc -o exp8-7.exe exp8-7.c maxtrixGraph/maxtrixGraph.c && ./exp8-7.exe
gcc -o exp8-8.exe exp8-8.c maxtrixGraph/maxtrixGraph.c && ./exp8-8.exe

# 单独编译各模块的独立测试
gcc -o ./adjacencyList/ad.exe ./adjacencyList/main.c ./adjacencyList/adjacencyList.c && ./adjacencyList/ad.exe
gcc -o ./maxtrixGraph/ma.exe ./maxtrixGraph/main.c ./maxtrixGraph/maxtrixGraph.c && ./maxtrixGraph/ma.exe
```

- 编译器：GCC（Windows 下 MinGW-w64），支持 GNU C 扩展
- 语言标准：C99 风格 + GNU 扩展（Floyd 使用了嵌套函数，见下）
- 无 Makefile 或 CMake —— 直接 `gcc` 编译
- 权限已在 `.claude/settings.local.json` 中预配，可直接运行上述命令

## 项目结构

```
graph/
├── adjacencyList/              # 邻接表存储表示（AGraph + 链表）
├── maxtrixGraph/               # 邻接矩阵存储表示（MGraph + 固定数组）
├── information/                # 实验任务书与参考图数据
│   ├── mission.md, graph8.54, graph8.55, graph8.1(a)
├── exp8-1.c                    # 实验1：邻接矩阵+邻接表存储与输出
├── exp8-2.c                    # 实验2：DFS递归/非递归 + BFS遍历
├── exp8-3.c                    # 实验3：连通图所有DFS序列（回溯法）
├── exp8-5.c                    # 实验5：Prim最小生成树
├── exp8-7.c                    # 实验7：Dijkstra最短路径
├── exp8-8.c                    # 实验8：Floyd所有顶点对最短路径
├── CLAUDE.md
└── test01.c
```

## 实验脉络

实验按图论知识点递进：
1. **exp8-1** 存储结构 —— 两种表示法的建立与输出
2. **exp8-2** 图遍历 —— DFS（递归/非递归）+ BFS
3. **exp8-3** 所有 DFS 序列 —— 回溯法枚举，理解搜索树结构
4. **exp8-5** 最小生成树 —— Prim 算法（基于邻接矩阵）
5. **exp8-7** 单源最短路径 —— Dijkstra 算法
6. **exp8-8** 全源最短路径 —— Floyd 算法

## 架构要点

### 两种图表示对比

| 方面 | adjacencyList/ | maxtrixGraph/ |
|---|---|---|
| 存储方式 | 每个顶点一条链表（动态节点） | 固定大小 `MaxNodeNum×MaxNodeNum` 矩阵 |
| 内存分配 | 堆（malloc/free） | 栈 + 固定数组 |
| 初始化 | 两阶段：`createAGraph` → `initAGraph` | 单步：`initMGraph` |
| 插入边 | 头插法插入链表 | 直接写矩阵，有去重检查 |
| 销毁 | `destroyAGraph`（释放所有节点和边） | 无需销毁（无动态分配） |
| 顶点结构 | `ArcNode`（含 `show` 字符串指针） | `MatrixVertex`（含 `show` 字符串指针） |
| 边结构 | `ArcEdge`（no, weight, next*） | `int` 权重（INF=10000 表示无边） |

### 关键约定
- `addAGraph(graph, x, y, w)` / `addMGraph(graph, x, y, w)` —— 起点、终点、权重
- `directed` 标志：1=有向图（只加一条边），0=无向图（加双向）
- 边界检查用 `>=`（顶点编号从 0 开始）
- 控制台编码：`system("chcp 65001>nul")` 启用 UTF-8

### 注意点
- **Floyd 的嵌套函数**：`exp8-8.c` 中 `printPath` 定义在 `Floyd` 函数内部，这是 **GNU C 扩展**（非标准 C99）。若用 `-Wall -pedantic` 编译会触发警告。用 MSVC 编译会失败。
- **数据来源**：`information/` 目录存放实验任务书 `mission.md` 和参考图数据（图 8.54、8.55、8.1(a) 的边列表/邻接表），实验代码中的硬编码数据源于这些文件。
- **`test01.c`**：空文件，无实际内容。
- **权限预配**：`.claude/settings.local.json` 已放行常用的 gcc 编译及运行命令。

## 已完成实验

| 文件 | 实验 | 核心算法 | 测试数据 |
|------|------|---------|---------|
| `exp8-1.c` | 邻接矩阵+邻接表存储 | init/add/print | 图8.54 |
| `exp8-2.c` | 图的遍历 | DFS递归/非递归、BFS | 图8.54 |
| `exp8-3.c` | 所有DFS序列 | 回溯法 | 图8.1(a) |
| `exp8-5.c` | Prim最小生成树 | lowcost数组 | 图8.55 |
| `exp8-7.c` | Dijkstra最短路径 | dist数组+路径记录 | 图8.54 |
| `exp8-8.c` | Floyd最短路径 | 三重循环+path矩阵 | 图8.54 |

## 开发约定

- 代码注释用中文
- 图数据硬编码在源文件中（不从文件读取输入）
- 无单元测试框架；用 `printf` 手动验证输出
