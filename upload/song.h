/* 
 * File:   song.h
 * Author: Henry
 *
 * Created on July 22, 2014, 10:35 AM
 */

#ifndef SONG_H
#define	SONG_H


#define NL 20

void playSong() {
    create_write_byte(128);
    create_write_byte(132);

    create_write_byte(140);
    create_write_byte(0);
    
    create_write_byte(5); //song length 
    
    create_write_byte(62);
    create_write_byte(12);
    create_write_byte(62);
    create_write_byte(40);
    create_write_byte(66);
    create_write_byte(12);
    create_write_byte(69);
    create_write_byte(12);
    create_write_byte(74);
    create_write_byte(36);

    create_write_byte(141);
    create_write_byte(0);
}

void playCH() {
    create_write_byte(128);
    create_write_byte(132);

    create_write_byte(140);
    create_write_byte(0);
    
    create_write_byte(16);
    
    create_write_byte(69); create_write_byte(NL*4);
create_write_byte(68); create_write_byte(NL);
create_write_byte(69); create_write_byte(NL);
create_write_byte(68); create_write_byte(NL*2);
create_write_byte(64); create_write_byte(NL*3);
create_write_byte(61); create_write_byte(NL);
create_write_byte(66); create_write_byte(NL*2);
create_write_byte(61); create_write_byte(NL*4);
create_write_byte(64); create_write_byte(NL);
create_write_byte(69); create_write_byte(NL*4);
create_write_byte(71); create_write_byte(NL);
create_write_byte(73); create_write_byte(NL);
create_write_byte(76); create_write_byte(NL*2);
create_write_byte(73); create_write_byte(NL*2);
create_write_byte(66); create_write_byte(NL);
create_write_byte(68); create_write_byte(NL);


    create_write_byte(141);
    create_write_byte(0);
}


#endif	/* SONG_H */

