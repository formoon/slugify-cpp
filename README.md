### 应用
Slug格式是网址确定化的一种常见方案。  
在Slug之前，常见的网址可能是这样：http://www.someweb.com/article?id=332234。  
使用Slug之后，假设文章标题是《Something interesting》，这篇文章的路径可能就是：  
http://www.someweb.com/articles/something-interesting
优势是显而易见的。  

然后问题就来了，对于西文，Slug化的处理是很简单的，而中文就复杂多了。  
作为一个流行了好几年的方法，已经有很多成熟库处理中文字符。  
可惜的是作为不常用于网络编程的c++，一直没有好用的工具。  
直到追求性能的应用驱动，把c++也带入了后端开发的行列。  

### 使用
很简单，看代码：  
```cpp
// 首先要引入头文件
#include "slugify-cpp.hpp"

// 使用之前先要初始化，这是为了载入unicode对照表数据
slugify_init();
cout << slugify("混合的字符串 mixed string ♥") << endl;

//输出：
// Hun-He-De-Zi-Fu-Chuan-mixed-string-hearts
```
此外，pointers.bin/mapping.txt两个文件是unicode对照表的数据文件，需要跟项目在同一目录，或者根据自己需求修改slugify-cpp.cpp对应代码。  

### 引用
代码参考了Rust语言的Crate [deunicode](https://github.com/kornelski/deunicode/)，并且直接使用了其数据库。感谢原作者。  
  

