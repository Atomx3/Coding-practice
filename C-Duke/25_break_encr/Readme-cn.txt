
In the last problem, you saw an implementation of a simple
"encryption" program.  In this problem, you will write a program
that breaks that encryption---that is, it will take as input
a text file encrypted with the encryption program you just
saw, and prints out the key used to encrypt it!

Breaking the Caesar Cipher uses a technique called "frequency counting."
This technique relies on the fact that the distribution of letters
in the English alphabet is far from uniform: 'e' is by far the most
common letter (~13%), followed by 't' (9%), and 'a' (8%).  Note
that the average frequency is 100/26 ~= 4%. 

This frequency distribution means that if you know (or suspect)
that a file contains English text encrypted with a Caesar Cipher,
you can simply count the frequency of all letters in it, and guess
that the letter which occurs most often is 'e'.   Once you know
which letter is 'e', you can backsolve for the key and decrypt
the file.  Note that in practice this requires a large enough
text that "the law of large numbers" applies---and while it is
not guaranteed to work, it typically does.


Requirements:
=============

 - Your program will take one command line argument: the name
   of a file to read as input
 - Your program will then perform frequency counting on the letters
   in that text file.  Your program should ignore all non-letter
   characters (those un-modified by your problem 1 program).
 - Your program should use the frequency count information to 
   determine which letter is 'e', and solve for the key.
 - On success, your program should print a single line of output to
   stdout, which should contain one decimal (base 10) integer (followed by a
   newline character).  This number should be the encryption key used
   on the text.  It should be in the range [0,26).  That is, the
   number you print should obey 0 <= answer < 26.
 - On failure, your program should print an appropriate error
   message to stderr, then exit with EXIT_FAILURE.
 - Provide a Makefile which compiles your program into
   a binary called "breaker"
Hints:
 - Divide this problem into sub-problems.  You should probably
   write at least two functions (other than main) to do this.
 - Think about how you want to represent your data.  An array
   might be handy somewhere.
 - You may find a function you wrote in a previous classwork 
   useful for this assignment.  Feel free to use or adapt it.
 - Remember that everything (including characters) are numbers.
   You might look back at the "Read encryption" assignment
   to see an example of doing math on characters.

在上一个问题中，你看到了一个简单的“加密”程序的实现。在这个问题中，你将编写一个程序来破解该加密程序——也就是说，它将以加密程序加密的文本文件作为输入，并打印出用于加密的密钥！

破解凯撒密码使用了一种称为“频率计数”的技术。这种技术依赖于英文字母的分布远非均匀的事实：‘e’ 是最常见的字母（约占 13%），其次是 ‘t’（9%）和 ‘a’（8%）。请注意，平均频率约为 100/26 ~= 4%。

这种频率分布意味着，如果你知道（或怀疑）一个文件包含用凯撒密码加密的英文文本，你可以简单地计算其中所有字母的频率，并猜测出现最频繁的字母是 ‘e’。一旦你知道哪个字母是 ‘e’，你可以反推出密钥并解密文件。请注意，实际上这需要足够大的文本以使“大数定律”适用——虽然不能保证一定有效，但通常是有效的。

要求：
你的程序将接受一个命令行参数：要读取的输入文件的名称
你的程序将对该文本文件中的字母进行频率计数。你的程序应忽略所有非字母字符（那些未被第一个问题的程序修改的字符）。
你的程序应使用频率计数信息来确定哪个字母是 ‘e’，并求解密钥。
成功时，你的程序应向标准输出打印一行输出，该输出应包含一个十进制（base 10）整数（后跟一个换行符）。这个数字应该是文本中使用的加密密钥。它应该在 [0,26) 范围内。也就是说，你打印的数字应满足 0 <= answer < 26。
失败时，你的程序应向标准错误输出打印适当的错误消息，然后以 EXIT_FAILURE 退出。
提供一个 Makefile，将你的程序编译成一个名为“breaker”的二进制文件。
提示：

将这个问题分解成子问题。你可能应该编写至少两个函数（除了 main）来完成这个任务。
考虑你想如何表示你的数据。数组可能在某些地方很有用。
你可能会发现你在以前的课堂作业中编写的一个函数对这个任务有用。随意使用或调整它。
请记住，一切（包括字符）都是数字。你可以回顾一下“读取加密”作业，看看其中的字符数学运算示例。