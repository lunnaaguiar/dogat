#include "estados.h"
#include <stdio.h>

// #include "player.h"
// #include "interactable.h"

// 0 - ATTRACT MODE
void AttractModeUpdate();
void AttractModeDraw();

// 1 - PLAYING
void PlayingUpdate(Jogo *jogo, float dt){

    // obs: inserir função de salvar tempo depois

    // alternar entre personagens 
    if (IsKeyPressed(KEY_SPACE)) {
            jogo->dog.isActive = !jogo->dog.isActive;
            jogo->cat.isActive = !jogo->cat.isActive;
        }

        // if (IsKeyPressed(KEY_M)){
        //     SalvarTempo(jogo->tempo.min, jogo->tempo.sec, jogo->tempo.ms);
        // }


    // player update
    PlayerUpdate(&jogo->dog, dt, jogo->parede); 
    PlayerUpdate(&jogo->cat, dt, jogo->parede);

    // colisão e interação com objetos
    CaixaUpdate(&jogo->caixa, dt);
    EmpurrarCaixa(&jogo->dog, &jogo->caixa, true, &jogo->cat);
    EmpurrarCaixa(&jogo->cat, &jogo->caixa, false, NULL);
    
    // regras do multijogador
    carregarPlayerMulti(&jogo->dog, &jogo->cat); // colisão pro gato subir no cachorro
}

void PlayingDraw(const Jogo *jogo){
    BeginDrawing();
    
        ClearBackground(BLACK);
        DrawLine(0, 600, 1280, 600, WHITE); // antigo chão

        DrawMapa(); // repetição que desenha cada tile para visualização da colisão
        
        // desenhos dos players
        PlayerDraw(&jogo->cat);
        PlayerDraw(&jogo->dog);
        
        CaixaDraw(&jogo->caixa);
        
        // timer
        // DrawText(TextFormat("Time: %02d:%02d:%02d", (int)min, (int)sec, (int)ms), 10, 40, 20, WHITE);
    
        
        EndDrawing(); // finaliza
}