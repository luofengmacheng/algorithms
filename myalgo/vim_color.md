## vim的配色方案的调整

用vim编写程序时，有时需要调整vim的默认配色方案，例如，我就很喜欢sublime的Monokai配色方案，那么，我可能就会想将vim的配色方案变成Monokai，但是，vim的配色方案中是没有Monokai的，那怎么办呢？

### 1 与vim配色方案相关的文件

与vim配色方案相关的文件有主文件夹的部分和系统部分。

主文件夹的部分有：~/.vimrc和~/.vim/colors/，.vimrc是vim的设置文件，与配色相关的就是文件中的colorscheme那一行。.vim/colors/是某个用户的配色方案文件夹。

系统部分有：/usr/share/vim/vim73/colors/，这个是存放所有用户的vim的配色方案，当然，有可能因为版本不同而路径不完全一样。

因此，要修改配色方案，只要修改这两部分就行。

### 2 将配色方案调整为sublime的Monokai

先去[vim-monokia](https://github.com/sickill/vim-monokai)下载monokai配色方案。

如果将monokai.vim拷贝到/usr/share/vim/vim73/colors/目录下，那么，系统所有用户都可以使用该配色方案。如果将monokai拷贝到~/.vim/colors/目录下，那么，只有该用户才能使用该配色方案。

然后，将colorscheme那一行改为colorscheme monokai(如果没有的话，就添加)，然后打开vim就可以了。
