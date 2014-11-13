void criando_tabela()
{
	    FILE *entrada = fopen(argv[2], "r" );

        if ( entrada == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {
            int x;
            /* read one character at a time from file, stopping at EOF, which
               indicates the end of the file.  Note that the idiom of "assign
               to a variable, check the value" used below works because
               the assignment statement evaluates to the value assigned. */
            while  ( ( x = fgetc( entrada ) ) != EOF )
            {
                printf( "%c", x );
            }
            fclose( file );
        }
    }
}