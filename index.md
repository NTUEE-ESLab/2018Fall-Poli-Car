track car
==
[id]:https://github.com/NTUEE-ESLab/track-car/blob/ghmaster/FINAL_REPORT.pdf
更多細節可以參閱我們的 [final report][id]

## Author
Pang-Cheng, Chen 陳邦正 <b05901037@ntu.edu.tw>   
Ching-Jin, Chen 陳慶瑾 <rogerchen0109@gmail.com>

## Abstract
在現今人工智慧與運算能力的日漸發展下，許許多多的簡單事件能夠交由電腦來處理，使得空閒下來的人力能夠去處理其他難以使用運算解決的問題，於是我們便想到了利用具有高度運算能力的Jetson TX2開發板來製作一台具有車牌辨識功能的軌跡車。

## Demo 影片
  Click [Here](https://drive.google.com/file/d/1F-WUsDC2_nmF16Zcxlg7ahGLO5Dojr4a) for demo video
  
## 開發環境
### 硬體
  * NVidia Jetson TX2
  * Arduino Uno
  * 19V/3.42A Power supply
  * 舵機
  * 馬達

### 軟體需求
  * python3 
  * openCV 3.4.2
  * numpy

## 運作機制
### 車牌辨識系統
這台影像辨識車是利用NVidia TX2這塊開發板來進行運算，並且使用python3 + openCV的套件來處理，主要的辨識重點有三項：第一項是  STOP  這個標誌，第二項是道路的轉彎狀態以及第三項為這次專題重點----車牌辨識。在影像辨識上，主要是先將圖片灰階化，再利用KNN演算法（CV2具有內建函式）來判定STOP字樣以及車牌號碼，KNN演算法主要是透過鄰近的node進行多數表決的演算法，雖然相較之下簡單，可以降低尋找車牌輪廓的時間，但是也相對容易產生誤判。轉彎控制上，則是會將畫面切成由上到下的五格，每一格擷取輪廓，並計算輪廓邊界的中點，將五張照片從左到右給一個weight從左到右分別為從-720到720，0為正中間，然後由上到下，根據圖像得到的weight計算軌道的角度，藉此來給予轉彎控制，另外為防止cv2的函式判斷到錯誤的輪廓，當鄰近的兩格weight超過一個閾值(在本project設定為150)，便把兩個值設定為-1000，而往下進行軌道運算時，便不會把-1000的值納入運算中。

### 驅動機制
首先是在透過在/etc/xdg/下寫一個desktop檔，並讓他執行一個在相同路徑的deploy.sh的檔案來完成開機自動執行程式。在deploy.sh中，一開始我們與助教想要透過產生一個terminal來完成實驗，不過後來發現會導致程式沒有辦法正常執行，所以最後我們是直接呼叫/usr/bin/python3，才使得程式得以正常運作。接著是車輛控制的部分：當TX2上面的辨識系統成功辨識到STOP字樣的時候，會透過Serial傳送訊號到arduino的板子，讓馬達的輸出pin腳位電壓降至0V，來達成辨識到stop即停車兩秒的效果。另外，影像辨識判斷到對應的轉彎角度時，會傳值到arduino開發板並且控制舵機給出適當的轉彎角度。

## 參考資料
[KNN演算法](https://zh.wikipedia.org/wiki/%E6%9C%80%E8%BF%91%E9%84%B0%E5%B1%85%E6%B3%95?fbclid=IwAR2vVCdGFLjZ6T2K-jANvHageiDzsQwjveFh_sb_RnCoQMQk55WO32otUko)
[車牌辨識原始碼](https://www.youtube.com/watch?v=fJcl6Gw1D8k&fbclid=IwAR2t-Z5ED17ThWwx45rfQ3B0-BgsZfVI7Q1PVL2GlIsW7lCxiiCCX8ANpOo)
[cv2繪製輪廓函式使用方法](https://www.pyimagesearch.com/2014/04/21/building-pokedex-python-finding-game-boy-screen-step-4-6/?fbclid=IwAR1sic3SGrXQAReDMFNLagDe4eF7UlNgAr70lMJvv2JbgcRnlG7IR2kexUg)
