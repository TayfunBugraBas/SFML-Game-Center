# SFML-Game-Center

<----Program Çalıştırma Prosedürleri---->

<----1.Adım---->
Proje yürütme Dosyasını "SFMLProjet.sln" Visual studio ile açınız.
<----2.Adım---->
Projeyi çalıştırınız.
Proje Hata verirse ilerideki adımları uygulayınız.


<----3.Adım---->
Visual Studionun üst bar çubuğundan proje sekmesinde "SFMLProject özellikleri" adlı kısıma tıklayınız.
Yapılandırma ayarlarını tüm yapılandırmalar yapınız ve bu durumu ileriki aşamalarda kontrol etmeyi unutmayınız.
<----4.Adım---->
C/C++ kısmına tıklayınız.
<----5.Adım---->
Ek İçeren dizinler kısmına tıklayarak Düzenleye basınız.
SFMLProject\freeglut\include
SFMLProject\GLFW\include
SFMLProject\glew-2.1.0\include
SFMLProject\SFML-2.5.1\include 
directorylerini kopyalayarak yapıştırınız.
<----6.Adım---->
Tamam tuşuna basıp Bağlayıcı->Genel kısmına tıklayınız
Ek kitaplık dizinine tıklayarak düzenle yazısına basınız.
SFMLProject\freeglut\lib\x64
SFMLProject\GLFW\lib-vc2019
SFMLProject\glew-2.1.0\lib\Release\x64
SFMLProject\SFML-2.5.1\lib
directorylerini kopyalayarak yapıştırınız.
<----7.Adım---->
Tamam tuşuna basıp Bağlayıcı->Giriş kısmına tıklayınız
Ek bağımlılıklar yazısına tıklayarak düzenleye basınız.
openal32.lib
SFMLProject\glew-2.1.0\lib\Release\x64 içerisindeki glew32s.lib ,glew32.lib
SFMLProject\freeglut\lib\x64 içerisindeki freeglut.lib
SFMLProject\GLFW\lib-vc2019 içerisindeki glfw3.lib,glfw3_mt.lib,glfw3dll.lib
ve
SFMLProject\SFML-2.5.1\lib içerisindeki graphics,audio,window,system,main ile ilgili .lib dosyalarını yazınız
<----8.Adım---->
Tamam tuşuna basınız daha sonra sağ alt tarafta gözüken uygula tuşuna basınız.
Bütün bunları yaptıktan sonra hatalarınızın çözülmüş olması gerekmektedir aksi tyakdirde bana ulaşınız.






