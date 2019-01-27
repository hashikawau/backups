/*********************************/
/*Åö Unicode ÇégÇ§    ëOìc ñ´ Åö*/
/*********************************/
#include    <windows.h>
#include    <conio.h>
#include <gl\gl.h>
#include <gl\glaux.h>

//Åö Windows Main ä÷êî
int main()
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGBA);
    auxInitPosition( 100, 100, 250, 250 );
    auxInitWindow( "My first OpenGl program" );
    
    glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    
    glFlush();
    
    cprintf( "Press any key to close the Window\n" );
    getch();
    
    return 0;
}