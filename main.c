#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "menu.h"
#include "recordes.h"
#include "personagem.h"
#include "labirinto.h"

void Config_Ini();

    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_DISPLAY_MODE dados_janela;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_BITMAP *instrucoes = NULL, *pers_sprite = NULL, *fundorecordes = NULL;
    ALLEGRO_BITMAP *fundo1 = NULL, *fundo2 = NULL,*fundo3 = NULL, *fundomenu = NULL;
    ALLEGRO_TIMER *temp = NULL;
    FILE *txt = NULL;

    int LARGURA = 0, ALTURA = 0;

    char Nome_aux[3];

int main (){

    int fim = 0, cursor = 1, jogo_state = 0, min = 0, i_nome = 0,
        f_insere = 0, f_atualiza = 0,f_gera = 0, f_move = 0;
    float seg = 0;
    int tecla[] = {0,0,0,0,0,0};
    struct recordista novo = {"   ",0,0};

    Config_Ini();

    int tam_celula = (LARGURA/ALTURA)*50;
    int tam_personagem = tam_celula - 20;
    int max_larg = (LARGURA/tam_celula) - 1;
    int max_alt = (ALTURA/tam_celula) - 4;
    int larg_lab = 0, alt_lab = 0;
    int cel_atual = 0;
    int rand_fundo;

    struct personagem Personagem;

    srand(time(NULL));

    ALLEGRO_EVENT evento;
    ALLEGRO_TIMEOUT tempo_aguardo;
    al_init_timeout(&tempo_aguardo,0.01);

    while(!fim)
    {
        al_wait_for_event_until(fila_eventos,&evento,&tempo_aguardo);
        al_clear_to_color(al_map_rgb(0,0,0));

        if(evento.type == ALLEGRO_EVENT_TIMER)
        {
                seg+=0.01;
                if(seg >= 59)
                {
                    seg = 0;
                    min++;
                }
        }
        else if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(evento.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    tecla[ESC] = 1;
                break;
                case ALLEGRO_KEY_UP:
                    tecla[CIMA] = 1;
                break;
                case ALLEGRO_KEY_RIGHT:
                    tecla[DIREITA] = 1;
                break;
                case ALLEGRO_KEY_LEFT:
                    tecla[ESQUERDA] = 1;
                break;
                case ALLEGRO_KEY_DOWN:
                    tecla[BAIXO] = 1;
                break;
                case ALLEGRO_KEY_ENTER:
                    tecla[ENTER] = 1;
                break;
            }

            if(tecla[CIMA] == 1 && jogo_state == 0)
            {
                if(cursor == 1) cursor = 1;
                else cursor--;
            }
            else if(tecla[BAIXO] == 1 && jogo_state == 0)
            {
                if(cursor == 4) cursor = 4;
                else cursor++;
            }else if(tecla[ESC] == 1)
            {
                al_stop_timer(temp);

                Limpa_Aux(&novo, Nome_aux);

                i_nome = 0;

                f_atualiza = 0;

                if(f_gera == 1)
                {
                    deletaLabirinto();

                    Personagem.pos_x = (retorna_matriz()[0].x + tam_celula/5);
                    Personagem.pos_y = (retorna_matriz()[0].y + tam_celula/5);

                    f_gera = 0;
                }

                larg_lab = 0;
                alt_lab = 0;

                cel_atual = 0;

                jogo_state = 0;

                seg = 0;
                min = 0;


            }else if(tecla[ENTER] && jogo_state == 0) f_insere = 1;
        } else if(evento.type == ALLEGRO_EVENT_KEY_UP)
        {
            f_move = 0;
            switch(evento.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    tecla[ESC] = 0;
                break;
                case ALLEGRO_KEY_UP:
                    tecla[CIMA] = 0;
                    f_insere = 0;
                break;
                case ALLEGRO_KEY_DOWN:
                    tecla[BAIXO] = 0;
                    f_insere = 0;
                break;
                case ALLEGRO_KEY_RIGHT:
                    tecla[DIREITA] = 0;
                break;
                case ALLEGRO_KEY_LEFT:
                    tecla[ESQUERDA] = 0;
                break;
                case ALLEGRO_KEY_ENTER:
                    tecla[ENTER] = 0;
                    f_insere = 0;
                break;
            }
        }



        if(jogo_state == 0)
        {
            al_draw_scaled_bitmap(fundomenu,0,0,1017,716,0,0,LARGURA,ALTURA,0);
            Mostra_Menu(&fonte,LARGURA,ALTURA);
            Atualiza_Menu(cursor,&fonte,LARGURA,ALTURA);
            jogo_state = Sai_Menu(cursor,tecla[ENTER]);

        }else if(jogo_state == 1)
        {
            if(i_nome <=3)
            {
              Insere_Nome(&fonte,tecla,&f_insere,i_nome,Nome_aux, LARGURA, ALTURA);
              if(tecla[ENTER] && f_insere == 0)
              {
                  f_insere = 1;
                  i_nome++;
              }
              al_draw_textf(fonte,al_map_rgb(255,255,0),LARGURA/2.5,ALTURA/2,0,"%s",Nome_aux);
              novo.nome[0] = Nome_aux[0];
              novo.nome[1] = Nome_aux[1];
              novo.nome[2] = Nome_aux[2];
            }

            else if(i_nome > 3)
            {
                if(larg_lab == 0 || alt_lab == 0)
                {
                    if(larg_lab == 0)
                    larg_lab = InsereLargura(&fonte,max_larg,&tecla,&f_insere,LARGURA,ALTURA);
                    else
                    alt_lab = InsereAltura(&fonte,max_alt,&tecla,&f_insere,LARGURA,ALTURA);
                }
                else
                {

              al_start_timer(temp);

              al_draw_filled_rectangle(0,0,LARGURA,ALTURA/10,al_map_rgb(0,0,255));
              al_draw_textf(fonte,al_map_rgb(255,255,255),LARGURA-10,ALTURA/40,ALLEGRO_ALIGN_RIGHT,"%s",Nome_aux);
              al_draw_textf(fonte,al_map_rgb(250,250,250),10,ALTURA/40,0,"%d:%.0f",min,seg);

              if(f_gera == 0)
              {
                  criaLabirinto(larg_lab,alt_lab,tam_celula,0,ALTURA/10);
                  labirintoPerfeito();
                  Personagem.pos_x = (retorna_matriz()[0].x + tam_celula/5);
                  Personagem.pos_y = (retorna_matriz()[0].y + tam_celula/5);
                  f_gera = 1;
                  rand_fundo = rand()%3;
              }

                drawFundo(fundo1,fundo2,fundo3,rand_fundo,LARGURA,ALTURA);
                drawLabirinto();

                jogo_state = Move_Personagem(&Personagem,&tecla,retorna_matriz(),larg_lab,larg_lab*alt_lab,tam_celula,&f_move);

                Mostra_Personagem(Personagem,pers_sprite,tam_personagem);
                }
            }


        }else if(jogo_state == 2)
            al_draw_scaled_bitmap(instrucoes,0,0,1080,768,0,0,LARGURA,ALTURA,0);
        else if(jogo_state == 3)
           Mostra_Recordistas(&fundorecordes,&txt,&fonte,LARGURA,ALTURA);
        else if(jogo_state == 4)
           fim = 1;
        else if(jogo_state == 5)
        {
            al_stop_timer(temp);

            novo.tmp_m = min;
            novo.tmp_s = seg;

            al_draw_textf(fonte,al_map_rgb(255,255,20),LARGURA/2,ALTURA/3,ALLEGRO_ALIGN_CENTER,"FIM DE JOGO!");
            al_draw_textf(fonte,al_map_rgb(255,255,20),LARGURA/2,ALTURA/2,ALLEGRO_ALIGN_CENTER,"SEU TEMPO: %d:%.0f",novo.tmp_m,novo.tmp_s);
            if(f_atualiza == 0)
            {
              Atualiza_Recordistas(&txt,novo,larg_lab*alt_lab,max_larg,max_alt);
              f_atualiza++;
            }
        }
        else jogo_state = 0;



        al_flip_display();
    }

    al_destroy_display(janela);
    al_destroy_bitmap(instrucoes);
    al_destroy_bitmap(pers_sprite);
    al_destroy_bitmap(fundo1);
    al_destroy_bitmap(fundo2);
    al_destroy_bitmap(fundo3);
    al_destroy_font(fonte);

    return 0;
}

void Config_Ini()
{
    if(!al_init())
    {
        fprintf(stderr, "Impossivel inicializar allegro5.h\n");
        exit(1);
    }
    if(!al_init_primitives_addon())
    {
        fprintf(stderr,"Impossivel inicializar biblioteca primitiva\n");
        exit(1);
    }
    al_init_font_addon();
    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        exit(1);
    }
    if(!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        exit(1);
    }

    if(!al_get_display_mode(al_get_num_display_modes() - 1, &dados_janela))
    {
        fprintf(stderr,"Impossivel carregar dados de resolucao\n");
        exit(1);
    }
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    LARGURA = 1024;//dados_janela.width;
    ALTURA = 768;//dados_janela.height;
    if((janela = al_create_display(LARGURA,ALTURA)) == NULL)
    {
        fprintf(stderr,"Impossivel criar display\n");
        exit(1);
    }
    if(!al_install_keyboard())
    {
        fprintf(stderr,"Impossivel instalar teclado\n");
        exit(1);
    }
    if(!al_install_mouse())
    {
        fprintf(stderr,"Impossivel instalar mouse\n");
        exit(1);
    }
     if((fila_eventos = al_create_event_queue()) == NULL)
    {
        fprintf(stderr,"Impossivel criar fila de eventos\n");
        exit(1);
    }

    if((temp = al_create_timer(0.01)) == NULL)
    {
        fprintf(stderr,"Impossivel criar temporizador\n");
        exit(1);
    }
    if((fonte = al_load_font("fonte.ttf",60,0))==NULL)
    {
        fprintf(stderr,"Impossivel carregar arquivo de fonte\n");
        exit(1);
    }
    if((instrucoes = al_load_bitmap("instrucoes.png")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar bitmap instrucoes\n");
        exit(1);
    }
    if((pers_sprite = al_load_bitmap("personagem.png")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar bitmap personagem\n");
        exit(1);
    }
    if((fundo1 = al_load_bitmap("fundo1.jpg")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar bitmap fundo1\n");
        exit(1);
    }
    if((fundo2 = al_load_bitmap("fundo2.jpg")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar bitmap fundo2\n");
        exit(1);
    }
    if((fundo3 = al_load_bitmap("fundo3.jpg")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar bitmap fundo3\n");
        exit(1);
    }
    if((fundomenu = al_load_bitmap("fundomenu.jpg")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar bitmap fundomenu\n");
        exit(1);
    }
    if((fundorecordes = al_load_bitmap("recordes.png")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar bitmap fundorecordes\n");
        exit(1);
    }
    if((txt = fopen("recordes.txt","r+")) == NULL)
    {
        fprintf(stderr,"Impossivel carregar arquivo recordes.txt\n");
        exit(1);
    }

    al_register_event_source(fila_eventos,al_get_display_event_source(janela));
    al_register_event_source(fila_eventos,al_get_keyboard_event_source());
    al_register_event_source(fila_eventos,al_get_mouse_event_source());
    al_register_event_source(fila_eventos,al_get_timer_event_source(temp));


}




