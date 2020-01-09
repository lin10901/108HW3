# 108HW3
FIFO
LRU

選取要進行FIFO,還是LRU
讀取檔案將讀入資料分別存入index,tag
將index 轉成10位元
將index%找出存放位子,設一個位子最多只能存4-way
進入位子前先查tag有無相同,若為相同紀錄HIT
接著尋找有無空位若為全空放由array最前的位子開始放起,
若無空位將array最前位子的值取出,後面值往前方移動,新值放array尾端

若為LRU當HIT的情況,array該位子紀錄HIT數量,找HIt值最小的值,若HIT值相同array前方比後方優先被取代,
將值取出,後面值往前方移動,新值放array尾端

最後印出total hit;




執行結果

FIFO
![image](https://github.com/lin10901/108HW3/blob/master/hw3fifo-1.png)
![image](https://github.com/lin10901/108HW3/blob/master/hw3fifo-2.png)

LRU
![image](https://github.com/lin10901/108HW3/blob/master/hw3lru-1.png)
![image](https://github.com/lin10901/108HW3/blob/master/hw3lru-2.png)
![image](https://github.com/lin10901/108HW3/blob/master/hw3lru-3.png)
