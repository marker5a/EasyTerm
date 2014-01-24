#include <QApplication> 
#include "terminal.h"

int main(int argc, char **argv)
{
	// create the mainwindow class
    QApplication app(argc, argv);
    terminal_app *dialog = new terminal_app(&app);
 
	// show the main window
    dialog->show();
    app.exec();
	
	return 0;    
}
