1. 批量翻译 Google translation api, batch_translate_text，还必须具有 Cloud Storage 存储分区的访问权限。

目前的程序不属于批量翻译？

说明文档和代码 [batch translate text](https://cloud.google.com/translate/docs/advanced/batch-translation?hl=zh-cn)



2. 为何被限制每次2000字符？
Cloud Translation API
配额： Number of romanization requests per minute
当前值: 6,000

是否因为以下原因？
```py
# API 调用频率限制
CALLS_PER_MINUTE = 15
ONE_MINUTE = 60
INITIAL_RETRY_DELAY = 2
MAX_RETRIES = 5
# 安全的分块大小，考虑到 API 额外开销
SAFE_CHUNK_SIZE = 600
```
请参阅[配额和限制](https://cloud.google.com/translate/quotas?hl=zh-cn)

