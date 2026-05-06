# 登录页面 - 拖动验证

这是一个包含拖动验证功能的登录页面，使用HTML、CSS和JavaScript实现。

## 功能特性

### 登录功能
- 手机号输入验证
- 密码输入
- 表单验证
- 回车键快速登录

### 拖动验证
- Canvas绘制的拼图验证码
- 滑块拖动交互
- 实时位置更新
- 验证成功/失败反馈
- 自动重试机制

### 用户体验
- 响应式设计
- 渐变背景效果
- 平滑动画过渡
- 移动端支持
- 键盘快捷键支持

## 文件结构

```
AIproject/
├── index.html      # 主页面HTML
├── style.css       # 样式文件
├── script.js       # JavaScript逻辑
└── README.md       # 说明文档
```

## 使用方法

### 方法1：直接打开
1. 双击 `index.html` 文件在浏览器中打开
2. 输入手机号和密码
3. 点击"登录"按钮
4. 在弹出的验证码窗口中拖动滑块完成验证
5. 验证成功后自动提交登录信息

### 方法2：使用本地服务器（推荐）
```bash
# 使用Python启动本地服务器
python -m http.server 8000

# 使用Node.js的http-server
npx http-server
```

然后在浏览器中访问 `http://localhost:8000`

## 技术实现

### HTML结构
- 语义化标签
- 表单元素
- Canvas画布
- 模态框组件

### CSS样式
- Flexbox布局
- 渐变背景
- 响应式设计
- 动画效果
- 媒体查询

### JavaScript功能
- DOM操作
- 事件处理
- Canvas绘图
- 拖拽交互
- 表单验证
- 状态管理

## 手机号验证规则

- 必须是11位数字
- 必须以1开头
- 第二位必须是3-9之间的数字
- 正则表达式：`/^1[3-9]\d{9}$/`

## 拖动验证说明

1. 点击登录按钮后显示验证码弹窗
2. 验证码包含一个拼图块和目标位置
3. 拖动滑块将拼图块移动到目标位置
4. 拖动到最右侧表示验证成功
5. 验证成功后自动提交登录信息

## 浏览器兼容性

- Chrome/Edge (推荐)
- Firefox
- Safari
- 移动浏览器

## 自定义配置

### 修改验证码尺寸
在 `script.js` 中修改：
```javascript
const width = 300;  // 画布宽度
const height = 150; // 画布高度
puzzleWidth = 50;   // 拼图块宽度
puzzleHeight = 50;  // 拼图块高度
```

### 修改颜色主题
在 `style.css` 中修改渐变颜色：
```css
background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
```

### 调整验证难度
在 `script.js` 中修改容差范围：
```javascript
const tolerance = 5; // 容差范围（像素）
```

## 安全说明

这是一个前端演示项目，实际生产环境需要：
- 后端API验证
- HTTPS加密传输
- 密码加密存储
- 防止暴力破解
- CSRF防护
- XSS防护

## 扩展功能建议

- 添加记住密码功能
- 实现第三方登录
- 添加忘记密码功能
- 实现短信验证码
- 添加用户注册功能
- 实现多语言支持

## 技术栈

- HTML5
- CSS3
- JavaScript (ES6+)
- Canvas API

## 许可证

MIT License

## 作者

AI Project Team

---

如有问题或建议，欢迎反馈！