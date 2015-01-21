## vim的配色方案的调整

用vim编写程序时，有时需要调整vim的默认配色方案，例如，我就很喜欢sublime的Monokai配色方案，那么，我可能就会想将vim的配色方案变成Monokai，但是，vim的配色方案中是没有Monokai的，那怎么办呢？

### 1 与vim配色方案相关的文件

与vim配色方案相关的文件有主文件夹的部分和系统部分。

主文件夹的部分有：~/.vimrc，这个就是vim的设置文件，与配色相关的就是文件中的colorscheme那一行。

系统部分有：/usr/share/vim/vim73/colors/，这个是存放vim的配色方案，当然，有可能因为版本不同而路径不完全一样。

因此，要修改配色方案，只要修改这两部分就行。

### 2 将配色方案调整为sublime的Monokai

先去[vim-monokia](https://github.com/sickill/vim-monokai)下载monokai配色方案。

将monokai.vim拷贝到/usr/share/vim/vim73/colors/目录下，然后修改~/.vimrc，将colorscheme那一行改为colorscheme monokai(如果没有的话，就添加)，然后打开vim就可以了。
