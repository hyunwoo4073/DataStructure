#ifndef KARPRABIN_H
#define KARPRABIN_H

int KarpRabin(char* Text, int TextSize, int Start,
              char* Parttern, int PatternSzie);

int Hash(char* String, int Size);
int ReHash(char* String, int Start, int Size, int HashPrev, int Coefficient);
#endif