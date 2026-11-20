# Dogat
 
Jogo de plataforma cooperativo em C com [raylib](https://www.raylib.com/).
Você controla um cachorro e um gato, alternando entre os dois, e leva os dois até as casinhas deles em cada fase.

<img src="https://64.media.tumblr.com/695206b9016139f7bcbe36e3b21ae1bc/35972c1d916e180e-b5/s1280x1920/2dd451edbd44fd8be4be19b1b3b168cae1f8a714.gif" width="40"> <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fusagif.com%2Fwp-content%2Fuploads%2Fgifs%2Fdancing-cat-18.gif" width="40"> <img src="https://64.media.tumblr.com/695206b9016139f7bcbe36e3b21ae1bc/35972c1d916e180e-b5/s1280x1920/2dd451edbd44fd8be4be19b1b3b168cae1f8a714.gif" width="40"> <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fusagif.com%2Fwp-content%2Fuploads%2Fgifs%2Fdancing-cat-18.gif" width="40"> <img src="https://64.media.tumblr.com/695206b9016139f7bcbe36e3b21ae1bc/35972c1d916e180e-b5/s1280x1920/2dd451edbd44fd8be4be19b1b3b168cae1f8a714.gif" width="40"> <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fusagif.com%2Fwp-content%2Fuploads%2Fgifs%2Fdancing-cat-18.gif" width="40"> <img src="https://64.media.tumblr.com/695206b9016139f7bcbe36e3b21ae1bc/35972c1d916e180e-b5/s1280x1920/2dd451edbd44fd8be4be19b1b3b168cae1f8a714.gif" width="40"> <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fusagif.com%2Fwp-content%2Fuploads%2Fgifs%2Fdancing-cat-18.gif" width="40"> <img src="https://64.media.tumblr.com/695206b9016139f7bcbe36e3b21ae1bc/35972c1d916e180e-b5/s1280x1920/2dd451edbd44fd8be4be19b1b3b168cae1f8a714.gif" width="40">

### Controles
 
| Tecla | Ação |
|---|---|
| `ENTER` | Iniciar o jogo (na tela inicial) |
| `←` `→` ou `A` `D` | Andar |
| `↑` ou `W` | Pular |
| `ESPAÇO` | Trocar entre cachorro e gato |
| `R` | Resetar a fase |
| `ESC` | Sair |

### Vídeo da gameplay:
[![YouTube](https://img.shields.io/badge/YouTube-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://youtu.be/66GXMJMB2wc)

*clique aqui* ⬆️

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
