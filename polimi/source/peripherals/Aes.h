//
// Created by famiglia on 16/01/21.
//

#ifndef SOURCE_AES_H
#define SOURCE_AES_H
struct Struct_AES {

    volatile unsigned short CTRL; //0x4..0
    volatile unsigned char padding[14];
    volatile unsigned int BLOCK0; //0x4..10
    volatile unsigned int BLOCK1; //0x4..10
    volatile unsigned int BLOCK2; //0x4..10
    volatile unsigned int BLOCK3; //0x4..10
    volatile unsigned int KEY0; //0x4..10
    volatile unsigned int KEY1;
    volatile unsigned int KEY2;
    volatile unsigned int KEY3;
    volatile unsigned int KEY4;
    volatile unsigned int KEY5;
    volatile unsigned int KEY6;
    volatile unsigned int KEY7; //0x4000003c start adress


};

#define AES ((struct Struct_AES *) 0x40000000)

class Aes {
/**
* Initializes the peripheral and set the key that will be used for future
encryptions/decryptions
* \param key pointer to the key
* \param key_size 128 for a 128 bit key, 256 for a 256 bit key
*/
    void AES_init_key(const unsigned int key[], int key_size) {

        AES->CTRL |= 1 << 4; //enable the peripheral, 1 shifted by 4 positions

        if (key_size == 256) {
            AES->CTRL |= 1 << 0; //work with a 256 key

            AES->KEY0 = key[0];
            AES->KEY1 = key[1];
            AES->KEY2 = key[2];
            AES->KEY3 = key[3];

            AES->KEY4 = key[4];
            AES->KEY5 = key[5];
            AES->KEY6 = key[6];
            AES->KEY7 = key[7];
        } else {

            AES->CTRL &= ~(1 << 0); //work with a 258 key

            AES->KEY0 = key[0];
            AES->KEY1 = key[1];
            AES->KEY2 = key[2];
            AES->KEY3 = key[3];
        }

    }

    /**
    * Blocking function that returns once all bytes are encrypted.
    * \param dest encrypted data have to be stored here
    * \param src pointer to data to encrypt
    * \param len number of 16 byte blocks to encrypt
*/
    void AES_encrypt(unsigned int dest[], const unsigned int src[], int len) {

        //encrypt
        AES->CTRL &= ~(1 << 3);
        blockHelper(dest, src, len);

    }

    void AES_decrypt(unsigned int dest[], const unsigned int src[], int len)
    {
        AES->CTRL |= 1<<3;
        blockHelper(dest,src,len);
    }


    void blockHelper(unsigned int dest[], const unsigned int *src, int len) { //len = 16 byte -> I have 4 blocks of 4 bytes so it's number of times I'll fill all the blocks
//for each 16 bytes, split them into blocks and wait for conversion
        for (int b = 0; b < len; ++b) {

            AES->BLOCK0 = src[b * 4 + 0];
            AES->BLOCK1 = src[b * 4 + 1];
            AES->BLOCK2 = src[b * 4 + 2];
            AES->BLOCK3 = src[b * 4 + 3];

            AES->CTRL |= (1 << 2); //go
            //wait (polling)
            while ((AES->CTRL & (1 << 5)) == 0);
            //clear
            AES->CTRL |= (1 << 5); //writing 1 clears the bit

            dest[b * 4 + 0] = AES->BLOCK0;
            dest[b * 4 + 1] = AES->BLOCK1;
            dest[b * 4 + 2] = AES->BLOCK2;
            dest[b * 4 + 3] = AES->BLOCK3;

        }
    }

};


#endif //SOURCE_AES_H
