# Dự án cuối kì 
I,Hướng dẫn cài đặt và chạy game

  B1:Tải Visual Studio Code

    Tạo folder Nghia trong ổ G, trong Nghia tạo thư mục Library

    Tải folder Tetris về (download file Zip và giải nén) và để trong Nghia


![G](https://user-images.githubusercontent.com/100202140/170916120-bc40d8aa-f3a7-402b-a1ef-e08247f07b13.png)


  B2: 
  
    Tải mingw32 tại link https://sourceforge.net/projects/mingw-w64/postdownload
    
    Tải SDL2 tại link https://www.libsdl.org/release/SDL2-devel-2.0.20-mingw.tar.gz
    
    Tải SDL2 image tại link https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz
    
    Tải SDL2 ttf tại link https://www.libsdl.org/projects/SDL_ttf/release/
    
    Giải nén các file vừa tạo và để trong folder Library



![Screenshot 2022-05-30 111143](https://user-images.githubusercontent.com/100202140/170915739-5caa8e8f-8950-4776-83ac-435c275de81b.png)

  B3: Setup

      Vào mingw32 -> bin và copy đường dẫn đến bin

      Vào path -> Environment variable -> Path -> 

      Tạo new và dán đường dẫn vừa copy vào 

      (Tương tự với SDL2,SDL image,SDL ttf) 


![path](https://user-images.githubusercontent.com/100202140/170919019-ddba89f9-402b-466b-bbd9-b4f3d6815d45.png)


  B4:

      Mở terminal tại thư mục chứa project, sử dụng lệnh mingw32-make để build

      Chạy ./main.exe

II, Mô tả chung về trò chơi

  Game có 2 chế độ, chế độ Easy là chế độ tetris cổ điển,khi các Block xếp kín 1 hàng thì hàng đó sẽ biến mất, chế độ Hard là chế độ kết hợp giữa 2048 và Tetris,các khối giống nhau ở cạnh nhau sẽ kết hợp làm 1, game kết thúc khi đạt đến 1 số điểm nhất định hoặc màn hình full block

  link Youtube: https://www.youtube.com/watch?v=HCpBMYxupPw

III, Các chức năng của trò chơi

  Menu đơn giản 
  Điều khiển bằng các phím mũi tên
  Chế độ hard có tính điểm, có retry khi kết thúc 

IV, Các kỹ thuật lập trình được sử dụng
  Sử dụng thư viện đồ họa SDL,SDL image,SDL ttf
  Struct, Class
  Mảng

V, Kết luận
Là dự án game đầu tay nên không tránh khỏi các thiếu xót, mong rằng sẽ nhận được góp ý từ mọi người

Hướng phát triển tiếp theo của game:
Chế độ Easy
  Update thêm phần cập nhật điểm số và tạo thêm ô để dự đoán block tiếp theo sẽ rơi xuống 

Chế độ Hard 
  Update Skill Búa (khi người chơi đạt đến số điểm nhất định) sẽ có skill búa để phá 1 khối bất  kì  (đã làm được 50%)
  Tạo thêm skill Swap để tráo đổi vị trí 2 khối theo ý mình 
  Thêm tính năng lưu trữ tiến độ chơi khi Exit giữa chừng

Sau khi hoàn thiện chương trình, thứ em tâm đắc nhất là
