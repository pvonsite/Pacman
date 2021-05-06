# **PACMAN**
*If you don't know Vietnamese, read readme (English).md. This is for Vietnamese.*   
*Dự án cho bài thi giữa kì tại UET*

Xin chào mọi người, tên mình là Tùng. Đây là dự án đầu tiên của mình. Trong dự án này, mình sẽ làm về tựa game Pacman với một chút sáng tạo riêng, sử dụng ngôn ngữ [C++](https://en.wikipedia.org/wiki/C++) và thư viện [SDL 2.0](https://www.libsdl.org/download-2.0.php).

Nếu bạn muốn học về SDL2.0, hãy vào [website](https://lazyfoo.net/tutorials/SDL/index.php) này.

Tất cả các code trong project được viết bởi mình, không tham khảo nguồn ngoài.

Lần đầu viết một project nên code có hơi khó đọc.

Link video: https://youtu.be/kDltl4RT5_U

## Mục lục
1. [Cách tải và cài đặt game](#cách-tải-và-chơi-game)
2. [Cách chơi game](#cách-chơi-game)
3. [Chi tiết về game](#chi-tiết-về-game)
4. [Thuật toán của game](#thuật-toán-về-game) 
5. [Nguồn ảnh và âm thanh](#nguồn-ảnh-và-âm-thanh)

### Nội dung
1. ### Cách tải và cài đặt game

    Đầu tiên bạn sẽ cần cài đặt [Code::Blocks](https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/codeblocks-20.03mingw-setup.exe/download) để chạy C++, làm theo các hướng dẫn để cài đặt:  
        - [SDL 2.0](https://www.libsdl.org/download-2.0.php)  
        - [SDL_image](https://www.libsdl.org/projects/SDL_image/)  
        - [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)  
        - [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)  

    Sau khi xong, tải file zip game của mình trên github về và giải nén chúng.  

    Sau đó mở `Code::Blocks` và nhấn vào `Open an existing project`. Di chuyển tới chỗ file đã giải nén và nhấn `Pacman.cbp`.

    Sắp tới mình sẽ tạo file zip có sẵn game để các bạn dễ chơi. Khi mình làm xong mình sẽ cập nhật ở [đây]() và đầu README.

2. ### Cách chơi game   
 
    Bạn điều khiển nhân vật màu vàng hình tròn tên `Pacman` ![](Source/Assets/Entity%20Image/pacman%20icon.png). Nhiệm vụ của mình là ăn hết các  `dot` ![](Source/Assets/Entity%20Image/dot.png) (hay còn gọi là `coin`) trong mê cung, lên bàn tiếp theo, giành được điểm thật cao. Sau khi ăn hết thì bạn sẽ được lên bàn tiếp theo. Bạn sẽ có 3 mạng
    
    Dùng phím W A S D hoặc các phím mũi tên để điều khiển `Pacman`.
    
    Ngăn cản bạn hoàn thành bàn chơi và giành được điểm cao là 6 con ma: `Blinky`, `Pinky`, `Clyde`, `Inky`, `Greendy`, `Friendy`.
    
    Trong bản game gốc thì có 4 con ma đầu, mình đã thêm 2 con ma nữa vào cho thêm thú vị.

    Ăn chấm sức mạnh ![](Source/Assets/Entity%20Image/power%20dot.png) (thường được gọi là `power dot`) bạn sẽ có một khoảng thời gian để ăn được các con ma. Ăn một con ma đang hoảng sợ cho bạn rất nhiều điểm và khiến con ma chạy về chỗ lồng chứa.
3. ### Chi tiết về game

    Game là một mê cung gồm có 28x31 ô.     
    Có tất cả 244 chấm trong 1 bàn, 240 chấm bình thường và 4 chấm sức mạnh.   

    Trong game gốc, có tất cả 256 level, sau level 255 game sẽ lỗi (do hồi đó bộ nhớ xây trên bit). Trong game của mình thì giới hạn là `2^31-1 level`.
    
    Đấy là giới hạn của biến `int`. Chính ra thì mình nên để giới hạn nhưng mình nghĩ cũng không ai rảnh cày đến tận level này đâu. 

    Về mỗi con ghost thì bọn chúng có một cách hoạt động riêng. Nhìn chung thì chúng có 3 trạng thái:

    #### `Đuổi`
    - [`Blinky`]() ![](Source/Assets/Entity%20Image/blinky%20icon.png): đuổi theo `Pacman`.   
    - [`Pinky`]() ![](Source/Assets/Entity%20Image/pinky%20icon.png): đi đến vị trí trước mặt `Pacman` 4 ô.
    - [`Inky`]() ![](Source/Assets/Entity%20Image/inky%20icon.png): đi đến vị trí được tạo bằng cách đối xứng vị trí của `Blinky` ![Blinky](Source/Assets/Entity%20Image/blinky%20icon.png) qua tâm là `Pacman`.
    - [`Clyde`]() ![](Source/Assets/Entity%20Image/clyde%20icon.png): đuổi theo Pacman nếu khoảng cách giữa nó và Pacman lớn hơn 8 ô, nếu không thì nó sẽ về góc của mình.  
    #### `Thăm dò`
    Trong trạng thái thăm dò, các con ma sẽ đi xung quanh 1 góc của bản đồ. Trong thời gian này `Pacman` sẽ dễ thở hơn.

    #### `Hoảng sợ`    
    Ngoại trừ con `Friendy`, trong trạng thái hoảng sợ, các con ma sẽ chuyển sang màu xanh như này  ![](Source/Assets/Entity%20Image/frighten%20ghost%20icon.png) và `Pacman` có thể ăn chúng trong 1 khoảng thời gian nhất định.

    Sau khi ăn thì con ma đó sẽ chuyển thành `đôi mắt` ![](Source/Assets/Entity%20Image/ghost%20eye.png), tìm đường ngắn nhất và đi về phía trước của lồng và hồi sinh.

    2 trạng thái đầu sẽ luân phiên nhau, trạng thái hoảng sợ sẽ chỉ kích hoạt khi Pacman ăn chấm sức mạnh.  
    Thêm thông tin về phần này: https://pacman.fandom.com/wiki/Maze_Ghost_AI_Behaviors  

    Mình có tạo 2 con ma mới:

    - `Greendy` ![](Source/Assets/Entity%20Image/greendy%20icon.png): Như cái tên của nó thì Greendy có màu xanh, sở thích của nó là ăn táo xanh ![](Source/Assets/Entity%20Image/greenapple.png). Greendy và táo xanh sẽ xuất hiện từ level 3 trở đi. Táo xanh sẽ xuất hiện ở góc trên trái đầu bàn chơi và sau đó thì là random 1 trong các góc. Greendy sẽ rời khỏi lồng khi trên mê cùng còn dưới 100 chấm. Sau khi rời lồng, nó ngay lập tức tìm đến táo xanh. Ăn được táo xanh sẽ giúp `Greendy` di chuyển nhanh gấp 2 lần trong 2s, đuổi theo `Pacman`. Sau khi hết thời gian thì nó lại đi tìm táo xanh. 

    - `Friendy` ![](Source/Assets/Entity%20Image/friendy%20icon.png): Đây là một con ma đặc biệt. Nó có màu vàng, như `Pacman` vậy, nhưng tối hơn. Nó là một người quan tâm tới bạn bè (bạn ở đây là mấy con ma ấy). Xuất hiện từ level 5. Rời khỏi lồng từ đầu game, nhưng chỉ đi một cách ngẫu nhiên trong mê cung. Nhưng nếu bạn ăn chấm sức mạnh `power dot`, đe dọa bạn của nó, nó sẽ không bị hoảng sợ, thay vào đó chuyển sang đuổi `Pacman` trong 3s. 
4. ### Thuật toán của game
    -------------------------------
    Đầu tiên là về thuật toán giúp các con ma đuổi theo `Pacman`.

    Trong game gốc thì nhà phát triển dùng [khoảng cách Euclid](https://vi.wikipedia.org/wiki/Euclidean_distance) để giúp con ma tìm đường đến đích. Điều này làm cho thi thoảng con ma đi đường xa hơn, không tối ưu cho lắm.
    
    Trong game của mình thì các con ma sẽ có mấy cái như sau:   
    *Gốc tọa độ trong game được lấy ở góc trái trên, Ox hướng sang phải, Oy hướng xuống dưới*
    - `tileX`: Vị trí ô hiện tại theo trục Ox
    - `tileY`: Vị trí ô hiện tại theo trục Oy
    - `scrPosX`: Vị trí trên màn hình hiện tại theo trục Ox
    - `scrPosY`: Vị trí trên màn hình hiện tại theo trục Oy
    - `nextTile (X, Y)`: tọa độ đích đến     
    
    Trong game gốc thì nhà phát triển quản lý bằng các ô, mình quản lý vị trí bằng vị trí trên màn hình.

    Khi mà con ma bước sang 1 ô mới thì mình sẽ phải tìm đường đi tốt nhất để đến đích. Có 3 hướng được phép ở đây (nếu như hướng đó là tường thì không tính): `phía trước mặt`, `quay 90 độ theo chiều kim đồng hồ`, `quay ngược chiều kim đồng hồ 90 độ`. Mình dùng BFS để tính trước xem từ một ô bất kì đến một ô nào đó của mê cung mất bao bước đi, với điều kiện là tại mỗi bước đi con ma không được quay đầu ngược lại so với hướng cũ của nó. BFS mình tính từ trước khi bạn ấn newgame nên nó sẽ ko bị chậm.

    Khi ma bước sang ô mới, từ 3 hướng mình nói ở trên, mình lấy hướng có bước đi nhỏ nhất. Nếu như đích đến là tường, thì mình dùng `khoảng cách Euclid` thay cho cái hướng đó. Trong quá trình chơi, nếu bạn thấy con ma không đi theo hướng tối ưu, thì đừng hiểu nhầm, chúng nó chỉ đang đi theo đường đến mục tiêu của nó. Mỗi con ma có một mục tiêu riêng mà. 


    ----------------------
    Tiếp theo hãy nói về chuyển động của Pacman.

    Khi mình thiết kế game, mình muốn Pacman đi ở giữa đường.

    Khi chơi, nếu thấy phía trước là lối rẽ, thường xu hướng của chúng ta là ấn nút rẽ sớm hơn, cách đấy khoảng một đoạn. 

    Lúc đầu, khi code, mình để khi người chơi nhấn nút thì lập tức Pacman sẽ rẽ luôn. Lúc này phát sinh 1 vấn đề. Mình muốn Pacman đi ở giữa, như vậy thì Pacman luôn ở vị trí 8 của ô (1 ô kích thước 16x16). Giả sử Pacman đang ở vị trí 10 mà người chơi ấn rẽ, Pacman rẽ luôn, lập tức bị lệch ra khỏi đường. Mà mình check tường theo ô. Bởi check tường theo vị trí trên màn hình sẽ phải check từng pixel một, điều này rất khó. Khi mà Pacman lệch như thế sẽ rất dễ tình trạng Pacman nhảy ra khỏi maze, gây bug.

    Sau khoảng 2 - 3 ngày loay hoay, mình tìm ra giải pháp. Đó là mình tìm trước xem tại ô này, nếu theo hướng này, thì có lối rẽ không, lối rẽ đấy có đi được không. Khi người chơi nhấn nút rẽ so với hướng đang đi, nếu như phía trước có lối rẽ và rẽ được thì mình ghi nhận lệnh rẽ vào 1 hàng đợi. Khi con ma đi đến đúng ngã rẽ thì mình mới đè lệnh rẽ vào.

    Làm như vậy, chuyển động của Pacman tại mỗi chỗ rẽ rất mượt, Pacman vẫn đi đúng giữa đường, người chơi vẫn có thể giữ thói quen.

5. ### Nguồn ảnh và âm thanh

    Hầu hết các ảnh trong game của mình đều tạo bởi mình. Mình vẽ chúng bằng photoshop. Mình cũng có tìm trên mạng nhưng không thấy phù hợp nên mình tự vẽ. Mình vẫn để file photoshop nếu các bạn có muốn sửa gì. Một số cái mình lấy trên mạng:

    - green-apple: http://pixelartmaker.com/art/5adcfa718020edf
    - arrow-wasd: nguồn ảnh là của adobe nhưng mình quên mất link rùi.
    - youlose: https://www.vectorstock.com/royalty-free-vector/you-lose-rubber-stamp-vector-17695736  
    - pacman-dead: https://www.deviantart.com/friendbeard/art/Dead-Heroes-Pacman-511878694  

    Âm thanh thì mình tìm thấy ở [apple music](https://music.apple.com/us/album/pac-man-game-sound-effect/328036461). Tuy nhiên là phải mất tiền mới có được, khá là buồn. Thế nên mình dùng một chrome extension, Audio Capture, để thu âm cái tab sau đó dùng [Cut Mp3 Online](https://mp3cut.net/vi/) để cắt âm thanh.



## *Kết thúc rồi. Chơi game vui nhé !!!* 

    




