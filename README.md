# Makefile简介

makefile可以自动化编译我们的程序。在一个项目有很多源代码的情况下，只需要一个make命令，整个项目的源代码都可以按照定义的规则自动编译，特别方便。只要makefile写得好，make命令会自动智能地根据当前文件修改情况来确定哪些文件需要重编译，从而自动编译所需要的文件和链接目标程序。

# Makefile的规则

makefile的主要形式：

```shell
target : prerequisites
    command
```

target可以是一个目标文件，也可以是一个执行文件。

prerequisites是生成该target所依赖的文件或是target

command是该target要执行的命令（shell命令）

这是一个 文件的依赖关系，target这一个或多个目标文件依赖于prerequisites中的文件，它的生成规则则定义在command中。

这就是makefile最核心的规则。

# 实例说明

本次实例共有8个c文件（one.c、two.c、three.c、four.c、five.c、six.c、seven.c、eight.c），3个头文件(first.h、second.h、third.h)。实例源代码可在[GithubSourceCode](https://github.com/nianer/Makefile-first-exploration)

## 第一个实例

使用到文件one.c、two.c、three.c、first.h、second.h、third.h

```makefile
main: one.o two.o three.o
    gcc -o main one.o two.o three.o

one.o: one.c first.h
    gcc -c one.c

two.o: two.c second.h
    gcc -c two.c

three.o: three.c third.h
    gcc -c three.c

clean:
    rm -f main *.o
```

main就是最终要生成的目标文件，它是一个可执行文件。它所依赖的文件是one.o、two.o、three.o。下面的命令表明了如何生成它，使用`gcc -o main one.o two.o three.o`

接下来的三个文件表示每一个c程序的链接文件，它规定了这些链接文件由哪些c文件生成，还有c文件中包含的头文件。下面的命令是如何生成它。

他们的逻辑就是一层一层的。正述来说，先由c文件生成.o文件，然后再由.o文件生成最后的可执行文件。而makefile的叙述正好反过来，先表明最终目标文件，在说明它是怎么生成的。

最后的clean不是一个文件，是一个动作名字，它的冒号后面什么都没有，那么make就不会自动去找它的依赖，也就不会自动执行其后所定义的命令。要想执行他后面的命令只需要加上这个动作名字:`make clean` 。clean的规则不要放在文件开头，不然就会变成make的默认目标。一个makefile文件最好还是要有clean的，用来清理多余的目标或者链接文件，否则随着编译的累积，可能会产生大量的无用的链接文件（垃圾文件）。

## 第二个实例

使用到文件one.c、two.c、three.c、first.h、second.h、third.h 、four.c

```makefile
main: one.o two.o three.o
	gcc -o main one.o two.o three.o

fourmain: four.o
	gcc -o fourmain four.o

one.o: one.c first.h
	gcc -c one.c

two.o: two.c second.h
	gcc -c two.c

three.o: three.c third.h
	gcc -c three.c

four.o: four.c first.h second.h
	gcc -c four.c

clean:
	rm -f *main *.o
```

这个实例在第一个实力基础上，新增了一个可执行的目标文件fourmain。也就是说一个makefile文件可以同时规定多个可执行的目标文件。

在这个实例中，如果你执行`make`命令，那么他只会编译生成main、one.o、two.o、three.o不会执行生成fourmain的操作。如果想要编译生成fourmain，那么要执行`make fourmain`

在最后clean中，出现`*main`。这里适用shell的字符匹配规则。这个*号表示任意字符。

## 第三个实例

使用到文件（one.c、two.c、three.c、four.c、five.c、six.c、seven.c、eight.c、first.h、second.h、third.h)。

```makefile
objs = five.o six.o seven.o eight.o

main: one.o two.o three.o
	gcc -o main one.o two.o three.o

fourmain: four.o
	gcc -o fourmain four.o

fivemain: $(objs)
	gcc -o fivemain $(objs)

all: main fourmain fivemain

one.o: one.c first.h
	gcc -c one.c

two.o: two.c second.h
	gcc -c two.c

three.o: three.c third.h
	gcc -c three.c

four.o: four.c first.h second.h
	gcc -c four.c

five.o: five.c
	gcc -c five.c

six.o: six.c
	gcc -c six.c

seven.o: seven.c
	gcc -c seven.c

eight.o: eight.c
	gcc -c eight.c

clean:
	rm -f *main *.o
```

makefile里也可以定义变量。这里我定义了一个变量`objs`。这样我以后如果要用到它后面的哪些字符（five.o six.o seven.o eight.o）就可以直接使用变量代替啦。调用变量的办法：`$(objs)` 。详情参见：`fivemain`

在这个实例中，一共定义了三个可执行的目标文件（main、fourmain、fivemain）。前面已经讲过如果执行`make` ，那么它只编译main，而不编译其他。想要编译其他的目标文件，就需要加上他们的名字。现在我想要一个命令就编译所有的可执行目标文件。于是，我定义了一个`all` ，并在他后面写上了所有的可执行的目标文件。这样，我只需要执行`make all`就可以一次性把所有的可执行目标文件全都编译。
