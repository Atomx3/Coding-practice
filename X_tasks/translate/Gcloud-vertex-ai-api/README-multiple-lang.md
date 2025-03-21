# 项目需求

本项目用于同时翻译多语种的博客文章，参考项目说明文`Gcloud_vertex-ai-api.md`。

使用AI 模型，多语言版本文档的批量翻译 Batch file translation by AI，无需在程序中解析文件特定格式。


## 基本概念

- 开发程序语言：python，程序逐行配英文注释；

- api：Google云计算，Vertex AI api，可定义使用的具体ai模型（Gemini pro/ ultra）；

备注：此前调用Google translation api的方法已经过时了，相比最新的Gemini模型，该免费模型的翻译质量较低，而且它只能做纯文本的翻译，不能识别带有格式的文档（例如markdown等各种文档格式的语法标记），这导致被翻译后的文件格式混乱。为了避免这种恶劣情况，需要在程序中定义文件格式语法标记，告诉翻译api哪些文本是可翻译，哪些是保留的标记，这增加了代码工作量，因此放弃使用 from google.cloud import translate_v2 as translate 库；

- 语言标签： Vertex AI API 的多语种翻译功能使用 BCP 47 语言标签作为输入和输出的语言标识符，主要组成部分是ISO 639 标准中的语言代码，和ISO 3166 标准中的地区代码，例如 zh-TW 中文正体、zh-CN 中文简体，en 英文（不区分en-US美国英语 和 en-GB英国英语）；

- 源语言lan_source：此为文件内容的人类自然语言版本（语言标签），程序通过ai自动识别源语言类别，为了降低调用云计算平台的成本，我们通常会在程序中定义某一种源语言，例如 lan_source = "zh-CN" 中文简体；

- 目标语言lan_target：把文件内容翻译成我们想要的其他人类自然语言版本，用目录名称定义目标语言，例如目录名 en 英文、de 德文，我们通常会在程序中定义某一种或多种目标语言。可能自定义的目录名并不一定与语言标签完全一致，例如目录zhs表示中文简体，zht 中文正体；

- 文件目录：目前项目框架采用Jekyll和Hugo方案，其博客内容的目录结构通过语言标签划分，例如目录名（en英文，de德文，zh-CN中文简体），每种语言目录中可能包含多级子目录、子文件，每种语言目录中的文件结构一致，文件名也都是一样的，为了实际需要，部分文件仅仅保留某一种语言版本并存在于某一种语言目录中，而没有同时出现在各种语言目录中。示例如下：

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
|-- zh-CN/
|   |-- index.md
|   |-- about/
|       |-- index.md
|       |-- team.md
|   |-- posts/
|       |-- post1.md
```

## 翻译方法
- 首次批量文件翻译：程序检索当前目录的全部源语言文件，通过ai模型完成翻译，直接把目标语言内容覆盖到文件中；

- 后续新增文件翻译：在各目标语言目录中持续有新的源语言文件被添加，程序应该检查文件内容的语言版本与所在目录的(目录名称)目标语言是否一致，若不一致，则需要翻译。
例如en目录中大部分都是英文版本内容的文件，后续有源语言zh-CN的文件被添加进去，每次运行程序，程序跳过已经翻译成目标语言en的文件，仅仅翻译新增加或更改的源语言zh-CN文件；

- 所有的目标语言目录和等待翻译的文件已经创建，不需程序再创建新的目标语言目录及其文件，例如在en英文目录中，有源语言为zh-CN中文简体的文件，程序直接把翻译后的内容直接覆盖到原文件中。

- 我们实际项目中有多个语言目录，可能超过5种，根据需要，每次需要翻译的目标语言数量要少于实际项目的目录中已经存在的各种语言目录数量，我们可能每次的程序运作时，仅仅设置某1-2种目标语言target_lang，也就是让程序仅仅翻译其中的某1-2种目标语言（例如en，ru）。请确认，程序中TARGET_DIRS 列出的多个目标语言目录决定了最终被翻译的target_lang种类吗？
  


# 文件格式
- 文件格式：根据文件名后缀判断文件格式，例如`.md .yaml .xml .json`，分别表示markdown、YAML、XML/HTML和 JSON格式。例如文件名以.md结尾的 filename.md，属于markdown格式；
- 多格式并存：可能在一份文件中有多种混合格式，例如markdown格式的文件中的头信息是yaml格式，或一个目录中有多个不同格式的独立文件，需要ai处理多种格式的文件，为了提高效率和准确性，我们尽可能每次只处理同一种格式的文件；
- 自动检测文件格式：确保ai模型能理解不同格式的语法标记，通过promt告知ai模型“根据格式类型选择相应的处理方案，保留源文件格式”，这是最重要的ai模型能力；


# 翻译内容特别注意事项
- 文件格式的语法标记必须保留：例如md文件中带有markdown格式标记和关键字是不可翻译或变更的，翻译后的文件与源文件应保持相同的格式；
- md文件的front matter 头部信息中的“ title, date, description, categories, tags”等关键字应保持原英文，不要翻译成目标语言，头信息为YAML 格式，语法标记如下：

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

- 文件目录名、文件名不要翻译，作为最终网页地址url的一部分，应始终保持其英文语言版本；



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



## 为Gemini优化的提示词：

```md
您是一位专业翻译。请将以下内容从[源语言]翻译成[目标语言]。

关键要求：
- 这是[格式]文件。严格保留所有原始格式、语法标记和结构；
- 对于[markdown格式]文件，保持[YAML格式]的头部信息中的英文关键字(title, date, description, categories, tags等)；
- 对于命名实体，即文中引用的组织名称、名人、名言、普通人名、地名、图书（圣经、经典）、电影名称、中文成语典故、歇後語和寓言短语等特定的专有名词或名称，应该保留一份原文的源语言、汉语拼音或罗马拼音，同时一份对应翻译的目标语言，使用格式："[原文 汉语拼音] 译文"；
- 仅仅翻译文件中的内容，保持文件/目录名为英文，以确保URL兼容性；
- 直接提供翻译，无需额外解释、上下文或示例；
- 在保持文化适当性的同时维持原有语气和风格；
```

```md
You are a professional translator. Please translate the following content from [SOURCE_LANGUAGE] to [TARGET_LANGUAGE].

Key requirements:

- This is a [FORMAT] file. Meticulously preserve all original formatting, syntax markers, and structure.
- For Markdown files, retain English keywords in the YAML frontmatter (e.g., title, date, description, categories, tags).
- For named entities (e.g., organization names, famous individuals, quotations, personal names, place names, books [including the Bible and classics], movie titles, Chinese idioms, proverbs, allegorical phrases, or any proper nouns), retain the original source language text and its Pinyin or Romanization alongside the target language translation using the format: "[Original Text Pinyin/Romanization] Translated Text".
- Translate only the file content. Keep file and directory names in English for URL compatibility.
- Provide a direct translation without additional explanations, context, or examples.
- Maintain the original tone and style while ensuring cultural appropriateness.


```


