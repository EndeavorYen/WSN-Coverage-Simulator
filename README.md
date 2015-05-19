# WSN-Coverage-Simulator
WSN Full Coverage Simulator

![Screenshot](Screenshot.jpg)

功能介紹 :
--------------------
  這個程式是採用C語言編寫的一個模擬器，功用是模擬WSN在地圖上佈Sensor點，是否能夠Full Coverage的問題。以及設立障礙物(挖洞)，觀察Sensor死掉後，地圖上Node被Cover的情況。
  
以下簡單介紹該模擬器的功能，以及使用方法 : 

   進入模擬器後，程式會先請使用者設定地圖的大小(或者說是Node的解析度)，接下來設定Sensor的覆蓋range大小。設定Node解析度在這裡稍微說明一下，當 ”Map的大小為 10 x 10, Sensor的Cover Range為 1”，和 “Map大小100 x 100，Sensor的 Cover Range為 10” 這兩種情況是一樣的，但是後者明顯的Node解析度(resolution)更高。解析度越高，越能更正確的判斷Map是否有被full covered，所以使用者電腦配備允許的話，建議提高Map的解析度來模擬，才會得到更精確的結果。

  完成上列的步驟後，主選單有6個功能可以選擇，介紹一下各個功能，以及說明一下使用方式 : 

[1] 顯示地圖 : 
   顯示目前地圖的狀態，確認佈點以及cover的狀態，是否符合所需的設定。

[2] 設定Sensor位置 : 
   手動輸入Sensor的位置，方便想在特定地方放置Sensor。若重複選擇有放置Sensor的點，該位置的Sensor會被取消掉，佈錯點或是想更改Sensor的位置可以善用此功能。

[3] 隨機布置Sensor位置 : 
   隨機在地圖上灑下指定數量的Sensor，有需要取消的Sensor也可以善用[2]的功能來移除。

[4] 挖洞 : 
   在地圖上挖障礙物(洞)，在洞內的Sensor視同死掉。設定的方法是採取座標位置(輸入起點座標以及結束座標，目前只可挖長方形的洞)，目前挖洞的功能強烈建議在設置完Sensor點之後才可設置。

[5] 計算是否Full Coverage : 
   顯示目前是否 Full Coverage，並且會顯示尚未被Cover的Node數目。

[6] 輸出結果至檔案中 : 
   將地圖輸出至log檔中，並且會顯示設置資訊。

[0] 結束程式 : 
   結束程式，關閉程式，終止程式。
