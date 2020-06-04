#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


void Mostra_Menu(ALLEGRO_FONT **fonte,int LARGURA, int ALTURA);
void Atualiza_Menu(int cursor,ALLEGRO_FONT **fonte,int LARGURA, int ALTURA);
int Sai_Menu(int cursor, int enter);
void Mostra_Recordistas(ALLEGRO_BITMAP **fundorecordes,FILE **txt,ALLEGRO_FONT **fonte,int LARGURA, int ALTURA);


#endif // MENU_H_INCLUDED
