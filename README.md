# Crypt
Crypt is a file encryption/decryption tool written in C++.

## Usage
First, compile the "crypt.cpp" file into a "crypt.exe" executable file.

To encrypt a file, run: ./crypt e "input_filename" "output_filename".

To decrypt a file, run: ./crypt d "input_filename" "output_filename".

After entering the command, you will be prompted for a key for encrypting/decrypting the file.

## Notice
- Since it is symmetric encryption, the key that is used to encrypt a file, is needed to decrypt the same file.
- You can pick any output_filename, but one with a ".bin" file extension is preferred when encrypting a file.
- When decrypting a file, you need to make sure the decrypted file has the original file extension. 
