# 项目需求

本项目用于每次仅仅翻译一个语种的博客文章。

使用更高级的LLM 模型，单一语言版本文档的批量翻译 Batch file translation by AI，无需在程序中解析文件特定格式。

使用方法：定义目标语言目录，将源语言文件存入，在根目录中运行程序，本人Github检索程序文件 `Gcloud_vertex-ai-api.py`。


## 基本概念

- 开发程序语言：python，程序逐行配英文注释；

- api：Google云计算，Vertex AI api，使用Gemini Pro模型；

备注：此前调用Google translation api - NMT(神经机器翻译) 模型显得已经过时了，相比最新的Gemini LLM模型，NMT免费模型的翻译质量较低，而且它只能做纯文本的翻译，不能识别带有格式的文档（例如markdown等各种文档格式的语法标记），这导致被翻译后的文件格式混乱，也可能是我们的程序设计和参数配置错误导致的问题。

为了避免这种恶劣情况，需要在程序中定义文件格式语法标记，告诉翻译api哪些文本是可翻译，哪些是保留的标记，这增加了代码工作量，无论如何，我们放弃了使用低端的模型；

- 语言标签： Vertex AI API 的多语种翻译功能使用 BCP 47 语言标签作为输入和输出的语言标识符，主要组成部分是ISO 639 标准中的语言代码，和ISO 3166 标准中的地区代码，例如 zh-TW 中文正体、zh-CN 中文简体，en 英文（不区分en-US美国英语 和 en-GB英国英语）；

- 源语言lan_source：此为文件内容的人类自然语言版本（语言标签），程序通过ai自动识别源语言类别，为了降低调用云计算平台的成本，我们通常会在程序中定义某一种源语言，例如 SOURCE_LANG = "zh-CN" 中文简体；

- 目标语言lan_target：即把文件内容的源语言翻译成我们想要的其他人类自然语言版本，用目录名称定义目标语言，例如目录名 en 英文、de 德文，我们通常在程序中定义某种目标语言，当前设置为 TARGET_LANG = "en"。

## 翻译方法
- 程序在根目录中，启动程序后，程序忽略其他语言目录，仅仅检索程序中定义的目标语言TARGET_LANG 目录及其子目录中的文件；
- 如果在目标语言目录中的文件内容为目标语言，则程序跳过，并在logging中发送一条信息播报；
- 若在目标语言目录中，程序发现源语言，则启动翻译，并把翻译后的内容直接覆盖到原文件中。



# 文件格式
- 文件格式：根据文件名后缀判断文件格式，例如`.md .yaml .xml .json`，分别表示markdown、YAML、XML/HTML和 JSON格式。例如文件名以.md结尾的 filename.md，属于markdown格式；
- 多格式并存：可能在一份文件中有多种混合格式，例如markdown格式的文件中的头信息是yaml格式，或一个目录中有多个不同格式的独立文件，需要ai处理多种格式的文件，为了提高效率和准确性，我们尽可能只处理同一种格式的文件；
- 自动检测文件格式：确保ai模型能理解不同格式的语法标记，通过prompt告知ai模型"根据格式类型选择相应的处理方案，保留源文件格式"，这是最重要的ai模型能力；


# 翻译内容特别注意事项
- 文件格式的语法标记必须保留：例如md文件中带有markdown格式标记和关键字是不可翻译或变更的，翻译后的文件与源文件应保持相同的格式；
- md文件的front matter 头部信息中的" title, date, description, categories, tags"等关键字应保持原英文，不要翻译成目标语言，头信息为YAML 格式，语法标记如下：

```yaml
---
Title: "Proust's Table - Atom"
Date: 2021-10-06
Description: Proust's Table
Category:
- About
Tags:
- Introduction
---
# translate from en to zh-CN, keep keywords in front matter
---
title: "普鲁斯特问卷- Atom"
date: 2021-10-06
description: 普鲁斯特问卷
categories:
  - 关于
tags:
  - 简介
---
# translate from zh-CN to ru
---
title: "Опросник Пруста - Атом"
date: 2021-10-06
description: Опросник Пруста
categories:
  - о
tags:
  - Введение
---
```

- 文件目录名、文件名不要翻译，作为最终网页地址url的一部分，应始终保持其英文语言版本；


## 模型和温度参数设置：

- **模型**：使用 Gemini Pro (gemini-1.5-pro-001)
- **温度设置**：0.3，原因：
  - 足够低以保持准确性并防止产生幻觉
  - 有助于在保持事实的同时保留写作风格
  - 为技术内容提供一致的输出
- **Top-P设置**：0.3，提供更确定性的输出
- **API调用频率限制**：每分钟15次调用，可根据配额调整

## 当前使用的翻译提示词：

```
Translate the following content from {source_lang} to {target_lang}. This is a {file_type} file, and preserving the original formatting is critical.

**ABSOLUTELY CRITICAL INSTRUCTIONS:**

1. **Preserve ALL Formatting:** Maintain *every* aspect of the original formatting. This includes, but is not limited to:
    * Markdown syntax (headings, lists, links, bold, italics, code blocks, etc.)
    * YAML structure (indentation, keys, values, lists) if present in a Markdown header or as a separate `.yaml` file.
    * Spacing (line breaks, indentation).
    * Any other file-type-specific formatting.
    * DO NOT add, remove, or alter any formatting elements.

2. **File/Directory Names:** Do NOT translate file names or directory names. Keep them in English.

3. **YAML Front Matter:**
    * Keep keywords in English: title, date, description, categories, tags
    * Translate values simply and directly
    * For tags/categories: translate to single clear terms without pinyin

4. **Tone and Style:** Maintain the original tone and style of the text while ensuring the translation is culturally appropriate for the target language, And keep the translation style consistent.
```
