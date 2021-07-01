使用的IDE为Microsoft Visual Studio，只记录源代码。



## daily_active

仅用于熟悉控制台界面的编辑



## typing_game

原项目来源https://www.51zxw.net/Show.aspx?cid=717&id=78854

一款打字游戏，随机生成字母下落，消除字母得分，字母落地扣血。有3种难度可选。

对教程的代码进行了修改、优化，增加了一些功能：

* 每个字母容器都在尾部插入、头部删除，且要对容器进行遍历，所以将LetterShower类的成员变量m_letters从`vector容器`改为`deque容器`。
* Menu类用于管理光标位置和字体颜色；
* Health类管理血量；
* LetterShower类管理字母的生成、下落和计分。
* Record类将每次游玩的得分和时间记入`.type_game_record`文件中，得分为0的结果不保存。
* 绘制界面的工作改由`main.cpp`中的全局函数来完成。

增加排名界面，显示玩家的历史得分、最高分。最多只能正常显示14条记录，且按记录录入的时间排序，无法调整。

目标：

增加MySQL，还是最多显示14条记录，但



