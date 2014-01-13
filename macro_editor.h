#ifndef MACRO_EDITOR_H
#define MACRO_EDITOR_H

#include "ui_macro.h"
#include "terminal.h"

class macro_editor : public QDialog, public Ui::Macro_Editor
{
    Q_OBJECT
 
public:
    macro_editor(class terminal_app *parent = 0);    
    
public slots:
	
private:	
	QButtonGroup *macro_1_hex_ascii;
	QButtonGroup *macro_2_hex_ascii;
	QButtonGroup *macro_3_hex_ascii;
	QButtonGroup *macro_4_hex_ascii;
	QButtonGroup *macro_5_hex_ascii;
	QButtonGroup *macro_6_hex_ascii;
	QButtonGroup *macro_7_hex_ascii;
	QButtonGroup *macro_8_hex_ascii;
	QButtonGroup *macro_9_hex_ascii;
	QButtonGroup *macro_10_hex_ascii;
	QButtonGroup *macro_11_hex_ascii;
	QButtonGroup *macro_12_hex_ascii;
	
}; 

#endif
