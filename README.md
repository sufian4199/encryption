# encryption
This project implements an encryption system in C++ using a modified, simplified version of AES (Advanced Encryption System) that will (1) read the plain text from a file and a key from another file; (2) encrypt the plain text according to the requirements detailed below; and (3) write the output for each step to the screen and to an output file. 
# 1. Input Files
The program will prompt the user to enter the name of the input file containing the plain text that will be encrypted (i.e., the plaintext input file) as well as the name of the input file containing the key that will be used in the encryption process (i.e., the key input file).
# 2. Output File
Program will prompt the user to enter the name of the output file containing the output of each step of the encryption algorithm. It will write the output of each step of the encryption algorithm in the output file. First, write the name of the step on a separate line, and then write the output of that particular step.
# 3. Encryption Algorithm
The encryption algorithm shall consist of two parts: (1) substitution, and (2) encryption on blocks of size 4 × 4 characters. The detailed description of the steps is as follows:
#   • Preprocessing
Remove any punctuation and whitespace characters from the input.
#   • Substitution
Perform a polyalphabetic substitution using the Vigenère cipher on the input file with the key provided in the key input file.
#   • Padding
Following steps are performed on blocks of size 4 x 4 characters formed from the output of "substitution" step. They are parts of AES and as in any block cipher, the input has to be padded. In this particular case, pad the output from the previous step with A’s so that the length of the message is divisible by 16.
#   • ShiftRows
This step is the same as the ShiftRows step in the AES encryption. Circularly shift the rows in each block in the following fashion: The first row remains the same. Shift the second row one position to the left. Shift the third row two positions to the left. Finally, shift the fourth row three positions to the left.
#   • Parity Bit
Convert each character to its numeric value (0 – 127) and use the most significant bit as a parity bit. We will give even parity to each character
#   • MixColumns
This step diffuses the
encryption. The transformation is performed by multiplying the circulant MDS matrix with each column from the input(Cross Product). This transformation is repeated for each block.
However, instead of simple multiplication, it uses multiplication in the Rijndael’s Galois field. But this is not as difficult as it sounds since this transformation matrix only contains the numbers 1, 2, and 3. Therefore, you will only multiply with 1, 2, and 3.
# 4. References
Although this encryption is a modified, simplified version of AES, you may refer to the Lecture Notes posted on Blackboard or the following for background information on AES:
http://en.wikipedia.org/wiki/Advanced_Encryption_Standard
