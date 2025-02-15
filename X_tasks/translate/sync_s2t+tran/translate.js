// 纯粹的翻译脚本，不包含Git操作
const fs = require('fs'); // 导入文件系统模块
const path = require('path'); // 导入路径模块
const { Translate } = require('@google-cloud/translate').v2; // 导入Google Translate API客户端
const translate = new Translate(); // 创建Translate客户端实例

// 从命令行参数中获取源目录和目标语言
const [,, srcDir, targetLang] = process.argv;

// 使用Google Translate API翻译文本的函数
async function translateText(text, target) {
  let [translation] = await translate.translate(text, target);
  return translation;
}

// 翻译文件内容的函数
async function translateFileContent(srcFile, destFile, targetLang) {
  const text = fs.readFileSync(srcFile, 'utf8');
  const translatedText = await translateText(text, targetLang);
  fs.writeFileSync(destFile, translatedText, 'utf8');
}

// 处理SUMMARY.md文件，保持文件名不变，翻译方括号内的内容
async function translateSummary(srcFile, destFile, targetLang) {
  // 读取源文件内容
  const text = fs.readFileSync(srcFile, 'utf8');
  
  // 按行拆分文件内容
  const lines = text.split('\n');
  
  // 翻译每一行的方括号内容
  const translatedLines = await Promise.all(lines.map(async (line) => {
    const match = line.match(/

\[(.*?)\]

\((.*?)\)/); // 匹配方括号和圆括号中的内容
    if (match) {
      const translatedTitle = await translateText(match[1], targetLang); // 翻译方括号内的标题
      return `[${translatedTitle}](${match[2]})`; // 保持文件名不变
    }
    return line; // 如果没有匹配到格式，返回原行内容
  }));
  
  // 将翻译后的内容写入目标文件
  fs.writeFileSync(destFile, translatedLines.join('\n'), 'utf8');
}


// 遍历目录并翻译文件
async function traverseDir(srcDir, destDir, targetLang) {
  if (!fs.existsSync(destDir)) {
    fs.mkdirSync(destDir, { recursive: true });
  }

  const files = fs.readdirSync(srcDir);
  for (const file of files) {
    const srcPath = path.join(srcDir, file);
    const destPath = path.join(destDir, file);

    if (fs.lstatSync(srcPath).isDirectory()) {
      await traverseDir(srcPath, destPath, targetLang);
    } else if (file === 'SUMMARY.md') {
      await translateSummary(srcPath, destPath, targetLang);
    } else if (file.endsWith('.md')) {
      await translateFileContent(srcPath, destPath, targetLang);
    } else {
      fs.copyFileSync(srcPath, destPath);
    }
  }
}

// 执行翻译过程
const targetLangs = ['en', 'de', 'ru']; // 目标语言列表
for (const lang of targetLangs) {
  const destDir = path.join(__dirname, lang); // 定义目标目录
  traverseDir(srcDir, destDir, lang); // 遍历源目录并翻译文件
}
