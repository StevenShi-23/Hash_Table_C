/*
Karl Toby Rosenberg

main test program 2

creates a hash table, reads a text file containing words,
(handles UNIX and DOS end-lines), adds all words to the hash table,
displays the table 

*/

#include "hashtable.h"

/*
    main
        note: pass a single command line argument of 'p' to display the hash table
*/
int main(int argc, char *argv[])
{
    //open a text file (for reading), one word per line for now
    FILE *text = fopen("words.txt", "r");
    
    if(!text)exit(-1);

    //default table size, default load factor of 0.75, default Jenkins hash function
    hash_table_t* hash_table = init_hash_table(127151, DEFAULTMAXLOAD, DEFAULTHASH);
    if(!hash_table)exit(-1);

    //count number of words reached
    uint64_t word_count = 1;
    //create a buffer to store words of at most 50 characters
    char buffer[51];
    //read each line
    while(fgets(buffer, 51, text))
    {
        //replace the \n new line character with a c string null terminator 
        if(buffer[0] && buffer[strlen(buffer)-1] == '\n')
        {
            buffer[strlen(buffer)-1] = '\0';
        }
        //also check for the \r new line character as part of \r\n Windows new line sequences
        if(buffer[0] && buffer[strlen(buffer)-1] == '\r')
        {
            buffer[strlen(buffer)-1] = '\0';
        }
        //add the word and its word number to the hash table as a key-value pair
        //(the put_record function allocates memory for a copy of the char*)
        put_record(buffer, word_count, hash_table);
        ++word_count;
    }
    //close the text file
    fclose(text);

    if(ferror(text))
    {
        printf("%s\n", "ERROR");
        del_hash_table(&hash_table);
        exit(-2);
    }
    
    //passing a single command line argument of 'p'
    //has the program display the table
    if(argc == 2 && argv[1][0] == 'p')
    {
        print_table(hash_table);
    }
    
    //delete the hash table
    del_hash_table(&hash_table);

    return 0;
}