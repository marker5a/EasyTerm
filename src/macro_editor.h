/*
 * macro_editor.h is part of EasyTerm, and is Copyright Christopher M
 * Hamilton (marker5a@gmail.com), 2014.
 *
 * EasyTerm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * EasyTerm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MACRO_EDITOR_H
#define MACRO_EDITOR_H

#include "ui_macro.h"
#include "terminal.h"

class macro_editor : public QDialog, public Ui::Macro_Editor
{
    Q_OBJECT
 
public:
    macro_editor(class terminal_app *parent = 0);    
    void connect_widgets();
    void group_radio_buttons();
    void load_settings();
    
public slots:
	void save_macros();
	
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
	class terminal_app *parent;
}; 

#endif
