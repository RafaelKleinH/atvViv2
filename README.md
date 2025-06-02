# atvViv2

Compilar:
g++ -framework Cocoa -framework OpenGL -framework IOKit -o AtvViv2 AtvViv2.cpp  stb_image.cpp gl_utils.cpp -I include -I/opt/homebrew/include /opt/homebrew/lib/libGlew.a /opt/homebrew/lib/libglfw3.a -I/opt/homebrew/Cellar/glfw/3.4/include/

Rodar:
./AtvViv2

Pontos extras:

Só eu commitei pois estava codando no mac e o Breno no Windows, então pra nao ficar gerando conflito codamos junto em call mas pelo meu mac. :D

Outro ponto, colocamos um limite no Y pois ficava feio o y ser infinito, diferente do X que é infinito, ainda da pra notar a parelax Y e a cena fica bonitinha. Colocamos como personagem os passarinhos. Eles ficam no meio e o mundo muda com a perspectiva deles. :D