1. In main(), encryptedtext.txt is read line by line using getline() until EOF. Each line/sentence is then passed to split(). After each sentence, the shift with the max occurences is written to shifts.txt and the occurences in shifts[] is reset for the next sentence.

2. In split(), the sentence being passed in is split into words using strtok(). Each token/word from the sentence is then passed to decrypt() to be shift.

3. In decrypt(), the decrypted word is shifted for keys 1-25. It checks all characters are in range A-Z. If a character is not within that range, it loops around so that the character comes back within the range. Each decrypted word and its key is passed to openDict() to see if it is an English word.

4. In openDict(), dictionary2.txt is opened and read into an array. Then, it loops through the dictionary words and compares each word to the decrypted word that was passed in. If the decrypted word matches the dictionary word, a variable found is incremented. Once a word has been checked against all the dictionary words, the shift with the max occurences is found.

5. Reading file into array based on: https://stackoverflow.com/questions/14781981/from-input-file-to-array-using-malloc-and-realloc
