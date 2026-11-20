# Dogat
 
Jogo de plataforma cooperativo em C com [raylib](https://www.raylib.com/).
Você controla um cachorro e um gato, alternando entre os dois, e leva os dois até as casinhas deles em cada fase.

### Controles
 
| Tecla | Ação |
|---|---|
| `ENTER` | Iniciar o jogo (na tela inicial) |
| `←` `→` ou `A` `D` | Andar |
| `↑` ou `W` | Pular |
| `ESPAÇO` | Trocar entre cachorro e gato |
| `ESC` | Sair |

### Vídeo da gameplay:
[Youtube](https://youtu.be/66GXMJMB2wc)

## Rodar no Windows
 
Pré-requisito: [raylib](https://www.raylib.com/) instalado em `C:\raylib` (com `gcc` / MinGW).
 
```
mingw32-make
.\Dogat.exe
```

## Rodar no Linux

#### Compilando na máquina (alternativa 1)

```
sudo apt install build-essential git cmake libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
git clone https://github.com/raysan5/raylib.git
cd raylib && mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=OFF .. && make && sudo make install
cd ../..
make
./Dogat
```

#### Baixar o jogo pronto no Linux (alternativa 2)
 
1. Abra a aba **Actions** do repositório no GitHub e clique na execução mais recente do **Build Linux**.
2. Role até **Artifacts** e baixe `dogat-linux`.
3. No terminal:
```
unzip dogat-linux.zip
tar -xzf dogat-linux.tar.gz
cd dogat-linux
./Dogat
```