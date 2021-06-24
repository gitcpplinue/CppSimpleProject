## daily_active

仅用于熟悉控制台界面的编辑



## typing_game

原项目来源https://www.51zxw.net/Show.aspx?cid=717&id=78854

一款打字游戏，随机生成字母下落，消除字母得分，字母落地扣血。有3种难度可选。

对教程的代码进行了修改、优化：

* 添加了Menu类，使用Menu类管理、执行界面的绘制。
* 每个字母容器都在尾部插入、头部删除，且要对容器进行遍历，所以将LetterShower类的成员变量m_letters从`vector容器`改为`deque容器`。
* 

