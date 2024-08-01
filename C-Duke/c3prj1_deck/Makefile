# 设置编译器标志：开启调试信息，打开所有警告，将所有警告视为错误，遵循严格的语法标准，并使用GNU99标准
CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99

# 给定的对象文件，这些可能是在课程中提供的预编译对象文件
GIVEN_OBJS=deck-c4.o  eval-c4.o  future.o  input.o  main.o

# 我的对象文件，这些是您自己编写的源代码文件编译后的对象文件
MY_OBJS=cards.o deck.o eval.o

# 定义test-deck目标，依赖于deck.o, test-deck.o, deck-c4.o, 和 cards.o
# 使用gcc命令和上面定义的CFLAGS来编译这些对象文件，生成名为test-deck的可执行文件
test-deck: deck.o test-deck.o deck-c4.o cards.o
	gcc -o test-deck -ggdb3 deck.o test-deck.o deck-c4.o cards.o

# 定义clean规则，用于清理编译过程中生成的文件
# 使用rm命令删除test, poker, cards.o, my-test-main.o以及所有以波浪号结尾的文件
clean:
	rm test poker cards.o my-test-main.o *~

