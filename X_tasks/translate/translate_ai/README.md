# 项目需求

使用Vertex AI gemini模型，多语言版本博客文档的批量翻译 Batch file translation by Vertex AI gemini，无需在程序中解析文件特定格式。


## 基本概念

- 开发程序语言：python，程序逐行配英文注释；

- api：Google云计算，Vertex AI api，可定义使用的具体ai模型（Gemini pro/ ultra）；

备注：此前调用Google translation api的方法已经过时了，相比最新的Gemini模型，该免费模型的翻译质量较低，而且它只能做纯文本的翻译，不能识别带有格式的文档（例如markdown等各种文档格式的语法标记），这导致被翻译后的文件格式混乱。

为了避免这种恶劣情况，需要在程序中定义文件格式语法标记，告诉翻译api哪些文本是可翻译，哪些是保留的标记，这增加了代码工作量；

- 语言标签： Vertex AI API 的多语种翻译功能使用 BCP 47 语言标签作为输入和输出的语言标识符，主要组成部分是ISO 639 标准中的语言代码，和ISO 3166 标准中的地区代码，例如 zh-TW 台湾正体、中文简体zh-CN，en 英文（不区分en-US美国英语 和 en-GB英国英语）；

- 源语言lan_source：此为文件内容的人类自然语言版本（语言标签），程序通过ai自动识别源语言类别，也可在程序中定义，例如在程序中定义 lan_source = "zh-TW"，为了降低调用云计算平台的成本，我们通常会在程序中定义某一种源语言；

- 目标语言lan_target：把文件内容翻译成我们想要的其他人类自然语言版本，用目录名称定义目标语言，例如目录名 en 英文，de 德文，自定义的目录名并不一定与语言标签完全一致，例如目录zhs表示中文简体，zht 中文正体，我们通常会在程序中定义某一种或多种目标语言；

- 文件目录：目前项目框架采用Jekyll和Hugo方案，其博客内容的目录结构通过语言标签划分，例如目录名（en英文，de德文，zhs中文简体），每种语言目录中可能有多级子目录、子文件，每种语言目录中的文件结构一致，文件名也都是一样的，为了实际需要，部分文件仅仅保留某一种语言版本并存在于某一种语言目录中，而没有同时出现在各种语言目录中。示例如下：

```plaintext 
|-- en/
|   |-- index.md
|   |-- about/
|       |-- index.md
|       |-- team001.md
|   |-- posts/
|       |-- post1.md
|       |-- post5.md
|-- de/
|   |-- index.md
|   |-- about/
|       |-- index.md
|       |-- team.md
|   |-- posts/
|       |-- post1.md
|       |-- post2.md
|-- zhs/
|   |-- index.md
|   |-- about/
|       |-- index.md
|       |-- team.md
|   |-- posts/
|       |-- post1.md
```

## 翻译方法
- 首次批量文件翻译：程序检索当前目录的全部源语言文件，通过ai模型完成翻译，直接把目标语言内容覆盖到文件中；

- 后续新增文件翻译：在各语言目录中持续有新的源语言文件被添加，例如en目录中大部分都是英文版本内容的文件，后续有源语言zh-CN的文件被添加进去，每次运行程序，程序跳过已经翻译成目标语言en的文件，仅仅翻译新增加或更改的源语言zh-CN文件；


- 程序应该检查文件内容的语言版本与所在目录的目标语言是否一致，若不一致，则需要翻译，而不是根据文件名与源语言目录是否一致来判断，因为所有的目录中文件结构和文件名都是一样的。


# 文件格式
- 源文件格式：根据文件名后缀判断文件格式，例如`.md .yaml .xml .json`，分别表示markdown、YAML、XML/HTML和 JSON格式。例如文件名以.md结尾，filename.md，属于markdown格式；
- 多格式并存：可能在一份文件中或一个目录中，需要同时处理多种混合格式的文件，为了提高效率，我们尽可能每次只处理同一种格式文件；
- 自动检测文件格式：确保ai模型能理解不同格式的语法标记，根据格式类型选择相应的处理方案，能保留源文件格式，这是最重要的ai模型能力；


# 翻译内容特别注意事项
- 文件格式的语法标记必须保留：例如md文件中带有markdown格式标记和关键字是不可翻译或变更的，翻译后的文件与源文件应保持相同的格式；而且md文件的头部信息front matter 中的YAML 格式标记如下, title, date, description, categories, tags等关键字应保持原英文不要翻译成目标语言。

```yaml
---
title: "普鲁斯特问卷- Atom"
date: 2021-10-06
description: 普鲁斯特问卷
categories:
  - 关于
tags:
  - 简介
---
```

- 处理命名实体：文中引用的组织名称、名人、名言、普通人名、地名、图书（圣经、经典）、电影名称、中文成语典故、歇後語和寓言短语等特定的专有名词或名称，应该保留一份原文的源语言和汉语拼音，同时一份对应翻译的目标语言，示例：原文、拼音和译文并列，“[original_text Chinese_pinyin]translate_text”。例如，中文翻译为英文：“[狐假虎威 hú jiǎ hǔ wēi] The fox exploits the tiger's might”。

- 文件目录名、文件名不要翻译，作为最终网页地址url的一部分，应始终保持其英文语言版本；



# 问题和需求

1. 请根据以上的项目需求，优化提示词，并翻译成英文版。
2. 尊重原文事实，同时翻译得有文采，防止出现严重的幻觉，应该选择哪种模型和多少度适当的temperature？


## 模型和温度参数建议：

模型：推荐使用Gemini Pro，原因：

- 更擅长理解文档格式并保持结构
- 具有强大的多语言能力
- 在准确性和创造性之间取得良好平衡
- 相比Ultra在此用例中更具成本效益

## 温度设置：0.3-0.4，原因：

- 足够低以保持准确性并防止产生幻觉
- 足够高以允许自然流畅的翻译
- 有助于在保持事实的同时保留写作风格
- 为技术内容提供一致的输出
- 这种组合能够提供可靠的翻译，同时保持可读性和风格，避免陷入可能导致错误的创造性极端。


# prompt 提示词

* 告诉gemini当前任务要处理的文件格式，例如.md markdown，应一丝不苟地保留文件原md格式和其中头部信息中的yaml格式；
* 不要添加任何额外的解释、上下文、示例，只提供与目标目录文件中的源内容相关的翻译文本。
* 尽可能保持文本的原始语气和风格，注意文化差异，在适当的情况下避免直译。处理命名实体，并保持一致的翻译标准和惯例。


## 为Gemini优化的提示词：

```md
您是一位专业翻译。请将以下内容从[源语言]翻译成[目标语言]。

关键要求：
- 这是[格式]文件。严格保留所有原始格式、语法标记和结构；
- 对于markdown文件，保持YAML头部信息中的英文关键字(title, date, description, categories, tags等)；
- 对于命名实体，即文中引用的组织名称、名人、名言、普通人名、地名、图书（圣经、经典）、电影名称、中文成语典故、歇後語和寓言短语等特定的专有名词或名称，应该保留一份原文的源语言、汉语拼音或罗马拼音，同时一份对应翻译的目标语言，示例：原文、拼音和译文并列，使用格式："[原文 汉语拼音] 译文"；
- 仅仅翻译文件中的内容，保持文件/目录名为英文，以确保URL兼容性；
- 直接提供翻译，无需额外解释、上下文或示例；
- 在保持文化适当性的同时维持原有语气和风格；
```

```md
You are a professional translator. Please translate the following content from [SOURCE_LANGUAGE] to [TARGET_LANGUAGE].

Key requirements:

- This is a [FORMAT] file. Strictly preserve all original formatting, syntax markers and structure;

- For markdown files, keep YAML frontmatter keywords in English (title, date, description, categories, tags, etc.);

- For named entities, including organization names, famous people, quotations, personal names, place names, books (Bible, classics), movie titles, Chinese idioms, proverbs and allegorical phrases or any specific proper nouns or names cited in the text, retain both the original source language and Chinese pinyin or Romanization, along with the target language translation. Example: Original text, pinyin and translation should be presented in parallel using the format: "[original_text Chinese_pinyin] translated_text";

- Only translate the content within files, keep file/directory names in English for URL compatibility;

- Provide direct translation without additional explanations or examples;

- Maintain the original tone and style while being culturally appropriate;
```
