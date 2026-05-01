<h1>微信消息轰炸器 - GUI 版</h1>

<p><em>微信消息轰炸器</em> 是一个用于自动批量发送消息的图形界面工具喵。它支持多种消息发送方式，提供友好的用户界面，方便用户实现自动化消息发送功能喵。</p>

<hr/>

<h2>✨ 功能介绍</h2>
<ul>
  <li>🖥️ 图形化界面，操作简单直观</li>
  <li>📝 支持两种发送模式：
    <ul>
      <li>自定义消息内容 + 数量</li>
      <li>仅指定数量，自动发送递增数字</li>
    </ul>
  </li>
  <li>⏱️ 可配置消息间隔时间和字符输入间隔</li>
  <li>📊 实时进度显示和状态反馈</li>
  <li>🛑 支持随时停止发送</li>
  <li>⌨️ 使用 Windows API 模拟键盘输入，支持 Unicode 字符（汉字和符号）</li>
</ul>

<hr/>

<h2>🚀 使用说明</h2>
<ol>
  <li>克隆或下载本项目到本地：
    <pre><code>git clone https://github.com/KleeSky/Message-bombardment.git</code></pre>
  </li>
  <li>使用 Visual Studio 2022 打开项目文件 <code>微信消息轰炸.sln</code></li>
  <li>选择配置（Debug/Release）和平台（x64/Win32）</li>
  <li>编译运行程序</li>
  <li>在 GUI 界面中设置参数：
    <ul>
      <li>选择发送模式</li>
      <li>输入消息内容（如选择自定义模式）</li>
      <li>设置发送数量</li>
      <li>调整消息间隔和字符间隔</li>
    </ul>
  </li>
  <li>点击"开始发送"按钮，然后快速切换到目标窗口（如微信聊天输入框）</li>
  <li>程序将自动按设定发送消息</li>
</ol>

<hr/>

<h2>📁 项目结构</h2>
<pre><code>├── include/                    # 头文件目录
│   ├── InputSimulator.h       # 输入模拟器接口
│   └── MessageSender.h        # 消息发送器接口
├── src/
│   ├── core/                  # 核心模块
│   │   ├── InputSimulator.cpp # 输入模拟实现
│   │   └── MessageSender.cpp  # 消息发送实现
│   └── gui/                   # 图形界面模块
│       └── MainWindow.cpp     # 主窗口实现
└── README.md                  # 项目说明
</code></pre>

<hr/>

<h2>🏗️ 架构设计</h2>
<p>项目采用模块化设计，主要包含以下组件：</p>
<ul>
  <li><strong>InputSimulator</strong>: 负责底层输入模拟，包括 Unicode 字符和特殊键位的发送</li>
  <li><strong>MessageSender</strong>: 核心业务逻辑，管理发送任务、进度和状态回调</li>
  <li><strong>MainWindow</strong>: GUI 界面层，处理用户交互和数据显示</li>
</ul>

<hr/>

<h2>📦 发行版说明</h2>
<ul>
  <li>发行版将包含预编译的 <code>.exe</code> 文件，方便用户直接运行，无需自行编译</li>
  <li>用户只需下载发行版，双击即可使用</li>
</ul>

<hr/>

<h2>💻 依赖环境</h2>
<ul>
  <li>Windows 7 及以上操作系统</li>
  <li>Visual Studio 2022（推荐，用于自行编译）</li>
  <li>需要 .NET Framework（Windows 通常已预装）</li>
  <li>需要通用控件库（comctl32.dll，Windows 系统自带）</li>
</ul>

<hr/>

<h2 style="color:#b03a2e;">⚠️ 重要注意事项</h2>
<ul style="color:#b03a2e; font-weight:bold;">
  <li>请务必合理使用本工具，避免骚扰他人！</li>
  <li>使用时请确保消息发送目标窗口处于激活状态</li>
  <li>本项目仅供学习和研究用途</li>
  <li>任何因滥用本工具造成的后果，作者概不负责</li>
</ul>

<hr/>

<h2>📬 联系方式</h2>
<p>如有问题欢迎提交 <a href="https://github.com/KleeSky/Message-bombardment/issues" target="_blank" rel="noopener noreferrer">Issues</a> 或联系项目维护者喵~</p>
