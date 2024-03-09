#### @@ Lilly tau
# Compact font designer
the compact font designer is a program allowing the user to create files containing 8x8 single color images representing ascii/utf8 character codes, each input file is written as size 2040. In which each character is eight bytes long, allowing for 255 characters. The commands for editting a compact\_font file are as follows:

- switch : changes which character you are editting in the file
- row    : changes the row of the character you are currently editting
- write  : sets the current row to an 8 bit binary number and increments row
- show   : prints the current character binary to the screen as an 8x8 grid
- load   : loads the contents of the current file for editting
- save   : writes the current working memory into the current file
- fclose : closes the current file and prompts for a new one
- help   : opens this menu
- nsexit : exits without saving
- exit   : exits and saves
- status : shows various working variables (such as current character, file, and row)
