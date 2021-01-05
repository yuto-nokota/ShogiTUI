#include<string.h>
#include<assert.h>
#include<stdio.h>
#include"sfen2bod.h"

// position [sfen <sfenstring> | startpos ] moves <move1> ... <movei>
// e.g.)
// position sfen 5k1nl/5sgb1/8p/5p1P1/6Gp1/9/6N1P/9/8L b P 1 moves 

void sfen2bod ( const char *sfen, char *bod ) {
  int i;
  int r=1;
  char board[4096]=" ９ ８ ７ ６ ５ ４ ３ ２ １\n"
                   "+---------------------------+\n"
                   "|";
  char turn[16]="";
  char hand[2][128]={"",""};
  int tempo;
  char kansuji[19][8]={"","一","二","三","四","五","六","七","八","九",
                       "十","十一","十二","十三","十四","十五","十六",
                       "十七","十八"};
  // parse board
  for ( i=0; sfen[i] && sfen[i]!=' '; i++ ) {
    if ( sfen[i] == '/' ) {
      assert( r<9 );
      strcat(board,"|");
      strcat(board,kansuji[r++]);
      strcat(board,"\n|");
      continue;
    } else if ( '1' <= sfen[i] && sfen[i] <= '9' ) {
      int n=sfen[i]-'0',k;
      for ( k=0; k<n; k++ ) {
        strcat(board," ・");
      }
    } else {
      if ( sfen[i] == '+' ) {
        switch ( sfen[++i] ) {
          case 'R' : strcat(board," 竜"); break;
          case 'B' : strcat(board," 馬"); break;
          case 'S' : strcat(board," 全"); break;
          case 'N' : strcat(board," 圭"); break;
          case 'L' : strcat(board," 杏"); break;
          case 'P' : strcat(board," と"); break;
          case 'r' : strcat(board,"v竜"); break;
          case 'b' : strcat(board,"v馬"); break;
          case 's' : strcat(board,"v全"); break;
          case 'n' : strcat(board,"v圭"); break;
          case 'l' : strcat(board,"v杏"); break;
          case 'p' : strcat(board,"vと"); break;
        }
      } else {
        switch ( sfen[i] ) {
          case 'K' : strcat(board," 玉"); break;
          case 'R' : strcat(board," 飛"); break;
          case 'B' : strcat(board," 角"); break;
          case 'G' : strcat(board," 金"); break;
          case 'S' : strcat(board," 銀"); break;
          case 'N' : strcat(board," 桂"); break;
          case 'L' : strcat(board," 香"); break;
          case 'P' : strcat(board," 歩"); break;
          case 'k' : strcat(board,"v玉"); break;
          case 'r' : strcat(board,"v飛"); break;
          case 'b' : strcat(board,"v角"); break;
          case 'g' : strcat(board,"v金"); break;
          case 's' : strcat(board,"v銀"); break;
          case 'n' : strcat(board,"v桂"); break;
          case 'l' : strcat(board,"v香"); break;
          case 'p' : strcat(board,"v歩"); break;
        }
      }
    }
  }
  strcat(board,"|九\n+---------------------------+");
  // parse tempo
  for ( i++; sfen[i] && sfen[i]!=' '; i++ ) {
    if ( sfen[i]=='b') strcpy(turn,"先手番");
    if ( sfen[i]=='w') strcpy(turn,"後手番");
  }
  // parse hand
  for ( i++; sfen[i] && sfen[i]!=' '; i++ ) {
    int n=0;
    if ( sfen[i] == '-' ) break;
    if ( '2' <= sfen[i] && sfen[i] <= '9' ) {
      n=sfen[i++]-'0';
    } else if ( sfen[i] == '1' ) {
      n=(sfen[i]-'0')*10 + (sfen[i+1]-'0');
      i+=2;
    }
    switch ( sfen[i] ) {
      case 'R' : strcat(hand[0],"飛"); strcat(hand[0],kansuji[n]); break;
      case 'B' : strcat(hand[0],"角"); strcat(hand[0],kansuji[n]); break;
      case 'G' : strcat(hand[0],"金"); strcat(hand[0],kansuji[n]); break;
      case 'S' : strcat(hand[0],"銀"); strcat(hand[0],kansuji[n]); break;
      case 'N' : strcat(hand[0],"桂"); strcat(hand[0],kansuji[n]); break;
      case 'L' : strcat(hand[0],"香"); strcat(hand[0],kansuji[n]); break;
      case 'P' : strcat(hand[0],"歩"); strcat(hand[0],kansuji[n]); break;
      case 'r' : strcat(hand[1],"飛"); strcat(hand[1],kansuji[n]); break;
      case 'b' : strcat(hand[1],"角"); strcat(hand[1],kansuji[n]); break;
      case 'g' : strcat(hand[1],"金"); strcat(hand[1],kansuji[n]); break;
      case 's' : strcat(hand[1],"銀"); strcat(hand[1],kansuji[n]); break;
      case 'n' : strcat(hand[1],"桂"); strcat(hand[1],kansuji[n]); break;
      case 'l' : strcat(hand[1],"香"); strcat(hand[1],kansuji[n]); break;
      case 'p' : strcat(hand[1],"歩"); strcat(hand[1],kansuji[n]); break;
    }
  }
  if ( hand[0][0]=='\0' ) strcpy(hand[0],"なし");
  if ( hand[1][0]=='\0' ) strcpy(hand[1],"なし");
  // parse tempo
  sscanf(sfen+i+1,"%d",&tempo);
  // output
  sprintf(bod,"後手の持ち駒：%s\n%s\n先手の持ち駒：%s\n\n%5s%s(%d手目)\n"
          ,hand[1],board,hand[0],"",turn,tempo);
}

