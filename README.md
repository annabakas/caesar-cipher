main()
	encrypted_text.txt is read line by line using getline()
	Each line/sentence is then passed to split().
	After each sentence, the shift with the max occurences is written to shifts.txt and the occurences in shifts[] is reset for the next sentence.


split()
	split() takes in a sentence and splits it using strtok()
	Each token/word from the sentence is then passed to decrypt() to be shifted.

decrypt()
	decrypt() takes in a word and shifts it for keys 1-25
	Each decrypted word and its key is passed to openDict() to see if it is an English word.

openDict()
	openDict() opens and reads dictionary2.txt into an array.
	Then, it loops through the dictionary words and compares each word to the decrypted word that was passed in.
	If the decrypted word matches the dictionary word, variable found is incremented.
	Once a word has been checked against all the dictionary words, the shift with the max occurences is found.

	Reading file into array based on: https://stackoverflow.com/questions/14781981/from-input-file-to-array-using-malloc-and-realloc
