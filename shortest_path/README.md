# 最短路算法

## 编译

```
xmake
```

## 使用

```
shortest_path [matrix.txt]
```

参数缺省时读取当前目录下的`matrix.txt`

## 例子

输入(第一行注明节点个数，方便程序解析)：
```
6
0 50 oo 40 25 10
50 0 15 20 oo 25
oo 15 0 10 20 oo
40 20 10 0 10 25
25 oo 20 10 0 55
10 25 oo 25 55 0
```

输出如下：
```
shortest path of node 1 -> node 2: 35.000000
road:
        2 <- 6 <- 1
 
shortest path of node 1 -> node 3: 45.000000
road:
        3 <- 5 <- 1
 
shortest path of node 1 -> node 4: 35.000000
road:
        4 <- 6 <- 1
 
shortest path of node 1 -> node 5: 25.000000
road:
        5 <- 1
 
shortest path of node 1 -> node 6: 10.000000
road:
        6 <- 1
 
shortest path of node 2 -> node 3: 15.000000
road:
        3 <- 2
 
shortest path of node 2 -> node 4: 20.000000
road:
        4 <- 2
 
shortest path of node 2 -> node 5: 30.000000
road:
        5 <- 4 <- 2
 
shortest path of node 2 -> node 6: 25.000000
road:
        6 <- 2
 
shortest path of node 3 -> node 4: 10.000000
road:
        4 <- 3
 
shortest path of node 3 -> node 5: 20.000000
road:
        5 <- 3
 
shortest path of node 3 -> node 6: 35.000000
road:
        6 <- 4 <- 3
 
shortest path of node 4 -> node 5: 10.000000
road:
        5 <- 4
 
shortest path of node 4 -> node 6: 25.000000
road:
        6 <- 4
 
shortest path of node 5 -> node 6: 35.000000
road:
        6 <- 4 <- 5
 
```
