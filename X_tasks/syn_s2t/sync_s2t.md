这是一个文件同步器，源文件中发生的任何变更，也将同步到目标文件中。

# 项目需求
- 源文件同步：将源文件目录(source_dir: zh)文件同步到多个目标目录中(target_dirs: ru, en)
- 保持一致性：确保所有目录中的文件结构、同名文件的格式和块（段落）完全相同；
- 高效更新：源文件中内容块变更，仅同步变更的块到相应目标文件中，避免全文件复制，节约计算资源；



# 工作过程

1. 主程序初始化
   - 定义项目根目录
   - 配置源文件和目标文件目录
   - 初始化meta目录
   - 设置git仓库

2. 文件同步阶段
   - 扫描源目录文件
   - 同步到多个目标目录
   - 保持目录结构一致

3. 元数据处理阶段
   - 解析源文件内容
   - 生成块级元数据
   - 更新meta文件

4. 变更监控阶段
   - git检测文件变化
   - 定位变更内容块
   - 执行增量更新
   - 同步元数据状态



# 文件结构

test_copy/
├── zh/
│   ├── source_file1.md
│   ├── source_file2.md
│   └── sub_dir1/
│        ├── source_file1.md
│        ├── source_file2.md
│        └── sub_dir2/
│            ├── source_file1.md
│            ├── source_file2.md
│            └── ...     
├── en/
│   ├── source_file1.md
│   ├── source_file2.md
│   └── sub_dir1/
│        ├── source_file1.md
│        ├── source_file2.md
│        └── sub_dir2/
│            ├── source_file1.md
│            ├── source_file2.md
│            └── ...     
├── ru/
│   ├── source_file1.md
│   ├── source_file2.md
│   └── sub_dir1/
│        ├── source_file1.md
│        ├── source_file2.md
│        └── sub_dir2/
│            ├── source_file1.md
│            ├── source_file2.md
│            └── ...     
│
├── meta/ # 内容块（段落）元数据文件
│   ├── source_file1.md.meta # 实际为.json 格式文件
│   ├── source_file2.md.meta
├── program/ # 程序文件
│   ├── tra_local.py
│   ├── meta_data_manager.py
│   ├── git_change_tracker.py
│   ├── target_file_updater.py
│   ├── test_solutio.md
│   ├── meta_def.md

# 核心组件
1. **变更跟踪器** (git_change_tracker.py)
    - 跟踪文件变化
    - 提供变更信息接口
    - 维护元数据同步，快速定位变更的块
    - 按需更新目标文件

      - git_change_tracker.py acts as a specialized local tracker just for monitoring source_dir changes.
      - Main git repository in the root handles the complete codebase versioning and remote collaboration.

2. **元数据管理器** (meta_data_manager.py)
    - 基于meta_def.md规则，解析文件格式语法结构
    - 为每个内容块生成唯一ID，记录块的内容和属性
    - 所有目录共享统一元数据，提供快速检索接口

3. **文件同步器** (target_file_updater.py)
    - 执行文件复制操作
    - 维护目录结构一致性
    - 确保格式标记完整性

4. **主控程序** (sync_s2t.py)
    - 协调各组件工作
    - 管理工作流程
    - 处理异常情况

5. **日志管理器** (log_manager.py)
    - 统一管理所有日志输出功能
    - 简化日志输出路径，只显示相对路径
    - 跟踪文件变更记录，避免重复日志信息
    - 按时间顺序整理输出变更记录
    - 提供操作最终状态报告并报错

# 主要特性
1. 核心功能
   - 保持文档格式完整性
   - 高效的变更检测和更新
   - 统一的元数据管理

2. 优化策略
   - 增量更新：仅处理变更内容
   - 共享元数据：避免重复解析
   - 块级操作：提高更新效率
   - 统一块ID：便于内容对照

3. 扩展能力
   - 支持添加新的目标语言目录
   - 可扩展的元数据结构
   - 模块化的组件设计


## "meta元数据"方案

为了方便跟踪文件内容的任何更改，程序初始化时，创建meta目录，用于存放每个文件的元数据。

元数据定义：给每份文件具体内容划分块（block）或段落（paragraph）的一一对应的标号记录。

文件块的标准是什么？哪几行或哪些内容可归为一个块？针对不同格式的文件提出定义方案，另参考文件 "meta_def.md"。



## 节能增效

meta 数据记录了文件的块级内容的id号，当源文件中的某内容块（段落）被修改，git配合meta 精确地跟踪被修改的块，根据块id号快速索引并精准定位，然后target file updater 仅仅操作从源文件到目标文件的被修改内容块的同步更新，而不需要重新复制整个源文件到目标文件中，因此节省了计算资源，并提高工作效率。
